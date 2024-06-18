#define STRING_CHUNK_SIZE 1024

typedef unsigned char uchar;
typedef uchar boolean;
typedef uint64_t i64;
typedef int status;
typedef int type;
typedef uchar byte;
struct serve_ctx;
struct serve_req;
struct mem_ctx;
struct mem_slab;

#define TRUE 1
#define FALSE 0

enum types {
    TYPE_MEMCTX,
    TYPE_MEMSLAB,
    TYPE_REQ,
    TYPE_SERVECTX,
};

enum methods {
    METHOD_GET,
    METHOD_SET,
    METHOD_UPDATE,
    METHOD_DELETE,
};

enum status_types {
    READY = 0,
    SUCCESS,
    ERROR,
    NOOP,
    INCOMING,
    PROCESSING,
    RESPONDING,
};

#define COMPLETE SUCCESS

#include "error.h"
#include "mem.h"
#include "string.h"
#include "scursor.h"
#include "serve.h"
#include "req.h"
