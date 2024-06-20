typedef status (*ParseFunc)(Parser *parser, struct serve_req *req, Range *range);
typedef status (*ParserMaker)(Serve *sctx, Req *req);
ParseFunc *Parser_MakeChain(MemCtx *m, int count, ...);

typedef struct parser {
    Match *matches;
    ParseFunc func;
} Parser;

status Parse_Method(struct serve_req *req, Range *range);
status Parse_Space(struct serve_req *req, Range *range);
status Parse_Path(struct serve_req *req, Range *range);
