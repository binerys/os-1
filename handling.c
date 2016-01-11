#include "handling.h"
#include <stdlib.h>
#include <stdio.h>

int INIT_FD = 100;

// fileDescriptors: Array of file descriptors created during simpsh usage
// - Simpsh FD # (Array Index) -> Actual FD # (Index Value)
int fileDescriptors[100];
//--------------------------------------------------------//

// fd_index - Keeps track of Simpsh FD, begins at 0
int fd_index = 0;

void handle_fd(int fd)
{
    fileDescriptors[fd_index] = fd;
    fd_index++;
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
