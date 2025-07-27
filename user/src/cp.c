#include "lib/sys.h"

#define BUF_SIZE 4096

// TODO: Redo with sendfile
int main(int argc, char *argv[]) {
    char **args = argv;
    if (argc < 3) {
        sys_write(STDOUT, "Not enough arguments!\n", 22);
        sys_exit(1);
    }

    int src = sys_open(args[1], O_RDONLY, 0755);
    if (src < 0) sys_exit(1);

    int dst = sys_open(args[2], O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (dst < 0) sys_exit(1);

    char buffer[BUF_SIZE];
    ssize_t bytes;
    while ((bytes = sys_read(src, buffer, BUF_SIZE)) > 0) {
        sys_write(dst, buffer, bytes);
    }

    sys_close(src);
    sys_close(dst);
    sys_exit(0);
}