#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "parsing.h"
#include "openF.h"
#include "handling.h"

int verboseTrue = 0; 

int parsing(int argc, char** argv)
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
            {"verbose", no_argument, 0, 'v'} 
        };

        int option_index = 0;
                
        a = getopt_long (argc, argv, "", long_options, &option_index);
        if (a == -1)
            break;
        
        switch(a)
        {
            case 'r':
                //do I need a printf here? 
                if (verboseTrue == 1)
                {
                    printf("--rdonly "); //add file that it is actually reading in - %
                }
                printf("rdonly \n");
                fd = open_rdonly_f(optarg);
                handle_fd(fd); 
                break;
            case 'w':
                if (verboseTrue == 1)
                {
                    printf("--wronly "); //add file that it is actually reading in
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
                for (int i= 0; optind < argc; optind++)
                {
                    if(argv[optind][0] == '-' && argv[optind][1] == '-'){
                        printf("Discovered new option: %s \n",argv[optind]);
                        break;
                    }

                    printf("Current arg: %s \n",argv[optind]);
                    argLen = strlen(argv[optind]);
                    commandArgs[i] = malloc(argLen*sizeof(char));
                    strcpy(commandArgs[i], argv[optind]);
                    printf("The copied arg: %s \n", commandArgs[i]);
                    i++;

                }

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
