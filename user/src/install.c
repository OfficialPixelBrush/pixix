#include "lib/sys.h"
#include "lib/str.h"
#include "lib/err.h"
#include "img/pixix.h"
#include "lib/concat.h"
#include "lib/mem.h"
#include "lib/mod.h"
#include "lib/cp.h"

const char * prgList[] = {
    "cd", "pitch", "ping", "insmod",
    "ln", "cp", "mkdir"
};

const char * modList[] = {
    "/linux.mod", "/normal.mod",
    "/modinfo.sh", "/moddep.lst",
    "/boot.mod", "/search.mod",
    "/ext2.mod", "/echo.mod",
    "/search_fs_uuid.mod",
    "/terminal.mod", "/part_msdos.mod",
    "/multiboot.mod", "/configfile.mod"
};

const char * ext4List[] = {
    "/fs/mbcache.ko", "/fs/jbd2/jbd2.ko",
    "/lib/crc16.ko", "/fs/ext4/ext4.ko"
};

int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    if (argcount < 2) {
        sys_write(STDOUT, "Too few arguments!\n", 19);
        sys_exit(1);
    }
    // Print Logo
    size_t n = sizeof(pixix_logo) / sizeof(pixix_logo[0]);
    for (int i = 0; i < n; i++) {
        if (i < n) {
            sys_write(STDOUT,pixix_logo[i],strlen(pixix_logo[i]));
            sys_write(STDOUT,"\x1b[0m ",6);
        }
        sys_write(STDOUT,"\n ",1);
    }
    // Symlink useful utilities
    if (strcmp(args[1],"link")==0) {
        int prgCount = sizeof(prgList) / sizeof(prgList[0]);
        for (int i = 0; i < prgCount; i++) {
            size_t src_alloc_size;
            char *src = strcat("/mnt/bin/", prgList[i], &src_alloc_size);
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
    }
    // Init ext4 modules
    if (strcmp(args[1],"ext4")==0) {
        if (argcount < 3) {
            sys_write(STDOUT, "Need src dir (mod)!\n", 18);
            sys_exit(1);
        }
        size_t outsize;
        char *newDir;

        int ext4Count = sizeof(ext4List) / sizeof(ext4List[0]);
        for (int i = 0; i < ext4Count; i++) {
            newDir = strcat(args[2],ext4List[i],&outsize);
            insmod(newDir);
            printerr(sys_munmap(newDir, outsize));
        }
    }
    // Grub setup
    if (strcmp(args[1],"grub")==0) {
        if (argcount < 4) {
            sys_write(STDOUT, "install grub (/disk) (/mnt/grubmod)\n", 40); 
            sys_exit(1);
        }

        size_t outsize;
        size_t outsize2;
        size_t outsize3;
        char *catString;
        char *catString2;
        char *catString3;

        // Creating necessary directories
        catString = strcat(args[2],"/boot",&outsize);
        sys_mkdir(catString, 0755);
        printerr(sys_munmap(catString, outsize));

        catString = strcat(args[2],"/boot/grub",&outsize);
        sys_mkdir(catString, 0755);
        printerr(sys_munmap(catString, outsize));

        catString = strcat(args[2],"/boot/grub/i386-pc",&outsize);
        sys_mkdir(catString, 0755);
        printerr(sys_munmap(catString, outsize));

        int modCount = sizeof(modList) / sizeof(modList[0]);
        for (int i = 0; i < modCount; i++) {
            catString = strcat(args[3],modList[i],&outsize);
            catString2 = strcat(args[2],"/boot/grub/i386-pc",&outsize2);
            catString3 = strcat(catString2,modList[i],&outsize3);
            copy(catString,catString3);
            printerr(sys_munmap(catString , outsize ));
            printerr(sys_munmap(catString2, outsize2));
            printerr(sys_munmap(catString3, outsize3));
        }
    }
    sys_exit(0);
}