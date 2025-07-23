#include "lib/sys.h"
#include "lib/err.h"

void main(int argc, char *argv[]) {
    if (argc < 2) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    printerr(sys_umount(argv[1]));
    sys_exit(0);
}