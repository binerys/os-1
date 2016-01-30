#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

#include "parser.h"
#include "handler.h"
#include "simpsh.h"

/* GLOBALS */
int verboseTrue = 0; 
int exitStatus = 0;

char*** commands;
int cmd_index = 0;
int max_args;
/*******************/

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
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);  
                fileFlags[0] = O_APPEND;
                break; 
            }
            case 'x': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[1] = O_CLOEXEC;
                break;
            }
            case 'e': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[2] = O_CREAT;
                break; 
            }
            case 'i': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[3] = O_DIRECTORY;
                break;
            }
            case 'n': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[4] = O_DSYNC;
                break; 
            }
            case 'l': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[5] = O_EXCL;
                break; 
            }
            case 'f': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[6] = O_NOFOLLOW;
                break; 
            }
            case 'b': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);    
                fileFlags[7] = O_NONBLOCK;
                break;
            }
            case 'y': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[8] = O_RSYNC;
                break; 
            }
            case 's': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[9] = O_SYNC;
                break; 
            }
            case 't': 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                fileFlags[10] = O_TRUNC;
                break; 
            }
            
            case 'r': /* READ ONLY */
            { 
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                    fprintf(stderr, "option '--rdonly' requires an argument \n");
                    exitStatus = 1;
                    break;
                }

                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);                
                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }  
                fd = open_rdonly_f(optarg, fileFlags);
                handle_fd(fd,FD); 
                break;
            }
            case 'w': /* WRITE ONLY */
            {
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                    fprintf(stderr, "option '--wronly' requires an argument \n");
                    exitStatus = 1;
                    break;
                }
                
                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);
                
                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }  
                
                
                fd = open_wronly_f(optarg, fileFlags);
                handle_fd(fd,FD);
                break;
            }
            case 'd': /* READ AND WRITE */
            {
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                    fprintf(stderr, "option '--rdwr' requires an argument \n");
                    exitStatus = 1;
                    break;
                }

                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);                

                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }

                fd = open_rdwr_f(optarg, fileFlags);
                handle_fd(fd,FD);
                break;
            }
            case 'c': /* COMMAND */
            {
                
                // Bring optind back one to read arguments 
                optind--;
               
                /* File Descriptor args */
                int fdArgsLen = 0; // The length of each argument
                int fdArgsCount = 0;  // Number of arguments
                int input = -1; 
                int output = -1;
                int error = -1; 

                /* Command args */
                int cmdArgsLen = 0; // Length of current comand
                int cmdArgsIndex = 0; // Tracks current commands argument index
                int cmdArgsCount = 0; // Number of arguments for command
                int cmdStatus;

                commands[cmd_index] = malloc(max_args*sizeof(char*));

                for (int i= 0; optind < argc; optind++)
                {
                    // Go through command args until we reach a new option
                    if(argv[optind][0] == '-' && argv[optind][1] == '-')
                    {
                        break;
                    }

                    // Process first three arguments
                    // Conditions: Must be a single digit
                    int temp; 
                    char* end;
                    if(i == 0 | i == 1 | i == 2)
                    {
                        // Convert argument into integer
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
                commands[cmd_index][cmdArgsCount] = NULL;

                if( verboseTrue == 1)
                {
                    printf("--commmand");
                    for (int j = 0; j < cmdArgsCount; j++)
                    {
                        // printf(" %s",cmdArgs[j]);
                        printf(" %s", commands[cmd_index][j]);
                        fflush(stdout);
                    }
                    printf("\n");
                    fflush(stdout);
                }

                cmdStatus = command(input,output,error,commands[cmd_index],cmdArgsCount,cmd_index);
                if (cmdStatus == -1)
                    exitStatus = 1;
                cmd_index++;
                break;
            }
            case 'v': /* VERBOSE */
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                verboseTrue = 1;
                break; 
            }
            case 'a': /* WAIT */ 
            {
                int argSize = 0;
                int subcmd_index;
                char* end_check;

                for (int i= 0; optind < argc; optind++)
                {
                    // Go through command args until we reach a new option
                    if(argv[optind][0] == '-' && argv[optind][1] == '-')
                    {
                        break;
                    }
                    if(argSize == 1)
                    {
                        fprintf(stderr,"ERROR: Wait requires a single argument.");
                        exitStatus = 1;
                        break;
                    }
                    
                    subcmd_index = strtol(argv[optind], &(end_check),0);
                    if(end_check == argv[optind]) // Not a digit
                    {
                        fprintf(stderr,"ERROR: Argument is not a digit! \n");
                        exitStatus = 1;
                    }
                    argSize++;
                }

                if(argSize == 0)
                {
                    if(verboseTrue == 1)
                    {
                        printf("--wait \n");
                        fflush(stdout);
                    }
                   /* if( p_wait(-1) == -1 )
                        fprintf(stderr, "ERROR: Unable to wait on a process");*/
                }
                else
                {

                    if(verboseTrue == 1)
                    {
                        printf("--wait %d", subcmd_index);
                        fflush(stdout);
                    }
                
                   /* if(p_wait(subcmd_index) == -1){
                        fprintf(stderr, "ERROR: Unable to wait on a process");
                        exitStatus = 1;
                    } */
                }

 
            }
            case 'o': /* PIPE */ 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                if (create_pipe() == -1)
                    fprintf(stderr,"ERROR: Unable to create a pipe");
                break; 
            }
            case 'z': /* ABORT */
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                volatile int *a = NULL;
                int b = *a;
                break; 
            }
            case 'g': /* CATCH */ 
            {
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                    fprintf(stderr, "option '--catch' requires an argument \n");
                    exitStatus = 1;
                    break;
                }

                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);
                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }

                struct sigaction catch_struct;
                catch_struct.sa_sigaction = catch_handler;
                sigemptyset(&catch_struct.sa_mask);
                catch_struct.sa_flags = 0;
                char* catchEnd;
                sigaction(strtol(optarg, &catchEnd, 0), &catch_struct, NULL);
                break; 
            }
            case 'q': /* IGNORE */ 
            {
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                    fprintf(stderr, "option '--ignore' requires an argument \n");
                    exitStatus = 1;
                    break;
                }

                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);

                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }

                struct sigaction sig_struct;
                sig_struct.sa_sigaction = sig_handler;
                sigemptyset(&sig_struct.sa_mask);
                sig_struct.sa_flags = 0;
                char* ignoreEnd;
                //need to chekc if optarg exists first?
                sigaction(strtol(optarg, &ignoreEnd, 0), &sig_struct, NULL);
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
            }
            case 'u': /* DEFAULT */ 
            {
                if (optarg[0] == '-' && optarg[1] == '-')
                {
                    verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                    fprintf(stderr, "option '--default' requires an argument \n");
                    exitStatus = 1;
                    break;
                }

                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);

                if ((optind < argc && argv[optind][0] != '-'))
                {
                    exitStatus = 1;
                }

                char* defEnd;
                signal (strtol(optarg, &defEnd, 0), SIG_DFL);
                break;
            }
            case 'h': /*PAUSE */ 
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
                pause();
                break;
            }
            case 'j': /*CLOSE*/ 
            {
                verbosePrint(verboseTrue, argv[optind - 2], optarg, 1);
                int tmp;
                char* end2;
                tmp = strtol(optarg, &end2,0);
                if(end2 == optarg) // Not a digit
                {
                    fprintf(stderr,"ERROR: Argument is not a digit! \n");
                    exitStatus = 1;
                }

                if(close_fd(tmp) == -1)
                {
                    fprintf(stderr, "ERROR: File is already closed.");
                }

                
                break;
            }
            case 'm': /* PROFILE */
            {
                verbosePrint(verboseTrue, argv[optind - 1], optarg, 0);
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

