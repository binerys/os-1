#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "parser.h"
#include "openF.h"
#include "handler.h"

int verboseTrue = 0; 
 
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
            {   
                if (verboseTrue == 1)
                {
                    printf("--rdonly %s\n", optarg); 
                }
                
                int rdCount = -1;
                
                for (int i= 0; optind < argc; optind++)
                {
                    rdCount++;
                    if(argv[optind][0] == '-' && argv[optind][1] == '-'){
                        //printf("Discovered new option: %s \n",argv[optind]);
                        break;
                    }
                }             
                printf("rdCount: %d\n",rdCount);                

                if (rdCount != 0)
                {
                    printf("Error: Not the correct amount of arguments for rdonly\n");
                    //break;
                }   

                fd = open_rdonly_f(optarg);
                handle_fd(fd); 
                break;
            }
            case 'w':
            {
                //printf("wronly");
                if (verboseTrue == 1)
                {
                    printf("--wronly %s\n", optarg); 
                }

                int wrCount = 0;

                for (int i= 0; optind < argc; optind++)
                {
                    if(argv[optind][0] == '-' && argv[optind][1] == '-'){
                        //printf("Discovered new option: %s \n",argv[optind]);
                        break;
                    }
                    wrCount++;
                }

                if (wrCount != 0)
                {
                    printf("Error: Not the correct amount of arguments for wronly\n");
                    break;
                }

                fd = open_wronly_f(optarg);
                handle_fd(fd);
                break;
            }
            case 'c':
                // Bring optind back one to read arguments 
                optind--;
               
                // File Descriptor args
                int fdArgsLen = 0;
                int fdArgsCount = 0;
                int input = -1; 
                int output = -1;
                int error = -1; 

                // Command Args
                char* cmdArgs[100]; // will malloc eventually, don't forget to append null byte!
                int cmdArgsLen = 0;
                int cmdArgsIndex = 0; // Incrementer for cmdArgs
                int cmdArgsCount = 0;

                for (int i= 0; optind < argc; optind++)
                {
                    // Go through command args until we reach a new option
                    if(argv[optind][0] == '-' && argv[optind][1] == '-')
                    {
                        printf("Discovered new option: %s \n",argv[optind]);
                        break;
                    }

                    // Process first three arguments
                    // Conditions: Must be a single digit
                    int temp; 
                    char* end;
                    if(i == 0 | i == 1 | i == 2)
                    {
                        fdArgsLen = strlen(argv[optind]);
                        if (fdArgsLen != 1) // Check that it is a single digit
                            printf("Error! Argument is not a single character!");

                        temp = strtol(argv[optind], &end,0);
                        if(end == argv[optind]) // Not a digit
                            printf("Error! Argument is not a digit!");

                        if(i == 0)  input = temp;
                        if(i == 1)  output = temp;
                        if(i == 2)  error = temp; 
                        fdArgsCount++;
                    }

                    // Parse remaining cmd arguments
                    else 
                    {
                        cmdArgsLen = strlen(argv[optind]);
                        cmdArgs[cmdArgsIndex] = malloc((cmdArgsLen+1)*sizeof(char));
                        strcpy(cmdArgs[cmdArgsIndex], argv[optind]);
                        cmdArgsIndex++;
                        cmdArgsCount++;
                    }

                    i++;
                }

                if(fdArgsCount != 3)
                    printf("Error: Too little arguments");

                // Append null byte to cmdArgs
                cmdArgs[cmdArgsCount] = "\0";

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
