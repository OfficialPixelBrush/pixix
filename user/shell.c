#include <unistd.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
#define COMMAND_MAX_LENGTH 256

int main() {
	// Set hostname
    if (sethostname("pixix", 5) != 0) {
        write(STDOUT,"Failed to set hostname!\n", 24);
    }

	char command[COMMAND_MAX_LENGTH];
	for (;;) {
		write(STDOUT, "# ", 2);
		int count = read(STDIN, command, COMMAND_MAX_LENGTH);

		if (count <= 0) {
            break;
        }

        // Remove trailing newline if present
        if (command[count - 1] == '\n') {
            command[count - 1] = 0;
        } else {
            command[count] = 0;
        }

		pid_t fork_result = fork();
        if (fork_result < 0) {
            break;
        }

		if (fork_result == 0) {
            // Child process

            // Build argv array for execve:
            char *argv[2];
            argv[0] = command;
            argv[1] = NULL;

            execve(command, argv, NULL);

            // If execve returns, it failed
            write(STDOUT, "FAILURE\n", 8);
           	break;
		} else {
			// Wait for child to finish
			siginfo_t info;
			waitid(P_ALL, 0, &info, WEXITED);
		}		
	}
	_exit(0);
}
