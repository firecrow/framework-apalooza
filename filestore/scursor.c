#include "external.h"
#include "filestore.h"

SCursor* SCursor_Make(MemCtx *m, String *s){
    SCursor *sc = (SCursor *) MemCtx_Alloc(m, sizeof(SCursor));
    sc->s = s;
    sc->seg = sc->s;

    return sc;
}

status SCursor_Prepare(SCursor *sc, i64 length){
    i64 remaining = sc->seg->length - sc->localPosition;
    if(remaining < length){
        sc->immidiateLength = remaining;
    }else{
        sc->immidiateLength = length;
    }

    return SUCCESS;
}

status SCursor_Incr(SCursor *sc, i64 length){
    i64 remaining = length;
    i64 local;
    while(remaining > 0){
        local = sc->seg->length - sc->localPosition;
        if(local > remaining){
            sc->localPosition += remaining;
            sc->position += remaining;
            remaining = 0;
            continue;
        }else{
            remaining -= local;
            sc->position += local;
            sc->seg = sc->seg->next;
        }
    }

    if(sc->seg == NULL && sc->position == String_Length(sc->s)){
        sc->state = COMPLETE;
        return sc->state;
    }

    return SUCCESS;
}
