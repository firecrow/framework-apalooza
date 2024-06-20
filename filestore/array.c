#include "external.h"
#include "filestore.h"

void *Array_Length(void **arr){
    Unit *u = *((Unit **)arr);
    int i = 0;
    while(u != NULL){
        i++;
    };
    return i;
}

void *Array_MakeFrom(MemCtx *m, int count, ...){
	va_list args;
    va_start(args, size);
    
    Unit **slab = (Unit **)MemCtx_Alloc(m, size*(count+1));
    for(int i = 0; i < count; i++){
        slab[i] = va_arg(args, Unit*);
    }
    slab[count] = NULL;

    return slab;
}
