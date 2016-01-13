#include <stdlib.h>

#include "parser.h"

int exit_status;

int main(int argc, char** argv)
{
    exit_status = parser(argc, argv);
    //printf("%d", exit_status);

    return exit_status;    
}
