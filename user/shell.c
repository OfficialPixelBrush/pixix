#include "lib/sys.h"
#include "lib/err.h"

int populate() {
    sys_write(STDOUT,"Prepping...\n",12);

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
    errprint(sys_mkdir("/mnt/a", 0755));
    errprint(sys_mkdir("/mnt/b", 0755));
    sys_write(STDOUT,"/mnt/*\n",7);

    errprint(sys_mkdir("/etc", 0755));
    sys_write(STDOUT,"/etc\n",5);

    sys_write(STDOUT,"Prep done!\n",12);
    return 0;
}

#define COMMAND_MAX_LENGTH 256

int main() {
    // Run prep
    populate();

    // This is a temporary solution because fdisk is being mean!!
    char *argv[] = { "ash", NULL };
    sys_execve("ash", argv, NULL);
    while(1);
    /*

    char command[COMMAND_MAX_LENGTH];
	for (;;) {
		sys_write(STDOUT, "# ", 2);
		int count = sys_read(STDIN, command, COMMAND_MAX_LENGTH);

		if (count <= 0) {
            break;
        }

        // Remove trailing newline if present
        if (command[count - 1] == '\n') {
            command[count - 1] = 0;
        } else {
            command[count] = 0;
        }

		pid_t fork_result = sys_fork();
        if (fork_result < 0) {
            break;
        }

		if (fork_result == 0) {
            char *argv[10];
            int argc = 0;

            char *p = command;
            argv[argc++] = p;

            for (; *p; p++) {
                if (*p == ' ') {
                    *p = '\0';  // terminate current argument
                    argv[argc++] = p + 1;  // next argument starts here
                }
            }
            argv[argc] = NULL;  // argv must be NULL-terminated

            sys_execve(command, argv, NULL);

            // If execve returns, it failed
            sys_write(STDOUT, "Command does not exist!\n", 24);
           	sys_exit(1);
		} else {
			// Wait for child to finish
			siginfo_t info;
			sys_waitid(P_ALL, 0, &info, WEXITED);
		}		
	}*/
	sys_exit(0);
}
