#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <math.h>

#include "handler.h"
#include "parser.h"
#include "simpsh.h"

/* GLOBALS */
process	*proc;
int *fds;


int fd_index = 0;
int proc_index = 0;

int fdCount;
int procCount;
/*************/

int flagsNum;

int setFlags (int flags[])
{
    int flagCalc = flags[0];
    for (int i = 1; i < 11; i++)
    {
        flagCalc = flagCalc | flags[i];
    }
    return flagCalc;
}

// Open file as read only 
int open_rdonly_f (char* file, int flags[])
{
    flagsNum = setFlags(flags) | O_RDONLY;
    int fd = open(file, flagsNum, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "ERROR: Unable to open file as read-only. \n");
        return -1;
    }
    else
    {
        return fd;
    }
}

// Open file as write only
int open_wronly_f (char* file, int flags[])
{
    flagsNum = setFlags(flags) | O_WRONLY;
    int fd = open(file, flagsNum, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "ERROR: Unable to open file as write-only \n");
        return -1;
    }
    else
    {
        return fd;
    }

}

//Open file and read and write
int open_rdwr_f (char* file, int flags[])
{
    flagsNum = setFlags(flags) | O_RDWR;
    int fd = open(file, flagsNum, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "ERROR: Unable to open file as read and write \n");
        return -1;
    }
    else
    {
        return fd;
    }

}

void handle_fd(int fd)
{
    fds[fd_index] = fd;
    fd_index++;
}


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
	pid_t pid = fork();

	switch(pid)
	{
		case 0: // CHILD PROCESS

			// Set redirects for the child
			dup2(new_input,0);
			dup2(new_output,1);
			
			if (new_error != -1)
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
	return 0;
}

int p_wait(int profCheck)
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
    
    if (profCheck == 1)
    {
        struct rusage comUsage;
        getrusage(RUSAGE_CHILDREN, &comUsage);
        printf("Children: User time: %d seconds %d microseconds, System Time: %d seconds, %d microseconds\n",comUsage.ru_utime.tv_sec, comUsage.ru_utime.tv_usec, comUsage.ru_stime.tv_sec, comUsage.ru_stime.tv_usec);  
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

void verbosePrint(int verbose_flag, char* arg, char* next_arg, int next_arg_flag)
{
    if (verbose_flag != 1)
    {
        return;
    }
    else if (next_arg_flag != 1)
    {
        printf("%s \n", arg);
        fflush(stdout);
    }
    else
    {
        printf("%s %s \n", arg, next_arg);
        fflush(stdout);
    }
}

void profilePrint(int profile_flag)
{
    if (profile_flag != 1)
    {
        return;
    }
    int cpuSec = 0;
    int cpuSysSec = 0;
    int cpuUsec = 0;
    int cpuSysUsec = 0;

    cpuSec = usage.ru_utime.tv_sec - prev.ru_utime.tv_sec;
    cpuSysSec = usage.ru_stime.tv_sec - prev.ru_stime.tv_sec;
    cpuUsec = usage.ru_utime.tv_usec - prev.ru_utime.tv_usec;
    cpuSysUsec = usage.ru_stime.tv_usec - prev.ru_stime.tv_usec;
 
    printf("User time: %d seconds %d microseconds, System Time: %d seconds, %d microseconds\n", cpuSec, cpuUsec, cpuSysSec, cpuSysUsec); 
}
