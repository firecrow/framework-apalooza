#include "external.h"
#include "filestore.h"

SCursor* SCursor_Make(MemCtx *m, String *s){
    SCursor *sc = (SCursor *) MemCtx_Alloc(m, sizeof(SCursor));
    sc->s = s;
    sc->seg = sc->s;

    return sc;
}

status SCursor_Reset(SCursor *sc){
    String *s = sc->s;
    memset(sc, 0, sizeof(SCursor));
    sc->s = s;
    sc->seg = s;
    return SUCCESS;
}

status SCursor_SetLocals(SCursor *sc){
    sc->segIdx = sc->position / STRING_CHUNK_SIZE;
    sc->localPosition = sc->position % STRING_CHUNK_SIZE;
    return SUCCESS;
}


status SCursor_Find(Range *range, String *search, int anchor){
    SCursor start = range->start; 
    SCursor end = range->end; 
    if(start->s == NULL || start->s->length < 1){
        return NOOP;
    }
    start->compare = 0;
    byte c;
    int i = 0;
    i64 start = start->position;
    String *seg = start->seg;
    while(seg != NULL){
        for(
            c = seg->bytes[i];
            i < seg->length;
            i++, c = seg->bytes[i]
        ){
            if(search->bytes[start->compare] == c){
                if(start->state == READY){
                    start->position = i;
                    start->seg = seg;
                }
                start->compare++;
                start->state = PROCESSING;
                if(start->compare == (search->length-1)){
                    end->position = i;
                    end->seg = seg;
                    if(anchor == POSITION_CONTAINS){
                        range->state = COMPLETE;
                        break;
                    }else if(anchor == POSITION_START){
                        if(start->position == start){
                            range->state = COMPLETE;
                            break;
                        }
                    }else if(anchor == POSITION_END){
                        if(start->position == String_Length(start->s) - search->length){
                            range->state = COMPLETE;
                            break;
                        }
                    }
                }
                continue;
            }

            if(anchor == POSITION_START){
                start->state = READY;
                return start->state;
            }else{
                start->state = READY;
                start->position = 0;
                start->compare = 0;
            }
        }
        seg = seg->next;
    }

    SCursor_SetLocals(start);
    SCursor_SetLocals(end);
    return range->state;
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
