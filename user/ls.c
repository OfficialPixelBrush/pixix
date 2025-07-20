#include "sys.h"
#include "lib.h"

#define BUF_SIZE 8192

int main(int argc, char *argv[]) {
    int fd;
    if (argc <= 1) {
        fd = sys_open(".", O_RDONLY | O_DIRECTORY, 0);
    } else {
        fd = sys_open(argv[1], O_RDONLY | O_DIRECTORY, 0);
    }
    if (fd < 0) errprint(fd);
    
    char buf[BUF_SIZE];
    int nread = sys_getdents64(fd,buf,BUF_SIZE);
    if (nread < 0) errprint(nread);

    int bpos = 0;
    while (bpos < nread) {
        struct linux_dirent64 *d = (struct linux_dirent64*)(buf + bpos);
        sys_write(STDOUT, d->d_name, strlen(d->d_name));
        sys_write(STDOUT, "\n", 1);
        bpos += d->d_reclen;
    }

    sys_exit(0);
}

    /*
    int fd = sys_open(".", O_RDONLY | O_DIRECTORY);

    while ((nread = syscall(SYS_getdents64, fd, buffer, sizeof(buffer))) > 0) {
        for each dirent in buffer {
            // Use fstatat(fd, dirent->d_name, &statbuf, 0) to get details if needed
            printf("%s\n", dirent->d_name);
        }
    }

    close(fd);
    */