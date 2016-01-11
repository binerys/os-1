

#include "handling.h"

int fileDescriptors[100];
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
