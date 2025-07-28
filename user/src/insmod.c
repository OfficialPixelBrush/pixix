#include "lib/sys.h"
#include "lib/err.h"
#include "lib/mod.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        sys_write(STDOUT, "Not enough arguments!\n", 22);
        sys_exit(1);
    }
    printerr(insmod(argv[1]));
    sys_exit(0);
}
