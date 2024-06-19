#include "external.h"
#include "filestore.h"

SCursor* SCursor_Make(MemCtx *m, String *s){
    SCursor *sc = (SCursor *) MemCtx_Alloc(m, sizeof(SCursor));
    sc->s = s;
    sc->seg = sc->s;

    return sc;
}

status Range_Set(Range *range, String *s){
    memset(range, 0, sizeof(Range));
    range->start.s = range->start.seg = range->end.s = range->end.seg = s;
    return SUCCESS;
}

status Range_Reset(Range *range, int anchor){
    range->compare = 0;
    if(range->state == COMPLETE){
        range->start.position = range->end.position;
        range->start.seg = range->end.seg;
        if(range->start.localPosition == range->start.seg->length){
            range->start.seg = range->start.seg->next;
        }
        range->start.position++;
        SCursor_SetLocals(&(range->start));
    }

    range->state = READY;
    if(anchor){
        range->start.state = READY;
    }else{
        range->start.state = PROCESSING;
    }

    return range->state;
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
    SCursor *start = &(range->start); 
    SCursor *end = &(range->end); 
    if(start->seg == NULL || start->seg->length < 1){
        return NOOP;
    }
    Range_Reset(range, anchor);
    byte c;
    int i = range->start.position;
    int startPosition = i;
    String *seg = start->seg;
    while(seg != NULL){
        for(
            c = seg->bytes[i];
            i < seg->length;
            i++, c = seg->bytes[i]
        ){
            if(search->bytes[range->compare] == c){
                if(start->state == READY){
                    start->position = i;
                    start->seg = seg;
                }
                range->compare++;
                start->state = PROCESSING;
                if(range->compare == search->length){
                    end->position = i;
                    end->seg = seg;
                    range->length = i - start->position;
                    range->state = COMPLETE;
                    break;
                }
            }else{
                if(anchor){
                    start->state = anchor ? READY :  PROCESSING;
                    return start->state;
                }else{
                    start->state = anchor ? READY :  PROCESSING;
                    start->position = startPosition;
                    range->compare = 0;
                }
            }

        }
        end->seg = seg;
        seg = seg->next;
    }

    SCursor_SetLocals(start);
    SCursor_SetLocals(end);

    end->position = start->position + range->length;
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
