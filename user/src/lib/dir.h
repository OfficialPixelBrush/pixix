// Library to simplify interacting with directories

#ifndef DIR_H
#define DIR_H

struct linux_dirent {
    ino_t  d_ino;
    off_t  d_off;
    unsigned short d_reclen;
    char     d_name[];
};

enum linux_dirent_type {
    DT_UNKNOWN = 0,
    DT_FIFO    = 1,
    DT_CHR     = 2,
    DT_DIR     = 4,
    DT_BLK     = 6,
    DT_REG     = 8,
    DT_LNK     = 10,
    DT_SOCK    = 12,
    DT_WHT     = 14 // whiteout (used on some filesystems like unionfs)
};
#endif