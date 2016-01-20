#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "handler.h"
#include "parser.h"
#include "simpsh.h"

// fileDescriptors: Array of file descriptors created during simpsh usage
// - Simpsh FD # (Array Index) -> Actual FD # (Index Value)
int fileDescriptors[100];
// fd_index - Keeps track of Simpsh FD, begins at 0
int fd_index = 0;
//--------------------------------------------------------//

// COMMAND:
int cmdCount = 0;

pid_t pid_list[100];
int pidCount = 0;



void handle_fd(int fd)
{
    //fileDescriptors[fd_index] = fd;
    fds[fd_index] = fd;
    fd_index++;
}

/**
 * Retrieves actual fd from fileDescriptors
 * @param  index Simpsh FD
 * @return       Actual file descriptor or -1 if does not exist 
 */
int get_fd(int index)
{
	if (index > fd_index)
		return -1;
	else{
		// return fileDescriptors[index];
		return fds[index];
	}
}

void add_pid(pid_t pid)
{
	pid_list[pidCount] = pid;
	pidCount++;
}

/**
 * Implementation of the command option
 * @param  i    Input file descriptor
 * @param  o    Output file descriptor
 * @param  e    Error file descriptor
 * @param  args Array of command and arguments
 * @param  argsCount Number of args
 * @return      Temporarily an integer
 */
int command(int i, int o, int e, char* args[], int argsCount)
{

	// REDIRECTION: 
	int new_input = get_fd(i);
	int new_output = get_fd(o);
	int new_error = get_fd(e);

	if (new_error == -1 | new_output == -1 | new_input == -1){
		fprintf(stderr, "ERROR: File descriptors do not exist \n");
	}

	dup2(new_input,0);
	dup2(new_output,1);
	dup2(new_error,2);

	close(new_output);
	close(new_input);
	close(new_error);

	int status;
	int ret = 0;
	pid_t pid = fork();

	switch(pid)
	{
		case 0: // CHILD PROCESS
			/* Execute Command */
			if(execvp(args[0], args) == -1){
				fprintf(stderr, "ERROR: Unable to execute command \n");
				return -1; 
			}
			cmdCount++;
			break;

		case -1: // ERROR
			fprintf(stderr, "ERROR: Forking a child process failed \n");
			return -1;
			break;

		default: // PARENT
			/* Wait for child */
			/*
			add_pid(pid);
			if (waitpid(pid_list[pidCount-1], &status,0) == -1){
				fprintf(stderr, "ERROR: waitpid() failed");
				return -1;
			}
			if (WEXITSTATUS(status)){
				ret = WEXITSTATUS(status);
			}
			*/
			// Print subcommand exit status
			/*
			printf("%d",ret);
			for (int i = 0; i < argsCount; i++)
			{
				printf(" %s",args[i]);
			}
			printf("\n");
			*/

			break;
	}

	return ret;
}

