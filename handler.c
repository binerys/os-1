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

int fdCount;
int procCount;

//jmp_buf context;

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

int close_fd(int index)
{
	if ((index > fd_index) || (fds[index] == -1)){
		return -1;
	}
	else{
		close(fds[index]);
		fds[index] = -1;
		return 0;
	}
	
}

/* Retrieves process index in proc of given pid */
int get_proc(pid_t pid)
{
	int i;
	for(i = 0; i < procCount; i++)
	{
		if(proc[i].pid == pid)
			return i;
	}

	// Unable to retrieve process index
	return -1;
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

	int status;
	int ret = 0;
	pid_t pid = fork();

	switch(pid)
	{
		case 0: // CHILD PROCESS

			// Set redirects for the child
			dup2(new_input,0);
			dup2(new_output,1);
			dup2(new_error,2);

			// Close remaining file descriptors
			int s;
			for (s = 0; s < fdCount; s++)
			{
				if (s != i && s != o && s != e)
					close_fd(s);
			}
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
	int pid; 
	int count = 0;

	// Infinite waiting fix - Close all file descriptors
	int s;
	for (s = 0; s < fdCount; s++)
	{
		close_fd(s);
	}

	while (count != cmd_index)
	{
		if ((pid = wait(&status)) == -1){
			fprintf(stderr, "ERROR: Unable to wait.");
			return -1;
		}
		if ( (i = get_proc(pid)) ==  -1) {
			fprintf(stderr, "ERROR: Unable to retrieve process index of pid %d", pid);
			break;
		}
		count++;
		if (WIFEXITED(status))
			proc[i].status = WEXITSTATUS(status);

		printf("%d", proc[i].status);

		// Print out all of the command's args
		int j;
		for(j = 0; j < proc[i].cmdCount; j++)
		{
			printf(" %s", proc[i].cmd[j]);
		}
		printf("\n");

	}

	return 0;
}

int create_pipe()
{
	int pfd[2];
	if( pipe(pfd) == -1)
		return -1;
	handle_fd(pfd[0]); // Read end
	handle_fd(pfd[1]); // Write End
	return 0;

}

void sig_handler(int signal, siginfo_t *a, void *b)
{
    longjmp(context, -1);
}

void catch_handler(int signal, siginfo_t *a, void *b)
{
    fprintf(stderr, "%d caught\n", signal);
    exit(signal);
}
