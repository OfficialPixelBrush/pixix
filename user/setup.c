// Incredibly minimal init system that populates dev and stuff
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1

int main() {
    // Mount tmpfs at /run
    if (mount("tmpfs", "/run", "tmpfs", 0, "mode=755") < 0) {
        return 1;
    }

    // Create /run/lock
    if (mkdir("/run/lock", 0755) < 0) {
        return 1;
    }

    // Mount procfs at /proc
    if (mount("proc", "/proc", "proc", 0, "") < 0) {
        return 1;
    }

    // Mount sysfs at /sys
    if (mount("sysfs", "/sys", "sysfs", 0, "") < 0) {
        return 1;
    }

    write(STDOUT,"MOUNTS GOOD\n",12);
    return 0;
}