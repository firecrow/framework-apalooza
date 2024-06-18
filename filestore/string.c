#include "external.h"
#include "filestore.h"

static String *string_Init(MemCtx *m){
    return (String *)MemCtx_Alloc(m, sizeof(String));
}

String *String_Make(MemCtx *m, uchar *bytes){
    String *s = string_Init(m); 
    String_Add(m, s, bytes);

    return s;
}


status String_Add(MemCtx *m, String *a, uchar *bytes) {
    size_t l = strlen((char *)bytes);
    size_t remaining = l;
    size_t copy_l = remaining;

    String *seg = a, *tail = NULL;
    while(a->next != NULL){
        seg = a->next;
    }

    /* copy the initial chunk */
    if(copy_l > (STRING_CHUNK_SIZE - seg->length)){
        copy_l = (STRING_CHUNK_SIZE - seg->length);
    }

    if(seg->bytes == NULL){
        seg->bytes = (uchar *)MemCtx_Alloc(m, copy_l+1);
        memcpy(seg->bytes, bytes, copy_l);
        remaining -= copy_l;
    }

    /* if more than a string seg remains, make a new one */
    while(remaining > STRING_CHUNK_SIZE){
        String *next = string_Init(m);
        next->bytes = (uchar *)MemCtx_Alloc(m, STRING_CHUNK_SIZE+1);
        memcpy(next->bytes, bytes, STRING_CHUNK_SIZE);
        bytes += STRING_CHUNK_SIZE;

        if(seg == NULL){
            seg = tail = next;
        }else{
            tail->next = next;
            tail = next;
        }
        remaining -= STRING_CHUNK_SIZE;
    }

    /* if any remains, make a final seg */
    if(remaining > 0){
        String *next = string_Init(m);
        next->bytes = (uchar *)MemCtx_Alloc(m, remaining+1);
        memcpy(next->bytes, bytes, remaining);


        if(seg == NULL){
            seg = tail = next;
        }else{
            tail->next = next;
            tail = next;
        }
    }

    return SUCCESS;
}

i64 String_Length(String *s) {
    String *tail = s;
    i64 length = 0;
    while(tail != NULL){
        length += tail->length; 
        tail = s->next;
    }
    return length;
}
