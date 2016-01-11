#include "handling.h"
#include <stdlib.h>

#define INIT_FD 100

// fileDescriptors: Dynamic array of file descriptors created during simpsh usage
// - Simpsh FD # (Array Index) -> Actual FD # (Index Value)

// INITIALIZE fileDescriptors ARRAY
int* fileDescriptors = malloc(INIT_FD*sizeof(int));
if (fileDescriptors = NULL)
{
    exit(EXIT_FAILURE);
}

// RESIZE fileDescriptors ARRAY
if ( (index+1) >= INIT_FD )
    int* fileDescriptors = malloc(INIT_FD*2*sizeof(int));
if (fileDescriptors = NULL)
{
    exit(EXIT_FAILURE);
}
//--------------------------------------------------------//

// index - Keeps track of Simpsh FD, begins at 0
int index = 0;

void handle_fd(int fd)
{
    fileDescriptors[index] = fd;
    index++;
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

    return tmp
}
