#include "lib/sys.h"
#include "lib/err.h"
#include "lib/mem.h"
#include "lib/num.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        sys_write(STDOUT, "Not enough arguments!\n", 22);
        sys_exit(1);
    }

    const char *mod_path = argv[1];
    int fd = sys_open(mod_path, O_RDONLY, 0);
    if (fd < 0) printerr(fd);
    int counter = 0;

    struct stat st;
    if (sys_fstat(fd, &st) < 0) {
        sys_close(fd);
        sys_exit(1);
    }
    sys_write(STDOUT,"Got filestats\n",14);

    void *module_image = sys_malloc(st.st_size);
    if (!module_image) {
        sys_close(fd);
        sys_exit(1);
    }
    sys_write(STDOUT,"Allocated space for module\n",27);

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
    sys_write(STDOUT,"Read module\n",12);
    sys_close(fd);

    int ret = sys_init_module(module_image, st.st_size, "");
    if (ret < 0) {
        sys_munmap(module_image, st.st_size);
        sys_close(fd);
        printerr_origin(ret,"sys_init_module");
        sys_exit(1);
    }

    sys_munmap(module_image, st.st_size);
    sys_write(STDOUT,"Module loaded successfully\n",27);
    sys_exit(0);
}
