#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>


static struct option long_options[] = 
{
    // FILE FLAGS:
    {"append", no_argument, 0 'p'},
    {"cloexec", no_argument, 0, 'x'},
    {"creat", no_argument, 0 'e'},
    {"directory", no_argument, 0, 'i'},
    {"dsync", no_argument, 0 'n'},
    {"excl", no_argument, 0, 'l'},
    {"nofollow", no_argument, 0 'f'},
    {"rsync", no_argument, 0, 'y'},
    {"sync", no_argument, 0 's'},
    {"trunc", no_argument, 0, 't'},    
    
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
