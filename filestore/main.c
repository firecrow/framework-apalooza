#include "external.h"
#include "filestore.h"

#define servecmd "serve="
#define testcmd "serve"

static status handle(MemCtx *m, char *arg){
    int servecmd_l = strlen(servecmd);
    if(strncmp(arg, servecmd, strlen(servecmd)) == 0){
        arg += servecmd_l;
        printf("port is %s\n", arg);

        int port = atoi(arg);
        if(port == 0){
            Error("unable to find port for serve cmd");
            return ERROR;
        }

        Serve *sctx = Serve_Make(m);
        return Serve_Run(sctx, port);
    }else if(strncmp(arg, testcmd, strlen(testcmd)) == 0){
        printf("Run tests");
        return SUCCESS;
    }

    return NOOP;
}

int main(int argc, char **argv){
    MemCtx *m = MemCtx_Make();

    if(argc == 1){
        printf("%s [test,serve=port]", argv[0]);
        exit(1);
    }
    
    if(argc > 1){
        for(int i = 1; i < argc; i++){
            if(handle(m, argv[i]) == ERROR){
                exit(1);
            }
        }
    }

    return 0;
}
