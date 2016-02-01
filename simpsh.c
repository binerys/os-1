#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "simpsh.h"
#include "parser.h"


void initialize(int argc, char** argv)
{
	int ret; 
	procCount = 0;
	fdCount = 0;
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
	// Initialize all exit statuses to -1
	for(int i = 0; i < procCount; i++)
	{
		proc[i].status = -1;
	}
	commands = malloc(procCount*sizeof(char**));
	fds = malloc(fdCount*sizeof(fileDescriptor));
	max_args = argc;
	optind = 1;

	return;
}

void terminate()
{
	int i, j;
	for(i = 0; i < procCount; i++)
	{
		for (j=0; j < proc[i].cmdCount; j++)
		{
			free(proc[i].cmd[j]);
		}
		free(proc[i].cmd);
	}
	free(commands);
	free(proc);
	free(fds);
}


int max_exit(int parseExit)
{
	int max = parseExit;
	int i;
	if (procCount == 0)
		return 0;
	for(i = 0; i < procCount; i++)
	{
		if (proc[i].status > max)
			max = proc[i].status;
	}
	return max;
}


