#include "external.h"
#include "filedb.h"

/*
static int openPortToFd(int port){
    int fd = 0, connfd = 0;
	struct sockaddr_in serv_addr;

	char sendBuff[1025];
	time_t ticks;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

    if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1) {
        printf("Error: openPortToFd setting nonblock\n");
		return -1;
    }

    int one = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int)) < 0) {
        printf("Error: openPortToFd setting reuse addr\n");
		return -1;
	}
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(int)) < 0) {
        printf("Error: openPortToFd setting reuse addr\n");
		return -1;
	}

	if(bind(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0){
        printf("Error: openPortToFd binding '%s'\n", strerror(errno));
		return -1;
    }

	if(listen(fd, 10) != 0){
        printf("Error: openPortToFd listening\n");
		return -1;
    };

    return fd;

    return 0;
}

lifecycle_t ServCtx_CloseReq(ServCtx *sctx, ReqLfc *rlfc){
    lifecycle_t r = ServCtx_EpollEvRemove(sctx, rlfc);
    if(r == SUCCESS){
        close(rlfc->fd);
        MemCtx_Cycle(rlfc->m, MBLOCK_FREE_ALL);
        return SUCCESS;
    }
    return r;
}

lifecycle_t ServCtx_ServeRound(ServCtx *sctx){
    lifecycle_t r = ERROR;
    int ev_count;
	struct epoll_event *curev;
	struct epoll_event event;
    struct epoll_event events[SERV_MAX_EVENTS];
	char buff[SERV_READ_SIZE + 1];

    ev_count = epoll_wait(sctx->epoll_fd, events, SERV_MAX_EVENTS, EPOLL_WAIT);
    if(ev_count == 0){
        if(DEBUG_CYCLESERVE_REQCYCLE){
            String_PrintColor(Nstr(sctx->m, "ServeRound EV Count 0\n"), DEBUG_CYCLESERVE_REQCYCLE);
        }
        return NOOP;
    }
    for(int i = 0; i < ev_count; i++){
        ReqLfc *rlfc = (ReqLfc *)events[i].data.ptr;
        sctx->request = rlfc;
        if(rlfc == NULL || rlfc->type != TYPE_REQ_LFC){
            printf("Error: bad rlfc from epoll\n");
            continue;
        }
        if(rlfc->handler_rh == NULL){
            rlfc->lifecycle = ERROR;
            printf("Error: bad rlfc from epoll\n");
        }
        if(rlfc->lifecycle == ERROR && rlfc->handler_rh != NULL && rlfc->handler_rh->lifecycle != ERROR){
            printf("Error: rlfc is off state error\n");
            ReqLfc_SetError(sctx, rlfc, NULL);
        }

        if(rlfc->handler_rh == NULL || rlfc->lifecycle == SUCCESS){
            if(DEBUG_CYCLESERVE_REQCYCLE){
                String_PrintColor(String_FormatN(sctx->m, 4, "Finalizing(", "%d", &(rlfc->fd), ")\n"), DEBUG_CYCLESERVE_REQCYCLE);
            }
            r = ServCtx_EpollEvRemove(sctx, rlfc);
            MemCtx_Cycle(rlfc->m, MBLOCK_FREE_ALL);
        }else{
            if(DEBUG_CYCLESERVE_REQCYCLE){
                String_PrintColor(String_FormatN(sctx->m, 7, "Serving(", "%d", &(rlfc->fd), "):", "%S", rlfc->handler_rh->name_s, "\n"), DEBUG_CYCLESERVE_REQCYCLE);
            }
            int direction = rlfc->handler_rh->direction;
            r = rlfc->handler_rh->func(sctx, rlfc->handler_rh, rlfc);
            int newDirection = rlfc->handler_rh->direction;
            if(direction != newDirection){
                ServCtx_EpollEvUpdate(sctx, rlfc, newDirection);
            }
        }
    }

    return SUCCESS;
}

lifecycle_t ServCtx_AcceptRound(ServCtx *sctx){
    int new_fd = accept(sctx->socket_fd, (struct sockaddr*)NULL, NULL);
    if(new_fd > 0){
        sctx->health.totalIncoming++;
        fcntl(new_fd, F_SETFL, O_NONBLOCK);
        ReqLfc *rlfc =  ServCtx_MakeReqLfc(sctx, new_fd);
        if(rlfc == NULL || rlfc->handler_rh == NULL){
            printf("Error: ServCtx_AcceptRound rlfc or handler is null\n");
            return ERROR;
        }
        lifecycle_t r = ServCtx_EpollEvAdd(sctx, rlfc, rlfc->handler_rh->direction); 
        if(r != SUCCESS){
            printf("Error: ServCtx_Accept\n");
            return r;
        }
        sctx->request = rlfc;
        return SUCCESS;
    }
    return NOOP;
}

lifecycle_t ServCtx_Stop(MemCtx *m, ServCtx *sctx){
    close(sctx->socket_fd);
    close(sctx->epoll_fd);
    return SUCCESS;
}


int serve(int port){
    ServeCtx *sctx = ServeCtx_Make();
    ServeCtx *sctx = ServeCtx_Serve(port);
    sctx->port = port;
    int fd = openPortToFd(port);
    if(fd <= 0){
        printf("Serv: Error opening port %d\n", port);
        return ERROR;
    }

    sctx->socket_fd = fd;

	int epoll_fd =  epoll_create1(0);
	if (epoll_fd == -1) {
		printf("Failed to create epoll file descriptor\n");
		return ERROR;
	}
    sctx->epoll_fd = epoll_fd;
}
*/
