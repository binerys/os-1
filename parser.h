#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>


static struct option long_options[] = 
{
    // FILE FLAGS:
    
    // FILE OPENING:
    {"rdonly", required_argument, 0, 'r'},
    {"wronly", required_argument, 0, 'w'},
    {"rdwr", required_argument, 0, 'd'},
   
    // SUBCOMMANDS
    {"command", required_argument, 0, 'c'},
    {"wait", no_argument,0,'a'}, 
   
    // MISC:
    {"verbose", no_argument, 0, 'v'},

    {0,0,0,0} 
};

/////////////////////////////////
/*  PARSER FUNCTIONS */
/////////////////////////////////
int parser(int argv, char** argc);

#endif 
