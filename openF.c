#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openF.h"

// Open file as read only 
int open_rdonly_f (char* file)
{
    int fd = open(file, O_RDONLY,644);
    printf("fd READ only value is %d \n", fd);
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
    int fd = open(file, O_WRONLY,644);
    printf("fd WRITE only value is %d \n", fd);
    if (fd == -1)
    {
        printf("Unable to open file as write-only");
        return -1;
    }    
    else
    {
        return fd;
    }

}
