#include "external.h"
#include "filestore.h"

int main(){
    MemCtx *m = MemCtx_Make();
    void *a = MemCtx_Alloc(m, 14);
    printf("memcount: %ld\n", MemCount()); 
    MemCtx_Free(m);
    printf("memcount after free: %ld\n", MemCount()); 
    return 0;
}
