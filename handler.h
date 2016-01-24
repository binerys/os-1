#ifndef HANDLER_H
#define HANDLER_H

void handle_fd(int fd);
int command(int i, int o, int e, char* args[], int argsCount);
void add_proc(pid_t pid, char** command, int commandCount);
int p_wait();
int create_pipe();

#endif
