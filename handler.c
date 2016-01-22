#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "handler.h"
#include "parser.h"
#include "simpsh.h"

process	*proc;
int *fds;


int fd_index = 0;
int proc_index = 0;

void handle_fd(int fd)
{
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
		return fds[index];
	}
}

void add_proc(pid_t pid, char** command, int commandCount)
{
	proc[proc_index].pid = pid;
	proc[proc_index].cmd = command;
	proc[proc_index].cmdCount = commandCount;
	proc_index++;
}

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
			break;

		case -1: // ERROR
			fprintf(stderr, "ERROR: Forking a child process failed \n");
			return -1;
			break;

		default: // PARENT
			/* Wait for child */
			add_proc(pid,args,argsCount);
			break;
	}

	return ret;
}

int p_wait()
{
	int i;
	int status;
	for (i = 0; i <= proc_index; i++)
	{
		if(waitpid(proc[i].pid, &status, 0) == -1)
			return -1;
		if (WIFEXITED(status))
			proc[i].status = WEXITSTATUS(status);

		printf("%d", proc[i].status);
		int j;
		for(j = 0; j < proc[i].cmdCount; j++)
		{
			printf(" %s", proc[i].cmd[j]);
		}
		printf("\n");
	}
	return 0;
}

