#include "handling.h"
#include <stdlib.h>
#include <stdio.h>

int INIT_FD = 100;
int *fileDescriptors;
// fileDescriptors: Dynamic array of file descriptors created during simpsh usage
// - Simpsh FD # (Array Index) -> Actual FD # (Index Value)

// INITIALIZE fileDescriptors ARRAY
fileDescriptors = malloc(INIT_FD*sizeof(int));
if (fileDescriptors = NULL){
    exit(EXIT_FAILURE);
}

// RESIZE fileDescriptors ARRAY
if((index+1)>=INIT_FD){
    int* fileDescriptors = malloc(INIT_FD*2*sizeof(int));
}
if (fileDescriptors = NULL){
    exit(EXIT_FAILURE);
}
//--------------------------------------------------------//

// fd_index - Keeps track of Simpsh FD, begins at 0
int fd_index = 0;

void handle_fd(int fd)
{
    fileDescriptors[fd_index] = fd;
    fd_index++;
    printf(fileDescriptors[fd_index]); // test
}
char* optArgString(char *a, char *b)
{
    char *tmp = a;

    //should prob do somehting to a here

    while (*b != '\0')
    {
        *a = *b;
        a++;
        b++;
    }

    *a = '\0';

    return tmp;
}
