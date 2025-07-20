// Incredibly minimal init system that populates dev and stuff
#include "sys.h"
#include "lib.h"

int main() {
    sys_write(STDOUT,"Running prep...\n",16);

    // Mount tmpfs at /run
    errprint(sys_mkdir("/run", 0755));
    errprint(sys_mount("tmpfs", "/run", "tmpfs", 0, "mode=755"));
    sys_write(STDOUT,"/run\n",5);

    // Create /run/lock
    errprint(sys_mkdir("/run/lock", 0755));
    sys_write(STDOUT,"/run/lock\n",10);

    // Mount procfs at /proc
    errprint(sys_mkdir("/proc", 0755));
    errprint(sys_mount("proc", "/proc", "proc", 0, ""));
    sys_write(STDOUT,"/proc\n",6);

    // Mount sysfs at /sys
    errprint(sys_mkdir("/sys", 0755));
    errprint(sys_mount("sysfs", "/sys", "sysfs", 0, ""));
    sys_write(STDOUT,"/sys\n",5);

    // Mount /dev
    errprint(sys_mount("devtmpfs", "/dev", "devtmpfs", MS_NOATIME, "mode=0755"));
    sys_write(STDOUT,"/dev\n",5);

    // Create /dev/pts for interactive shells
    errprint(sys_mkdir("/dev/pts", 0755));
    errprint(sys_mount("devpts", "/dev/pts", "devpts", MS_NOEXEC | MS_NOSUID, "gid=5,mode=0620"));
    sys_write(STDOUT,"/dev/pts\n",9);

    // Create /mnt
    errprint(sys_mkdir("/mnt", 0755));
    sys_write(STDOUT,"/mnt\n",5);

    sys_write(STDOUT,"Prep done!\n",12);
    sys_exit(0);
}