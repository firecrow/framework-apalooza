#include "external.h"
#include "filestore.h"

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

i64 Req_Parse(Serve *sctx, Req *req, String *s){
    i64 taken = 0;
        
    return taken;
}
