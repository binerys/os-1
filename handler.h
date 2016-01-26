#ifndef HANDLER_H
#define HANDLER_H

#include <setjmp.h>

int setFlags (int flags[]);
int open_rdonly_f(char* file, int flags[]);
int open_wronly_f(char* file, int flags[]);
int open_rdwr_f(char* file, int flags[]);

void handle_fd(int fd);
int command(int i, int o, int e, char* args[], int argsCount);
void add_proc(pid_t pid, char** command, int commandCount);
int p_wait();
int create_pipe();
void sig_handler();
void catch_handler();
void verbosePrint(int verbose_flag, char* arg, char* next_arg, int next_arg_flag);

extern jmp_buf context;
int close_fd(int index);


#endif
