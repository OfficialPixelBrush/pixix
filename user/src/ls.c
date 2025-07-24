#include "lib/sys.h"
#include "lib/str.h"
#include "lib/err.h"
#include "lib/dir.h"

// Based on example in https://linux.die.net/man/2/getdents64

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    char *dest = 0;
    char flag = 'o';
    if (argc < 2) {
        dest = ".\0";
    } else if (argc == 2) {
        dest = argv[1];
    } else if (argc >= 3) {
        flag = *argv[1];
        dest = argv[2];
    }
    int fd = sys_open(dest, O_RDONLY | O_DIRECTORY, 0 );
    if (fd < 0) printerr(fd);
    
    char buf[BUFFER_SIZE];
    
    while(1) {
        int nread = sys_getdents(fd, buf, BUFFER_SIZE);
        if (nread < 0) printerr(nread);
        if (nread == 0) break;

        for (int bpos = 0; bpos < nread;) {
            struct linux_dirent *d = (struct linux_dirent *) (buf + bpos);
            char d_type = *(buf + bpos + d->d_reclen - 1);
            // ignore symlinks unless we ask for them
            if (d_type == DT_LNK && flag != 's') {
                goto skip;
            }
            // Ignore hidden unless we ask for them
            if (d->d_name[0] == '.' && flag != 'h') {
                goto skip;
            }
            sys_write(STDOUT, d->d_name, strlen(d->d_name));
            sys_write(STDOUT, " ", 1);
            skip:
            bpos += d->d_reclen;
        }
    }
    sys_write(STDOUT, "\n", 1);
    sys_exit(0);
}