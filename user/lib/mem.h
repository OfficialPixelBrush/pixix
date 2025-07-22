// Helper library for numbers
#include "sys.h"

#ifndef MEM_H
#define MEM_H

enum ProtFlags {
    PROT_NONE  = 0x0,
    PROT_READ  = 0x1,
    PROT_WRITE = 0x2,
    PROT_EXEC  = 0x4,
};

enum MapFlags {
    MAP_SHARED     = 0x01,
    MAP_PRIVATE    = 0x02,
    MAP_FIXED      = 0x10,
    MAP_ANONYMOUS  = 0x20,
    MAP_DENYWRITE  = 0x0800,
    MAP_EXECUTABLE = 0x1000,
    MAP_LOCKED     = 0x2000,
    MAP_NORESERVE  = 0x4000,
    MAP_POPULATE   = 0x8000,
    MAP_NONBLOCK   = 0x10000,
    MAP_STACK      = 0x20000,
    MAP_HUGETLB    = 0x40000,
};

struct mmap_arg_struct {
    unsigned long addr;
    unsigned long len;
    unsigned long prot;
    unsigned long flags;
    unsigned long fd;
    unsigned long offset;
}; 

void *sys_mmap(struct mmap_arg_struct *mmap_arg);
int sys_munmap(void * addr, size_t len);

// Helpers
void *sys_malloc(unsigned long size) {
    struct mmap_arg_struct args = {
        .addr = 0,
        .len = size,
        .prot = PROT_READ | PROT_WRITE,
        .flags = MAP_PRIVATE | MAP_ANONYMOUS,
        .fd = (unsigned long)-1,
        .offset = 0
    };
    return sys_mmap(&args);
}

#endif