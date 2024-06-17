#include "external.h"
#include "filestore.h"

i64 Req_Parse(Serve *sctx, Req *req, String *s){
    i64 taken = 0;
        
    return taken;
}

status Req_Recv(Serve *sctx, Req *req){
    uchar buff[SERV_READ_SIZE];
    size_t l = recv(rec->fd, buff, SERV_READ_SIZE, 0);
    if(l > 0){
        return Req_Parse(sctx, req, String_Make(req->m, buff));
    }
}

status Req_Process(Serve *sctx, Req *req){
    req->response = String("response");
    req->status = RESPONDING;
}

status Req_Handle(Serve *sctx, Req *req){
    printf("Handle query %d", req->fd);
    fflush(stdout);
    if(state == READY){
        state = INCOMING;
    }

    if(state == INCOMING){
        return Req_Recv(sctx, req);
    }

    if(state == PROCESSING){

    }

    if(state == RESPONDING){

    }
}

Req *Req_Make(){
    MemCtx *m = MemCtx_Make();
    Req* req = (Req *)MemCtx_Alloc(m, sizeof(Req));
    MemCtx_Bind(m, req);

    return req;
}

status Req_SetError(Serve *sctx, Req *req, String *msg){
    req->state = ERROR;
    req->response = msg;
    return SUCCESS;
}

