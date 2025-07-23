#include "lib/sys.h"
#include "lib/err.h"

int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    if (argcount < 3) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    printerr(sys_symlink(args[1], args[2]));
}
