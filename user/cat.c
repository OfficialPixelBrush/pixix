#include "lib/sys.h"

#define MAX_CHARS 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        sys_write(STDOUT, "Not enough arguments!\n", 22);
        sys_exit(1);
    }
    int fd = sys_open(argv[1], O_RDONLY, 0);
    if (fd < 0) {
        sys_write(STDOUT, "Couldn't read file!\n", 20);
        sys_exit(1);
    }

    int bytes_read = 1;
    char buf[MAX_CHARS];
    while(bytes_read > 0) {
        bytes_read = sys_read(fd,buf,MAX_CHARS);
        sys_write(STDOUT,buf,bytes_read);
    }
    sys_close(fd);
    sys_exit(0);
}