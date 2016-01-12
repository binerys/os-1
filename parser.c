#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "parser.h"
#include "openF.h"
#include "hander.h"

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
                int index = 0;
                for (index = 0; optind < argc; optind++)

                // Array of command arguments
                char* commandArgs[4];
                int argLen = 0;
                int argCount = 0;
                for (int i= 0; optind < argc; optind++)
                {
                    // 
                    if(argv[optind][0] == '-' && argv[optind][1] == '-'){
                        printf("Discovered new option: %s \n",argv[optind]);
                        break;
                    }
                    if (argCount == 4){
                        printf("Error: Too many arguments");
                        break;
                    }
                    printf("Current arg: %s \n",argv[optind]);
                    argLen = strlen(argv[optind]);
                    commandArgs[i] = malloc(argLen*sizeof(char));
                    strcpy(commandArgs[i], argv[optind]);
                    printf("The copied arg: %s \n", commandArgs[i]);
                    argcount++;
                    i++;
                }
                if (argCount != 4)
                    printf("Error: Too little arguments");

                command(commandArgs);

                break;
            case 'v':
                //set bool to true
                //printf("verbose");
                verboseTrue = 1;
                break;
            default:
                abort();
        }
    }    
}
