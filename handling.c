

#include "handling.h"

int fileDescriptors[100];
int index = 0;

void handle_fd(int fd)
{
    fileDescriptors[index] = fd;
    index++;
}
