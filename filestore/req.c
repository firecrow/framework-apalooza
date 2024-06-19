#include "external.h"
#include "filestore.h"

static char *okBase_cstr = "HTTP/1.1 200 OK\r\nServer: filestore\r\nContent-Length: ";
static String *packageResponse(MemCtx *m, String *content){
    String *s = String_From(m, okBase_cstr);
    String *length_s = String_FromInt(m, (int)content->length); 
    String_Add(m, s, length_s);
    String_AddCstr(m, s, "\r\n\r\n", 4);
    String_Add(m, s, content);

    return s;
}

static char *errBase_cstr = "HTTP/1.1 500 Error\r\nServer: filestore\r\nContent-Length: ";
static String *packageError(MemCtx *m, String *content){
    String *s = String_From(m, errBase_cstr);
    String *length_s = String_FromInt(m, (int)content->length); 
    String_Add(m, s, length_s);
    String_AddCstr(m, s, "\r\n\r\n", 4);
    String_Add(m, s, content);

    return s;
}

char *Method_ToString(int method){
    if(method == METHOD_GET){
        return "GET";
    }else if(method == METHOD_SET){
        return "SET";
    }else if(method == METHOD_UPDATE){
        return "UPDATE";
    }else{
        return "UNKONWN_method";
    }
}

status Req_Parse(Serve *sctx, Req *req, String *s){
    Range find;
    Range_Set(&find, s);

    if(req->method == METHOD_UNKOWN){
        int i = 0;
        int start = find.start.position;
        while(methodTk[i] != NULL && find.state != COMPLETE){
            if(SCursor_Find(&find, methodTk[i], TRUE) == COMPLETE){
                req->method = methods[i];
                break;
            }
            i++;
        }
    }

    if(SCursor_Find(&find, space_tk, TRUE) != COMPLETE){
        req->state = ERROR;
        return req->state;
    }

    if(SCursor_Find(&find, space_tk, FALSE) == COMPLETE){
        req->path = String_FromRange(req->m, &find);
    }else{
        req->state = ERROR;
        return req->state;
    }
        
    req->state = PROCESSING;
    Serve_NextState(sctx, req);
    return req->state;
}

status Req_Recv(Serve *sctx, Req *req){
    uchar buff[SERV_READ_SIZE];
    size_t l = recv(req->fd, buff, SERV_READ_SIZE, 0);
    if(l > 0){
        return Req_Parse(sctx, req, String_Make(req->m, buff));
    }

    return NOOP;
}

status Req_Process(Serve *sctx, Req *req){
    req->response = packageResponse(req->m, String_From(req->m, "poo"));
    req->cursor = SCursor_Make(req->m, req->response);

    req->state = RESPONDING;
    Serve_NextState(sctx, req);
    return req->state;
}

status Req_Handle(Serve *sctx, Req *req){
    if(req->state == INCOMING){
        return Req_Recv(sctx, req);
    }

    if(req->state == PROCESSING){
        return Req_Process(sctx, req);
    }

    return NOOP;
}

Req *Req_Make(){
    MemCtx *m = MemCtx_Make();
    Req* req = (Req *)MemCtx_Alloc(m, sizeof(Req));
    req->direction = -1;

    MemCtx_Bind(m, req);

    return req;
}

status Req_SetError(Serve *sctx, Req *req, String *msg){
    req->state = RESPONDING;
    Serve_NextState(sctx, req);
    req->response = packageError(req->m, msg);
    return SUCCESS;
}
