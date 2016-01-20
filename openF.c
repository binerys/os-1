#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openF.h"

int flags;

int setFlags (int flags[])
{
    int flagNum = flags[0];
    for (int i = 1; i < 11; i++)
    {
        flagNum = flagNum | flags[i];
    }
    return flagNum;
}

// Open file as read only 
int open_rdonly_f (char* file, int flags[])
{
    flags = setFlags(flags[]) | O_RDONLY;
    int fd = open(file, flags ,644);
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
    flags = setFlags(flags[]) | O_WRONLY;
    int fd = open(file, flags ,644);
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
