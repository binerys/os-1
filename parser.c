#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "parser.h"
#include "openF.h"
#include "handler.h"

int verboseTrue = 0; 

// - Processes fds and command
// - Verifies if fd's exist: returns 0 if no
// - Attempts to run command 


int parser(int argc, char** argv)
{
    while (1)
    {
        int a;  
        int fd;      

        static struct option long_options[] = 
        {
            {"rdonly", required_argument, 0, 'r'},
            {"wronly", required_argument, 0, 'w'},
            {"command", required_argument, 0, 'c'},
            {"verbose", no_argument, 0, 'v'},
            {0,0,0,0} 
        };

        int option_index = 0;
                
        a = getopt_long (argc, argv, "", long_options, &option_index);
        if (a == -1)
            break;
        
        switch(a)
        {
            case 'r':   
                if (verboseTrue == 1)
                {
                    printf("--rdonly %s\n", optarg); 
                }

                fd = open_rdonly_f(optarg);
                handle_fd(fd); 
                break;
            case 'w':
                //printf("wronly");
                if (verboseTrue == 1)
                {
                    printf("--wronly %s\n", optarg); 
                }
                fd = open_wronly_f(optarg);
                handle_fd(fd);
                break;
            case 'c':
                // Bring optind back one to read arguments 
                optind--;
                // Array of command arguments
                char* commandArgs[4];
                int argLen = 0;
                int argCount = 0;
                int input = -1; 
                int output = -1;
                int error = -1; 
                char* cmd; 

                for (int i= 0; optind < argc; optind++)
                {
                    if(argv[optind][0] == '-' && argv[optind][1] == '-'){
                        printf("Discovered new option: %s \n",argv[optind]);
                        break;
                    }
                    if (argCount == 4){
                        printf("Error: Too many arguments");
                        break;
                    }
                    
                    // Copy argument from argv to command args
                    argLen = strlen(argv[optind]);
                    commandArgs[i] = malloc(argLen*sizeof(char));
                    strcpy(commandArgs[i], argv[optind]);
                    argCount++;
                    i++;
                }
                if (argCount != 4)
                    printf("Error: Too little arguments");

                // Extract commands from commandArgs and validate
                int temp; 
                char* end;
                for(int i = 0; i < argCount; i++)
                {
                    // Arg #1,2,3: Check that arg is a single number
                    if(i == 0 | i == 1 | i == 2)
                    {
                        argLen = strlen(commandArgs[i]);
                        if( argLen != 1)
                            printf("Error! Argument is not a single character!");
                        
                        temp = strtol(commandArgs[i], &end,0);
                        if(end == commandArgs[i]) // Not a digit
                            printf("Error! Argument is not a digit!");

                        if(i == 0)  input = temp;
                        if(i == 1)  output = temp;
                        if(i == 2)  error = temp; 
                    }
                }

                // Call command
                break;
            case 'v':
                //set bool to true
                //printf("verbose");
                if (verboseTrue == 1)
                {
                    printf("--verbose \n");
                }
                verboseTrue = 1;
                break;
            default:
                abort();
        }
    }    
}
