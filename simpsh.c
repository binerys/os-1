#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "simpsh.h"
#include "parser.h"


void initialize(int argc, char** argv)
{
	int ret; 
	int procCount = 0;
	int fdCount = 0;
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
				fdCount++;
				break;
			}
			case '?':
				break;
			case -1:
				break;
			default:
				break;
		}
	}

	proc = malloc(procCount*sizeof(process));
	commands = malloc(procCount*sizeof(char**));
	fds = malloc(fdCount*sizeof(int));
	optind = 1;

	return;
}

void terminate()
{
	free(proc);
	free(fds);
	free(commands);
}

