#include "lib/sys.h"
#include "lib/str.h"
#include "lib/err.h"
#include "lib/num.h"

// Based on example in https://linux.die.net/man/2/getdents64

#define BUFFER_SIZE 1024

int main() {
    int fd = sys_open(".", O_RDONLY | O_DIRECTORY, 0 );
    if (fd < 0) printerr(fd);

    char buf[BUFFER_SIZE];
    int nread, bpos;
    for ( ; ; ) {
        nread = sys_getdents64(fd, buf, BUFFER_SIZE);
        if (nread < 0) printerr(nread);
        if (nread == 0) break;

        for (bpos = 0; bpos < nread;) {
            struct linux_dirent64 *d = (struct linux_dirent64 *) (buf + bpos);
            sys_write(STDOUT, d->d_name, strlen(d->d_name));
            sys_write(STDOUT, "\n", 1);
            bpos += d->d_reclen;
        }
    }
    sys_exit(0);
}