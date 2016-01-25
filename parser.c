#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

#include "parser.h"
#include "openF.h"
#include "handler.h"
#include "simpsh.h"

int verboseTrue = 0; 
int exitStatus = 0;

char*** commands;
int cmd_index = 0;
#define MAX_ARGS 100

int fileFlags[11];

#ifndef O_RSYNC
    #define O_RSYNC O_SYNC
#endif

jmp_buf context;

 
int parser(int argc, char** argv)
{
    int loop = 1;
    for (int i = 0; i < 11; i++)
    {
        fileFlags[i] = 0;
    }

    while (loop)
    {
        int a;  
        int fd;      

        int option_index = 0;
                
        a = getopt_long (argc, argv, "", long_options, &option_index);
        if (a == -1)
            break;
        
        switch(a)
        {
            case 'p':
                if (verboseTrue == 1)
                {
                    printf("--append\n");
                }
                fileFlags[0] = O_APPEND;
                break;
            case 'x':
                if (verboseTrue == 1)
                {
                    printf("--cloexec\n");
                }
                fileFlags[1] = O_CLOEXEC;
                break;
            case 'e':
                if (verboseTrue == 1)
                {
                    printf("--creat\n");
                } 
                fileFlags[2] = O_CREAT;
                break;
            case 'i':
                if (verboseTrue == 1)
                {
                    printf("--directory\n");
                }
                fileFlags[3] = O_DIRECTORY;
                break;
            case 'n':
                if (verboseTrue == 1)
                {
                    printf("--dsync\n");
                }
                fileFlags[4] = O_DSYNC;
                break;
            case 'l':
                if (verboseTrue == 1)
                {
                    printf("--excl\n");
                }
                fileFlags[5] = O_EXCL;
                break;
            case 'f':
                if (verboseTrue == 1)
                {
                    printf("--nofollow\n");
                }
                fileFlags[6] = O_NOFOLLOW;
                break;
            case 'b':
                if (verboseTrue == 1)
                {
                    printf("--nonblock\n");
                }
                fileFlags[7] = O_NONBLOCK;
                break;
            case 'y':
                if (verboseTrue == 1)
                {
                    printf("--rsync\n");
                }
                fileFlags[8] = O_RSYNC;
                break;
            case 's':
                if (verboseTrue == 1)
                {
                    printf("--sync\n");
                }
                fileFlags[9] = O_SYNC;
                break;
            case 't':
                if (verboseTrue == 1)
                {
                    printf("--trunc\n");
                }
                fileFlags[10] = O_TRUNC;
                break;
            
            case 'r': /* READ ONLY */
            { 
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    if (verboseTrue == 1)
                    {
                        printf("--rdonly\n");
                    }
                    fprintf(stderr, "option '--rdonly' requires an argument \n");
                    exitStatus = 1;
                   // optind--;
                    break;
                }

                if (verboseTrue == 1)
                    printf("--rdonly %s\n", optarg);
                
                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }  
                fd = open_rdonly_f(optarg, fileFlags);
                handle_fd(fd); 
                break;
            }
            case 'w': /* WRITE ONLY */
            {
                
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    if (verboseTrue == 1)
                    {
                        printf("--wronly\n");
                    }
                    fprintf(stderr, "option '--wronly' requires an argument \n");
                    exitStatus = 1;
                   // optind--;
                    break;
                }
                

                if (verboseTrue == 1)
                {
                    printf("--wronly %s \n", optarg);
                }

                
                
                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }  
                
                
                fd = open_wronly_f(optarg, fileFlags);
                handle_fd(fd);
                break;
            }
            case 'd': /* READ AND WRITE */
            {
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    if (verboseTrue == 1)
                    {
                        printf("--rdwr\n");
                    }
                    fprintf(stderr, "option '--rdwr' requires an argument \n");
                    exitStatus = 1;
                    break;
                }

                if (verboseTrue == 1)
                    printf("--rdwr %s\n", optarg);

                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }
                fd = open_rdwr_f(optarg, fileFlags);
                handle_fd(fd);
                break;
            }
            case 'c': /* COMMAND */
                // Bring optind back one to read arguments 
                optind--;
               
                // File Descriptor args
                int fdArgsLen = 0;
                int fdArgsCount = 0;
                int input = -1; 
                int output = -1;
                int error = -1; 

                // Command Args
                // char* cmdArgs[100];
                int cmdArgsLen = 0;
                int cmdArgsIndex = 0; // Incrementer for cmdArgs
                int cmdArgsCount = 0;
                int cmdStatus;

                commands[cmd_index] = malloc(MAX_ARGS*sizeof(char*));

                for (int i= 0; optind < argc; optind++)
                {
                    // Go through command args until we reach a new option
                    if(argv[optind][0] == '-' && argv[optind][1] == '-')
                    {
                        //printf("Discovered new option: %s \n",argv[optind]);
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
                            fprintf(stderr,"Error! Argument is not a single character! \n");

                        temp = strtol(argv[optind], &end,0);
                        if(end == argv[optind]) // Not a digit
                            fprintf(stderr,"Error! Argument is not a digit! \n");

                        if(i == 0)  
                            input = temp;
                        if(i == 1)  
                            output = temp;
                        if(i == 2) 
                             error = temp; 
                        fdArgsCount++;
                    }

                    // Parse remaining cmd arguments
                    else 
                    {

                        cmdArgsLen = strlen(argv[optind]);
                        commands[cmd_index][cmdArgsIndex] = malloc((cmdArgsLen+1)*sizeof(char));
                        strcpy(commands[cmd_index][cmdArgsIndex], argv[optind]);
                        commands[cmd_index][cmdArgsIndex][cmdArgsLen+1] = '\n';
                        cmdArgsIndex++;
                        cmdArgsCount++;
                    }

                    i++;
                }

                if(fdArgsCount != 3)
                    fprintf(stderr,"ERROR: Too little arguments \n");
                if(input == -1 | output == -1 | error == -1)
                {
                    fprintf(stderr,"ERROR: Command args incorrectly set \n");
                }

                // Append null pointer to cmdArgs
                //cmdArgs[cmdArgsCount] = NULL;
                commands[cmd_index][cmdArgsCount] = NULL;


                if( verboseTrue == 1)
                {
                    printf("--commmand");
                    for (int j = 0; j < cmdArgsCount; j++)
                    {
                        // printf(" %s",cmdArgs[j]);
                        printf(" %s", commands[cmd_index][j]);
                    }
                    printf("\n");
                }
                // cmdStatus = command(input,output,error,cmdArgs,cmdArgsCount);
                cmdStatus = command(input,output,error,commands[cmd_index],cmdArgsCount);
                cmd_index++;
                break;
            case 'v': /* VERBOSE */
                if (verboseTrue == 1)
                {
                    printf("--verbose \n");
                }
                verboseTrue = 1;
                break;

            case 'a': // WAIT
                if (verboseTrue == 1)
                {
                    printf("--wait \n");
                }
                if( p_wait() == -1 )
                    fprintf(stderr, "ERROR: Unable to wait on a process");
                break;

            case 'o': // PIPE
                if (verboseTrue == 1)
                {
                    printf("--pipe \n");
                }
                if (create_pipe() == -1)
                    fprintf(stderr,"ERROR: Unable to create a pipe");
                break;
            case 'z': /* ABORT */
                if (verboseTrue == 1)
                {
                    printf("--abort \n");
                }
                volatile int *a = NULL;
                int b = *a;
                break;
            case 'g': /* CATCH */
                if (verboseTrue == 1)
                {
                    printf("--catch %s\n", optarg);
                }
                struct sigaction catch_struct;
                catch_struct.sa_sigaction = catch_handler;
                sigemptyset(&catch_struct.sa_mask);
                catch_struct.sa_flags = 0;
                sigaction(atoi(optarg), &catch_struct, NULL);
                break;
            case 'q': /* IGNORE */
                if (verboseTrue == 1)
                {
                    printf("--ignore %s\n", optarg);
                }
                struct sigaction sig_struct;
                sig_struct.sa_sigaction = sig_handler;
                sigemptyset(&sig_struct.sa_mask);
                sig_struct.sa_flags = 0;
                //need to chekc if optarg exists first?
                sigaction(atoi(optarg), &sig_struct, NULL);
                if (setjmp(context))
                {
                    sigset_t ss;
                    sigemptyset(&ss);
                    sigaddset(&ss, SIGSEGV);
                    sigprocmask(SIG_UNBLOCK, &ss, NULL);
                    goto skip;
                }
                skip:
                break;
            case 'u': /* DEFAULT */
                if (verboseTrue == 1)
                {
                    printf("--default %s\n", optarg);
                }
                signal (atoi(optarg), SIG_DFL);
                break;
            case 'h': /*PAUSE */
                if (verboseTrue == 1)
                {
                    printf("--pause \n");
                }
                pause();
                break;
            case 'j': /*CLOSE*/ 
            {
                int tmp;
                char* end2;
                tmp = strtol(optarg, &end2,0);
                if(end2 == optarg) // Not a digit
                    fprintf(stderr,"ERROR: Argument is not a digit! \n");

                if(close_fd(tmp) == -1)
                    fprintf(stderr, "ERROR: File is already closed.");
                
                break;
            }
            default:
                abort();
            case '?':
                exitStatus = 1;
                break;
        }
    }

    // Return maximum exit status
    return exitStatus;    
}

