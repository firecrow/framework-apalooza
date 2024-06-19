typedef status (*ParseFunc)(struct serve_req *req, Range *range);
ParseFunc *Parser_MakeChain(MemCtx *m, int count, ...);

status Parse_Method(struct serve_req *req, Range *range);
status Parse_Space(struct serve_req *req, Range *range);
status Parse_Path(struct serve_req *req, Range *range);
