#include "external.h"
#include "filedb.h"

void Fatal(char *msg, type t){
    printf("Fatal Error:");
    printf("%s\n", msg);
    exit(13);
}
