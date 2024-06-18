#include "external.h"
#include "filestore.h"

static int openPortToFd(int port){
    int fd = 0;
	struct sockaddr_in serv_addr;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

    if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
        Fatal("openPortToFd setting nonblock\n", TYPE_SERVECTX);
		return -1;
    }

    int one = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) < 0) {
        Fatal("openPortToFd setting reuse addr\n", TYPE_SERVECTX);
		return -1;
	}
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(int)) < 0) {
        Fatal("openPortToFd setting reuse addr\n", TYPE_SERVECTX);
		return -1;
	}

	if(bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0){
        Fatal("openPortToFd binding\n", TYPE_SERVECTX);
		return -1;
    }

	if(listen(fd, 10) != 0){
        Fatal("openPortToFd listening\n", TYPE_SERVECTX);
		return -1;
    };

    return fd;
}

static status Serve_EpollEvUpdate(Serve *sctx, Req *req, int direction){
    int r;
    struct epoll_event event;

    event.events = direction;
    event.data.ptr = (void *)req;

    r = epoll_ctl(sctx->epoll_fd, EPOLL_CTL_MOD, req->fd, &event);
    if(r != 0){
        Error("Failed to modify file descriptor\n");
        return ERROR;
    }

    return SUCCESS;
}

status Serve_NextState(Serve *sctx, Req *req){
    int direction = req->direction;
    if(req->state == READY){
        req->state = INCOMING;
    }
    status state = req->state;
    if(state == INCOMING){
        direction = EPOLLIN;
    }else if(state == PROCESSING){
        direction = EPOLLIN|EPOLLOUT;
    }else if(state == RESPONDING){
        direction = EPOLLOUT;
    }else if(state == ERROR){
        direction = EPOLLOUT;
    }else{
        Error("Direction Not Found");
        return ERROR;
    }

    if(direction != -1 && direction != req->direction){
        req->direction = direction;
        Serve_EpollEvUpdate(sctx, req, req->direction);
        return SUCCESS;
    }

    return NOOP;
}

static status Serve_EpollEvAdd(Serve *sctx, Req *req, int fd, int direction){
    int r;
    struct epoll_event event;

    event.events = direction;
    event.data.ptr = (void *)req;

    r = epoll_ctl(sctx->epoll_fd, EPOLL_CTL_ADD, fd, &event);
    if(r != 0){
        Error("Failed to add file descriptor to epoll");
        return ERROR;
    }

    req->fd = fd;
    req->direction = direction;

    return SUCCESS;
}

static status Serve_EpollEvRemove(Serve *sctx, Req* req){
    int r = epoll_ctl(sctx->epoll_fd, EPOLL_CTL_DEL, req->fd, NULL);
    if(r != 0){
        Error("Failed to remove file descriptor to epoll");
        return ERROR;
    }

    return SUCCESS;
}

static status Serve_CloseReq(Serve *sctx, Req *req){
    status r = Serve_EpollEvRemove(sctx, req);
    if(r == SUCCESS){
        close(req->fd);
        MemCtx_Free(req->m);
        return SUCCESS;
    }
    return r;
}

status Serve_Respond(Serve *sctx, Req *req){
    if(req->cursor->state != COMPLETE){
        SCursor_Prepare(req->cursor, SERV_WRITE_SIZE); 
        size_t l = write(req->fd, req->cursor->seg->bytes, req->cursor->immidiateLength);
        status r = SCursor_Incr(req->cursor, l);
        if(r == COMPLETE){
            req->state = COMPLETE;
        }
    }

    if(req->cursor->position >= req->response->length){
        req->state = COMPLETE;
    }

    return req->state;
}

status Serve_AcceptRound(Serve *sctx){
    int new_fd = accept(sctx->socket_fd, (struct sockaddr*)NULL, NULL);
    if(new_fd > 0){
        fcntl(new_fd, F_SETFL, O_NONBLOCK);
        Req *req = Req_Make();

        if(sctx != NULL){
            status r = Serve_EpollEvAdd(sctx, req, new_fd, EPOLLIN); 
            Serve_NextState(sctx, req);
            if(r != SUCCESS){
                Error("Serve_Accept");
                return ERROR;
            }

            return SUCCESS;
        }
    }

    return NOOP;
}

status Serve_ServeRound(Serve *sctx){
    status r = ERROR;
    int ev_count;
	struct epoll_event *curev;
	struct epoll_event event;
    struct epoll_event events[SERV_MAX_EVENTS];
	char buff[SERV_READ_SIZE + 1];

    ev_count = epoll_wait(sctx->epoll_fd, events, SERV_MAX_EVENTS, EPOLL_WAIT);
    if(ev_count == 0){
        return NOOP;
    }

    for(int i = 0; i < ev_count; i++){
        Req *req = (Req *)events[i].data.ptr;
        if(req == NULL){
            Error("bad req from epoll");
            continue;
        }

        if(req->state == ERROR){
            Req_SetError(sctx, req, NULL);
        }

        if(req->state == COMPLETE){
            Log(0, "Served %d %s - mem: %ld", req->fd, Method_ToString(req->method), MemCount());
            r = Serve_CloseReq(sctx, req);
        }

        if(req->state == RESPONDING){
            Serve_Respond(sctx, req);
        }else{
            Req_Handle(sctx, req);
        }
    }

    return SUCCESS;
}

status Serve_Run(Serve *sctx, int port){
    int fd = openPortToFd(port);
    sctx->port = port;
    sctx->socket_fd = fd;

	int epoll_fd =  epoll_create1(0);
	if (epoll_fd == -1) {
		Fatal("Failed to create epoll file descriptor\n", TYPE_SERVECTX);
		return ERROR;
	}

    sctx->epoll_fd = epoll_fd;
    sctx->serving = TRUE;
    int cadance = 0;
    while(sctx->serving){
        if(cadance-- == 0){
            Serve_AcceptRound(sctx);
            cadance = ACCEPT_CADANCE;
        }
        Serve_ServeRound(sctx);
    }

    return SUCCESS;
}

Serve *Serve_Make(MemCtx *m){
    Serve *sctx = (Serve *)MemCtx_Alloc(m, sizeof(Serve)); 
    sctx->m = m;
    return sctx;
}
