#include "lib/sys.h"
#include "lib/str.h"
#include "lib/err.h"

// Based on example in https://linux.die.net/man/2/getdents64

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc < 2) {
        sys_write(STDOUT, "Not enough arguments!\n", 22);
        sys_exit(1);
    }
    int fd = sys_open(argv[1], O_RDONLY | O_DIRECTORY, 0 );
    if (fd < 0) printerr(fd);
    
    char buf[BUFFER_SIZE];
    
    while(1) {
        int nread = sys_getdents(fd, buf, BUFFER_SIZE);
        if (nread < 0) printerr(nread);
        if (nread == 0) break;

        for (int bpos = 0; bpos < nread;) {
            struct linux_dirent *d = (struct linux_dirent *) (buf + bpos);
            uint8_t d_type = *(buf + bpos + d->d_reclen - 1);
            if (d->d_name[0] != '.') {
                sys_write(STDOUT, d->d_name, strlen(d->d_name));
                sys_write(STDOUT, " ", 1);
            }
            bpos += d->d_reclen;
        }
    }
    sys_write(STDOUT, "\n", 1);
    sys_exit(0);
}