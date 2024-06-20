#include "external.h"
#include "filestore.h"

static status parse_Method(Req *req, Range *range){
    int i = 0;
    int start = range->start.position;
    while(methodTk[i] != NULL && range->state != COMPLETE){
        if(SCursor_Find(range, methodTk[i], TRUE) == COMPLETE){
            req->method = methods[i];
            return SUCCESS;
        }
        i++;
    }

    return ERROR;
}

Parser *Parser_MakeMethod(Sctx *sctx, Req *req){
    Parser *prs = (Parser *) MemCtx_Alloc(m, sizeof(Parser));
    char *method = sctx->methods[0];
    
    Match **matches = (Match **)Array_MakeFrom(req->m, Array_Length(sctx->methods)); 
    while(method !== NULL){
        matches[i] = Match_Make(req->m, String_From(res->m, method));
    }
    prs->matches = matches;
    prs->func = parse_Method;

    return prs;
}

status Parse_Space(Req *req, Range *range){
    if(SCursor_Find(range, space_tk, TRUE) == COMPLETE){
        return SUCCESS;
    }
    return ERROR;
}

status Parse_Path(Req *req, Range *range){
    if(SCursor_Find(range, space_tk, FALSE) == COMPLETE){
        req->path = String_FromRange(req->m, range);
        return SUCCESS;
    }

    return ERROR;
}

status Parse_HttpV(Req *req, Range *range){
    return ERROR;
}

status Parse_Colon(Req *req, Range *range){
    return ERROR;
}

status Parse_LineEnd(Req *req, Range *range){
    return ERROR;
}

status Parse_DoubleLineEnd(Req *req, Range *range){
    return ERROR;
}

status Parse_Json(Req *req, Range *range){
    return ERROR;
}
