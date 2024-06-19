typedef struct serve_req {
    status state;
    int fd;
    int direction;
    MemCtx *m;
    byte method;
    String *path;
    String *_shelf;
    String *id;
    String *body;
    String *response;
    SCursor *cursor;
} Req;

Req *Req_Make();
status Req_Parse(Serve *sctx, Req *req, String *s);
status Req_SetError(Serve *sctx, Req *req, String *msg);
status Req_Recv(Serve *sctx, Req *req);
status Req_Handle(Serve *sctx, Req *req);
status Req_Process(Serve *sctx, Req *req);

char *Method_ToString(int method);
