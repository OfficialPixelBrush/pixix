#include <sys/types.h>

// Central system library
#ifndef SYS_H
#define SYS_H

#define STDIN 0
#define STDOUT 1

#define P_ALL 0
#define WEXITED 4

#define TIOCSPGRP 0x5410

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

struct stat {
    unsigned short st_dev;
    unsigned short __pad1;
    unsigned long  st_ino;
    unsigned short st_mode;
    unsigned short st_nlink;
    unsigned short st_uid;
    unsigned short st_gid;
    unsigned short st_rdev;
    unsigned short __pad2;
    unsigned long  st_size;
    unsigned long  st_blksize;
    unsigned long  st_blocks;
    unsigned long  st_atime;
    unsigned long  st_atime_nsec;
    unsigned long  st_mtime;
    unsigned long  st_mtime_nsec;
    unsigned long  st_ctime;
    unsigned long  st_ctime_nsec;
    unsigned long  __unused4;
    unsigned long  __unused5;
};

int sys_exit(int status);
int sys_fork();
int sys_read(unsigned int fd, void *buf, unsigned int count);
int sys_write(unsigned int fd, const void *buf, unsigned int count);
int sys_open(const void *buf, int flags, int mode);
int sys_close(unsigned int fd);
int sys_execve(const char *filename, char *const argv[], char *const envp[]);
int sys_chdir(const char *filename);
int sys_mknod(const char *filename, int mode, unsigned int dev);
int sys_getpid();
int sys_mount(const char *source, const char *target, const char *filesystemtype, unsigned long mountflags, const void *data);
int sys_umount(const char *source);
int sys_mkdir(const char *name, int mode);
int sys_ioctl(unsigned int fd, int request, const void *argp);
int sys_setpgid(unsigned int pid, unsigned int pgid);
int sys_setsid();
int sys_symlink(const char *oldpath, const char *newpath);
int sys_fstat(unsigned int fd, struct stat *statbuf);
int sys_sysinfo(void *info);
int sys_uname(void *buf);
int sys_init_module(void *umod, unsigned long len, const char *uargs);
int sys_delete_module(const char *name_user, unsigned int flags);
int sys_getdents(unsigned int fd, void *dirp, unsigned int count);
int sys_waitid(int idtype, int id, void *infop, int options);
#endif