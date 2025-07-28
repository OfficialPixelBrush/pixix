#include "lib/sys.h"
#include "lib/cp.h"

#define BUF_SIZE 4096

// TODO: Redo with sendfile
int main(int argc, char *argv[]) {
    char **args = argv;
    if (argc < 3) {
        sys_write(STDOUT, "Not enough arguments!\n", 22);
        sys_exit(1);
    }
    copy(args[1],args[2]);
    sys_exit(0);
}