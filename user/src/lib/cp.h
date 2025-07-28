#include "sys.h"
#include "str.h"

#define BUF_SIZE 4096

int copy(const char* srcpath, const char* destpath) {
    int src = sys_open(srcpath, O_RDONLY, 0755);
    if (src < 0) return 1;

    int dst = sys_open(destpath, O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (dst < 0) return 1;

    char buffer[BUF_SIZE];
    ssize_t bytes;
    while ((bytes = sys_read(src, buffer, BUF_SIZE)) > 0) {
        sys_write(dst, buffer, bytes);
    }
    sys_write(STDOUT, srcpath, strlen(srcpath));
    sys_write(STDOUT," -> ", 4);
    sys_write(STDOUT, destpath, strlen(destpath));
    sys_write(STDOUT, "\n", 1);

    sys_close(src);
    sys_close(dst);
    return 0;
}