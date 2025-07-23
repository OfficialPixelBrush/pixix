#include "lib/sys.h"
#include "lib/err.h"
#include "lib/num.h"

int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    if (argcount < 2) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    printerr(sys_chdir(args[1]));
}
