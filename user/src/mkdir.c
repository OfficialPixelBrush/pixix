#include "lib/sys.h"
#include "lib/err.h"
#include "lib/num.h"

int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    //int mode = 0755;
    if (argcount < 2) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    // If we have exactly 2 args,
    // we don't care about mode
    } /*else if (argcount > 2) {
        mode = readoct(args[2]);
    }*/

    // We don't care about permissions *that* much
    printerr(sys_mkdir(args[1], 0755));
}
