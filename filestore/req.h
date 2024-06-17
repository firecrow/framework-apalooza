typedef struct serve_req {
    byte method;
    status state;
    String *_shelf;
    String *id;
    String *body;
    String *response;
    i64 out_position;
} ServeReq;
