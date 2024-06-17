#define MEM_SLAB_SIZE 4096

typedef struct mem_slab {
    byte bytes[MEM_SLAB_SIZE];
    void *addr;
    struct mem_slab *next;
} MemSlab;

typedef struct mem_ctx {
    MemSlab *start_sl;
} MemCtx;

size_t MemCount();
void *MemCtx_Alloc(MemCtx *m, size_t s);
MemCtx *MemCtx_Make();
status MemCtx_Free(MemCtx *m);
void *MemSlab_GetStart(MemSlab *sl);
MemSlab *MemSlab_Make(MemCtx *m);
size_t MemSlab_Available(MemSlab *sl);
void *MemSlab_Alloc(MemSlab *sl, size_t s);
