#include "lib/sys.h"
#include "lib/err.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    printerr(sys_chdir(argv[1]));
}
