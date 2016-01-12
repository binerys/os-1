#include <stdio.h>
#include <stdlib.h>
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
                //do I need a printf here? 
                //printf("rdonly");
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
                //printf("command");
                optind--;
                int index = 0;
                for (index = 0; optind < argc; optind++)
                {
                    if (*argv[optind] == '-')
                    {
                        if (*(argv[optind]++) == '-')
                        {
                            break;
                        }
                    }

                    //char addOn[5];
                    //char *optArgString = addString(&addOn , argv[optind]);
                   //do more stuff here 
                        
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
