#include "external.h"
#include "filestore.h"

ParseFunc *Parser_MakeChain(MemCtx *m, int count, ...){
	va_list args;
    va_start(args, count);
    
    ParseFunc *parsers = (ParseFunc *)MemCtx_Alloc(m, sizeof(ParseFunc)*(count+1));
    for(int i = 0; i < count; i++){
        parsers[i] = va_arg(args, ParseFunc);
    }
    parsers[count] = NULL;

    return parsers;
}

status Parse_Method(Req *req, Range *range){
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
