#include "lib/sys.h"
#include "lib/err.h"
#include "lib/str.h"

void main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    if (argc < 4) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    int flags = 0;
    char * extra = "";
    // Check for read-only FS
    if (strcmp(args[3],"iso9660") == 0) {
        flags |= MS_RDONLY;
        extra = "mode=755";
    }
    printerr(sys_mount(args[1], args[2], args[3], flags, extra));
    sys_exit(0);
}