#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "handler.h"


int INIT_FD = 100;

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

int status_list[100];
int statusCount = 0;

void handle_fd(int fd)
{
    fileDescriptors[fd_index] = fd;
    printf("Value in array is: %d  at index %d \n", fileDescriptors[fd_index], fd_index);
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
	else
		return fileDescriptors[index];
}

void add_pid(pid_t pid)
{
	pid_list[pidCount] = pid;
	pidCount++;
}

void add_status(int st)
{
	status_list[statusCount] = st; 
	statusCount++;
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

	printf("New_output fd is: %d \n", new_output);
	printf("New_input fd is: %d \n", new_input);
	printf("new_error fd is: %d \n", new_error);
	if (new_error == -1 | new_output == -1 | new_input == -1){
		printf("ERROR: file descriptors do not exist \n");
	}

	dup2(new_input,0);
	dup2(new_output,1);
	dup2(new_error,2);

	close(new_output);
	close(new_input);
	close(new_error);

	int status;
	pid_t pid = fork();

	switch(pid)
	{
		case 0: // CHILD PROCESS
			/* Execute Command */
			if(execvp(args[0], args) == -1)
				printf("ERROR: Unable to execute command");
			cmdCount++;
			break;

		case -1: // ERROR
			printf("ERROR: Forking a child process failed \n");
			break;

		default: // PARENT
			/* Wait for child */
			add_pid(pid);
			if (waitpid(pid_list[pidCount-1], &status,0) == -1){
				printf("ERROR: waitpid() failed");
			}
			if (WEXITSTATUS(status)){
				status_list[statusCount-1] = WEXITSTATUS(status);
			}

			// Print subcommand exit status
			printf("%d",WEXITSTATUS(status));
			for (int i = 0; i < argsCount; i++)
			{
				printf(" %s",args[i]);
			}
			printf("\n");
			break;
	}


}

