#include "lib/sys.h"
#include "lib/str.h"
#include "lib/err.h"
#include "img/pixix.h"
#include "lib/concat.h"

/*

argv[0] = install
argc[1] = operation (mod,diskln,help)

*/

const char * prgList[] = {
    "bin/cd", "bin/pitch", "bin/ping", "bin/insmod",
    "mkswap", "bin/ln", "bin/cp", "ifconfig",
    "udhcpc", "route", "fdisk", "wget",
    "mkfs.ext2", "bin/mkdir"
};

int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    if (argc < 2) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    /*
    sys_write(STDOUT,pixix_logo,strlen(pixix_logo));
    sys_write(STDOUT,"\x1b[0m\n",5);
    */
    //if (strcmp(args[1],"ln")) {
    int prgCount = sizeof(prgList) / sizeof(prgList[0]);
    for (int i = 0; i < prgCount; i++) {
        size_t src_alloc_size;
        char *src = strcat("/mnt/", prgList[i], &src_alloc_size);
        if (!src) sys_exit(1);

        size_t dest_alloc_size;
        char *dest = strcat("/", prgList[i], &dest_alloc_size);
        if (!dest) sys_exit(1);
        
        printerr(sys_symlink(src, dest));

        sys_write(STDOUT, src, strlen(src));
        sys_write(STDOUT, " -> ", 4);
        sys_write(STDOUT, dest, strlen(dest));
        sys_write(STDOUT, "\n", 1);

        printerr(sys_munmap(src, src_alloc_size));
        printerr(sys_munmap(src, dest_alloc_size));
    }
    //}
    sys_exit(0);
}