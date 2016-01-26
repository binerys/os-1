#ifndef HANDLER_H
#define HANDLER_H

#include <setjmp.h>

/**
*   setFLags: returns OR of all of the file flags
    flags: array with all of the valid file flags
**/
int setFlags (int flags[]);

int open_rdonly_f(char* file, int flags[]);
int open_wronly_f(char* file, int flags[]);
int open_rdwr_f(char* file, int flags[]);

void handle_fd(int fd);
int command(int i, int o, int e, char* args[], int argsCount);
void add_proc(pid_t pid, char** command, int commandCount);
int p_wait();
int create_pipe();

/**
*   sig_handler: Jumps out of ignore    
**/
void sig_handler();

/**
*   catch_handler: Prints to stderr and exits with the signal number
**/
void catch_handler();

/**
*   verbosePrint: Prints out for verbose
*   verbose_flag: Checks if the verbose flag is on or not
*   arg: Current argument
*   next_arg: Next argument
*   next_Arg_flag: Checks whether the next argument should be printed or not
**/
void verbosePrint(int verbose_flag, char* arg, char* next_arg, int next_arg_flag);

extern jmp_buf context;
int close_fd(int index);


#endif
