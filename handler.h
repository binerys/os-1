#ifndef HANDLER_H
#define HANDLER_H

#include <setjmp.h>
#include <sys/resource.h>

/////////////////////////////////
/* FUNCTIONS */
/////////////////////////////////

/* File Opening Functions */
/**
*   setFLags: returns OR of all of the file flags
    flags: array with all of the valid file flags
**/
int setFlags (int flags[]);

int open_rdonly_f(char* file, int flags[]);
int open_wronly_f(char* file, int flags[]);
int open_rdwr_f(char* file, int flags[]);

/* File Descriptor Functions */

/** 
*	handle_fd: Stores new file descriptor into fds array
*	- fd: file descriptor
**/
void handle_fd(int fd);

/** 
*	get_fd: Retrieves file descriptor at specified index
**/
int get_fd(int index);

/** 
*	close_fd: Closes file descriptor at specified index
**/
int close_fd(int index);

/* Process Functions */

/** 
*	add_proc: Adds new process to process array
*	- pid: process id
* 	- command: Pointer to command and arguments in commands array
*	- commandCount: Number of arguments for command
**/
void add_proc(pid_t pid, char** command, int commandCount);

/** 
*	get_proc: Retrieves index of process with specified pid
**/
int get_proc(pid_t pid);


/* Execution Functions */

/** 
*	command: Executes command
*	- i, o, e: input, output, and error file descriptor
* 	- args: Pointer to command and arguments in commands array
*	- argsCount: Number of arguments for command
**/
int command(int i, int o, int e, char* args[], int argsCount);
int create_pipe();


/* Signal Handling Functions */
/**
*   sig_handler: Jumps out of ignore    
**/
void sig_handler();

/**
*   catch_handler: Prints to stderr and exits with the signal number
**/
void catch_handler();


/* Misc */

/**
*   verbosePrint: Prints out for verbose
*   verbose_flag: Checks if the verbose flag is on or not
*   arg: Current argument
*   next_arg: Next argument
*   next_Arg_flag: Checks whether the next argument should be printed or not
**/
void verbosePrint(int verbose_flag, char* arg, char* next_arg, int next_arg_flag);

void profilePrint(int profile_flag);

int p_wait();

extern jmp_buf context;

extern struct rusage usage;
extern struct rusage prev;

#endif
