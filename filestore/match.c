#include "external.h"
#include "filestore.h"

Match *Match_Make(MemCtx *m, String *s){
    Match *mt = (Match *)Alloc(m, sizeof(Match));
    mt->type = TYPE_STRINGMATCH;
    mt->s = s;
    return mt;
}

void Match_Reset(Match *mt){
    mt->position = 0;
    mt->state = READY;
}

status Match_Feed(Match *mt, uchar c){
    if(mt->s->bytes[mt->position] == c){
        if(mt->position == mt->s->length){
            mg->state = COMPLETE;
        }else{
            mt->state = PROCESSING;
        }
    }else{
        Match_Reset(mt);
    }
    return mt->state;
}
