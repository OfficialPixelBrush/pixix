#include "sys.h"
#include "mem.h"
#include "num.h"
#include "str.h"

int insmod(const char* mod_path) {
    int fd = sys_open(mod_path, O_RDONLY, 0);
    if (fd < 0) return fd;
    int counter = 0;

    struct stat st;
    if (sys_fstat(fd, &st) < 0) {
        sys_close(fd);
        return 1;
    }

    void *module_image = sys_malloc(st.st_size);
    if (!module_image) {
        sys_close(fd);
        return 1;
    }

    int readsize = sys_read(fd, module_image, st.st_size);
    if (readsize != st.st_size) {
        // Size mismatch!
        printint(readsize);
        sys_write(STDOUT, "/", 1);
        printint(st.st_size);
        sys_munmap(module_image, st.st_size);
        sys_close(fd);
        sys_exit(1);
    }
    sys_close(fd);

    int ret = sys_init_module(module_image, st.st_size, "");
    if (ret < 0) {
        sys_munmap(module_image, st.st_size);
        sys_close(fd);
        return ret;
    }

    sys_munmap(module_image, st.st_size);
    sys_write(STDOUT,"Loaded ",7);
    sys_write(STDOUT,mod_path,strlen(mod_path));
    sys_write(STDOUT,"\n",1);
    return 0;
}