#define STRING_CHUNK_SIZE 1024

typedef unsigned char uchar;
typedef uint64_t i64;
typedef int status;
typedef int type;
typedef uchar byte;
struct serve_ctx;
struct serve_req;
struct mem_ctx;
struct mem_slab;

enum types {
    TYPE_MEMCTX,
    TYPE_MEMSLAB,
};

enum status_types {
    SUCCESS = 0,
    ERROR = 1
};

#include <error.h>
#include <mem.h>

typedef struct serve_ctx {
    int epoll_fd;
} ServeCtx;

ServeCtx *ServeCtx_Make();
ServeCtx *ServeCtx_Serve(int port);

typedef struct string {
    char *content;
    i64 length;
    i64 allocated;
    struct string *next;
} String;

String *String_Make(uchar *content);
status String_Add(String *a, String *additional);
i64 String_Length(String *s);

typedef struct serve_req {
    String *path;
    String *content;
    String *response;
    i64 out_position;
} ServeReq;
