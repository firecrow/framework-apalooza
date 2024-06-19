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
struct strcursor_range;

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define TRUE 1
#define FALSE 0

enum types {
    TYPE_MEMCTX,
    TYPE_MEMSLAB,
    TYPE_REQ,
    TYPE_SERVECTX,
    TYPE_TESTSUITE,
};

enum methods {
    METHOD_UNKOWN = 0,
    METHOD_GET = 1,
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

enum positions {
    POSITION_CONTAINS = 0,
    POSITION_START = 1,
    POSITION_END,
};

char *State_ToString(status state);

#define COMPLETE SUCCESS
#define TEST_OK READY

#include "error.h"
#include "log.h"
#include "mem.h"
#include "string.h"
#include "tokens.h"
#include "scursor.h"
#include "serve.h"
#include "req.h"
