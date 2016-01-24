#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "openF.h"

int flagsNum;

int setFlags (int flags[])
{
    int flagCalc = flags[0];
    for (int i = 1; i < 11; i++)
    {
        flagCalc = flagCalc | flags[i];
    }
    return flagCalc;
}

// Open file as read only 
int open_rdonly_f (char* file, int flags[])
{
    flagsNum = setFlags(flags) | O_RDONLY;
    int fd = open(file, flagsNum, 0644);
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
    flagsNum = setFlags(flags) | O_WRONLY;
    int fd = open(file, flagsNum, 0644);
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

//Open file and read and write
int open_rdwr_f (char* file, int flags[])
{
    flagsNum = setFlags(flags) | O_RDWR;
    int fd = open(file, flagsNum, 0644);
    if (fd == -1)
    {
        fprintf(stderr, "ERROR: Unable to open file as read and write \n");
        return -1;
    }
    else
    {
        return fd;
    }

}

