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
