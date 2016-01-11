#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openF.h"

// Open file as read only 
int open_rdonly_f (char* file)
{
    int fd = open(file, O_RDONLY);
    printf("fd value is %d", fd);
    if (fd == -1)
    {
        printf("Unable to open file as read-only.");
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
    int fd = open(file, O_WRONLY);
    printf("fd value is %d", fd);
    if (fd == -1)
    {
        printf("Unable to open file as read-only");
        return -1;
    }    
    else
    {
        return fd;
    }

}
