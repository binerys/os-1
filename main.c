#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "simpsh.h"

int exit_status;

int main(int argc, char** argv)
{
	// Create a copy of argv for initial getopt to use
	char** argCopy = malloc(argc*sizeof(char*)); 
	int i; 
	for (i=0;i<argc;i++)
	{
		argCopy[i] = argv[i];
	}
	
	initialize(argc, argCopy);
    exit_status = parser(argc, argv);
    terminate();
    
    free(argCopy);
    int maxExit = max_exit(exit_status);
    printf("exit: %d", maxExit);
    exit(maxExit);
}
