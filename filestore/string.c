#include "external.h"
#include "filestore.h"

String *String_Make(MemCtx *m, uchar *bytes){
    String *s, *tail;


    return s;
}

status String_Add(String *a, String *bytes) {
    size_t l = strlen(bytes);
    size_t remaining = l;
    size_t copy_l = remaining;

    String *seg = a;
    while(a->next != NULL){
        seg = a->next;
    }

    /* copy the initial chunk */
    if(copy_l > (STRING_CHUNK_SIZE - seg->length)){
        copy_l = (STRING_CHUNK_SIZE - seg->length);
    }

    uchar *p = a->bytes+a->length;
    memcpy(p, bytes, copy_l);
    remaining -= copy_l;

    /* if more than a string seg remains, make a new one */
    while(remaining > STRING_CHUNK_SIZE){
        String next = (String *) Alloc(m, sizeof(String));
        next->bytes = (uchar *) Alloc(m, STRING_CHUNK_SIZE+1);
        memcpy(next->bytes, bytes, STRING_CHUNK_SIZE);
        bytes += STRING_CHUNK_SIZE

        if(s == NULL){
            s = tail = next;
        }else{
            tail->next = next;
            tail = next;
        }
        remaining -= STRING_CHUNK_SIZE;
    }

    /* if any remains, make a final seg */
    if(remaining > 0){
        String next = (String *) Alloc(m, sizeof(String));
        next->bytes = (uchar *) Alloc(m, remaining+1);
        memcpy(next->bytes, bytes, remaining);

        if(s == NULL){
            s = tail = next;
        }else{
            tail->next = next;
            tail = next;
        }
    }

    return SUCCESS;
}

i64 String_Length(String *s) {
    return 0;
}
