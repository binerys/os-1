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
    fd_index++;
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
 * @return      Temporarily an integer
 */
int command(int i, int o, int e, char* args[])
{

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
			if (WIFEXITED(status)){
				status_list[statusCount-1] = WIFEXITED(status);
			}

			printf("Finished process for command %s \n", args[0]);
			break;
	}


}

