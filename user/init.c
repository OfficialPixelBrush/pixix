// This is basically our init script
#include "lib/sys.h"
#include "lib/err.h"

void prep() {
    sys_write(STDOUT,"Prepping...\n",12);

    // Mount tmpfs at /run
    printerr(sys_mkdir("/run", 0755));
    printerr(sys_mount("tmpfs", "/run", "tmpfs", 0, "mode=755"));
    sys_write(STDOUT,"/run\n",5);

    // Create /run/lock
    printerr(sys_mkdir("/run/lock", 0755));
    sys_write(STDOUT,"/run/lock\n",10);

    // Mount procfs at /proc
    printerr(sys_mkdir("/proc", 0755));
    printerr(sys_mount("proc", "/proc", "proc", 0, ""));
    sys_write(STDOUT,"/proc\n",6);

    // Mount sysfs at /sys
    printerr(sys_mkdir("/sys", 0755));
    printerr(sys_mount("sysfs", "/sys", "sysfs", 0, ""));
    sys_write(STDOUT,"/sys\n",5);

    // Mount /dev
    printerr(sys_mount("devtmpfs", "/dev", "devtmpfs", MS_NOATIME, "mode=0755"));
    sys_write(STDOUT,"/dev\n",5);

    // Create /dev/pts for interactive shells
    printerr(sys_mkdir("/dev/pts", 0755));
    printerr(sys_mount("devpts", "/dev/pts", "devpts", MS_NOEXEC | MS_NOSUID, "gid=5,mode=0620"));
    sys_write(STDOUT,"/dev/pts\n",9);

    // Create /mnt
    printerr(sys_mkdir("/mnt", 0755));
    sys_write(STDOUT,"/mnt\n",5);

    printerr(sys_mkdir("/etc", 0755));
    sys_write(STDOUT,"/etc\n",5);

    // Mount tmpfs at /run
    printerr(sys_mkdir("/lib", 0755));
    printerr(sys_mkdir("/lib/modules", 0755));
    sys_write(STDOUT,"/lib/*\n",7);

    sys_write(STDOUT,"Prep done!\n",12);
    return;
}

void _start() {
    prep();
    sys_execve("/bin/shell",0,0);
}