#include <unistd.h>

#ifndef SYS_H
#define SYS_H

#define STDIN 0
#define STDOUT 1

enum OC_ACCESS {
    O_ACCMODE   = 0003,
    O_RDONLY    = 00,
    O_WRONLY    = 01,
    O_RDWR      = 02,
    O_CREAT     = 0100,
    O_EXCL      = 0200,
    O_NOCTTY    = 0400,
    O_TRUNC     = 01000,
    O_APPEND    = 02000,
    O_NONBLOCK  = 04000,
    O_NDELAY    = 04000,  // same as O_NONBLOCK
    O_SYNC      = 010000, // specific to ext2 fs and block devices
    FASYNC      = 020000, // fcntl, for BSD compatibility
    O_DIRECT    = 040000, // direct disk access hint - currently ignored
    O_LARGEFILE = 0100000,
    O_DIRECTORY = 0200000, // must be a directory
    O_NOFOLLOW  = 0400000  // don't follow links
};

enum OC_PERMS {
    S_ISUID = 04000,  // set user ID on execution
    S_ISGID = 02000,  // set group ID on execution
    S_ISVTX = 01000,  // sticky bit
    S_IRUSR = 00400,  // read by owner (S_IREAD)
    S_IWUSR = 00200,  // write by owner (S_IWRITE)
    S_IXUSR = 00100,  // execute/search by owner (S_IEXEC)
    S_IRGRP = 00040,  // read by group
    S_IWGRP = 00020,  // write by group
    S_IXGRP = 00010,  // execute/search by group
    S_IROTH = 00004,  // read by others (R_OK)
    S_IWOTH = 00002,  // write by others (W_OK)
    S_IXOTH = 00001   // execute/search by others (X_OK)
};


enum MOUNT_FLAGS {
    MS_MGC_MSK = 0xC0ED,
    MS_RDONLY = 1,
    MS_NOSUID = 2,
    MS_NODEV = 4,
    MS_NOEXEC = 8,
    MS_SYNCHRONOUS = 16,
    MS_REMOUNT = 32,
    MS_MANDLOCK = 64,
    MS_NOATIME = 1024,
    MS_NODIRATIME = 2048,
    MS_BIND = 4096,
    MS_REC = 16384,
    MS_VERBOSE = 32768,
    MS_ACTIVE = (1<<30),
    MS_NOUSER = (1<<31)
};

struct linux_dirent64 {
    unsigned long   d_ino;
    long            d_off;
    unsigned short  d_reclen;
    unsigned char   d_type;
    char            d_name[];
};

int sys_exit(int status);
int sys_fork();
ssize_t sys_read(int fd, void *buf, size_t count);
ssize_t sys_write(int fd, const void *buf, size_t count);
int sys_open(const void *buf, int flags, int mode);
int sys_close(int fd);
int sys_execve(const char *filename, char *const argv[], char *const envp[]);
int sys_mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);
int sys_mkdir(const char *name, int mode);
int sys_sysinfo(void *info);
int sys_uname(void *buf);
int sys_getdents64(int fd, char* buf, int nbytes);
int sys_waitid(int idtype, int id, void *infop, int options);
#endif