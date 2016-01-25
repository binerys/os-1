#ifndef OPENF_H
#define OPENF_H

int setFlags (int flags[]);
int open_rdonly_f(char* file, int flags[]);
int open_wronly_f(char* file, int flags[]);
int open_rdwr_f(char* file, int flags[]);

#endif 
