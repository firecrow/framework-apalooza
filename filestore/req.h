typedef struct serve_req {
    status state;
    int fd;
    MemCtx *m;
    byte method;
    String *_shelf;
    String *id;
    String *body;
    String *response;
    SCursor *cursor;
} Req;

Req *Req_Make();
i64 Req_Parse(Serve *sctx, Req *req, String *s);
status Req_SetError(Serve *sctx, Req *req, String *msg);
status Req_Recv(Serve *sctx, Req *req);
status Req_Handle(Serve *sctx, Req *req);
status Req_Process(Serve *sctx, Req *req);
