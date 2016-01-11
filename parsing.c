#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "parsing.h"
#include "openF.h"
#include "handling.h"

bool verboseTrue = false; 

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
                //printf("rdonly");
                if (verboseTrue == true)
                {
                    printf("--rdonly "); //add file that it is actually reading in - %
                }
                printf("rdonly \n");
                fd = open_rdonly_f(optarg);
                handle_fd(fd); 
                break;
            case 'w':
                //printf("wronly");
                if (verboseTrue == true)
                {
                    printf("--wronly "); //add file that it is actually reading in - %
                }

                fd = open_wronly_f(optarg);
                handle_fd(fd);
                break;
            case 'c':
                //printf("command");
                optind--;
                for (int index = 0; optind < argc; optind++)
                {
                    if (*argv[optind] == '-')
                    {
                        if (*(argv[optind]++) == '-')
                        {
                            break;
                        }
                    }

                    //char addOn[];
                    char *optArgString = addString(&addOn , argv[optind]);
                   //do more stuff here 
                        
                }
                break;
            case 'v':
                //set bool to true
                //printf("verbose");
                verboseTrue = true;
                break;
            default:
                abort();
        }
    }    
}
