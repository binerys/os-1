#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openF.h"

int open_rdonly_f (char* file)
{
    //not sure 
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        printf("Error");
        return -1;
    }    
    else
    {
        return fd;
    }
}

int open_wronly_f (char* file)
{
    //not sure 
    int fd = open(file, O_WRONLY);
    if (fd == -1)
    {
        printf("Error");
        return -1;
    }    
    else
    {
        return fd;
    }

}
