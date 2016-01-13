#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openF.h"

// Open file as read only 
int open_rdonly_f (char* file)
{
    int fd = open(file, O_RDONLY,644);
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
int open_wronly_f (char* file)
{
    int fd = open(file, O_WRONLY,644);
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
