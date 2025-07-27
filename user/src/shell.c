#include "lib/sys.h"
#include "lib/err.h"

#define COMMAND_MAX_LENGTH 256
#define COMMAND_MAX_ARGS 10

void _start() {
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

		unsigned int fork_result = sys_fork();
        if (fork_result < 0) sys_exit(1);

		if (fork_result == 0) {
            char *argv[COMMAND_MAX_ARGS];
            int argc = 0;

            char *p = command;
            argv[argc++] = p;

            for (; *p; p++) {
                if (*p == ' ') {
                    *p = '\0';  // terminate current argument
                    argv[argc++] = p + 1;  // next argument starts here
                }
            }
            argv[argc] = 0;  // argv must be NULL-terminated

            printerr(sys_execve(command, argv, 0));

            // If execve returns, it failed
            sys_write(STDOUT, "Command does not exist!\n", 24);
           	sys_exit(1);
		} else {
			// Wait for child to finish
			sys_waitid(P_ALL, 0, 0, WEXITED);
		}		
	}
	sys_exit(0);
}
