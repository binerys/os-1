#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "simpsh.h"

int exit_status;


int main(int argc, char** argv)
{
	initialize(argc, argv);
    exit_status = parser(argc, argv);
    terminate();
    return exit_status;    
}
