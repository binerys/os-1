#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "simpsh.h"
#include "parser.h"


void initialize(int argc, char** argv)
{
	int ret, fdCount = 0, procCount = 0;
	int option_index = 0, loop = 1; 
	
	while(loop)
	{
		ret = getopt_long (argc, argv, "", long_options, &option_index);
		if (ret == -1)
			loop = 0;
		switch(ret)
		{
			case 'c': // COMMAND
			{
				procCount++;
				break;
			}
			case 'r': // READ-ONLY
			{
				fdCount++;
				break;
			}
			case 'w': // WRITE-ONLY
				fdCount++;
				break;
			case 'd': // READ & WRITE
			{
				fdCount++;
				break;
			}
			case 'o': //PIPE
			{
				fdCount++;
				break;
			}
			case '?':
				break;

			case -1:
				break;
			default:
				abort();
		}
	}

	proc = malloc(procCount*sizeof(process));
	fds = malloc(fdCount*sizeof(int));
	optind = 0;

	printf("The number of processes are: %d", procCount);
	printf("The number of file descripters are: %d", fdCount);
	return;
}

