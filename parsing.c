#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char** argv)
{
    while (1)
    {
        int a;  
        int fd;      

        static struct option long_options[] = 
        {
            {"rdonly", required_argument, 0, 'r'}
            {"wronly", required_argument, 0, 'w'}
            {"command", required_argument, 0, 'c'}
            {"verbose", no_argument, 0, 'v'} 
        };
        
        a = getopt_long (argc, argv, "", long_options, &option_index)
        if (a == -1)
            break;
        
        switch(a)
        {
            case 'r':
                //do I need a printf here? 
                fd = open_rdonly_file(optarg);
                handle_filedesc(fd); 
                break;
            case 'w':
                fd = open_wronly_file(optarg);
                handle_filedesc(fd);
                break;
            case 'c':
                break;
            case 'v':
                break;
            default:
                abort();
        }

    }    
}
