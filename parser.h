#ifndef PARSER_H
#define PARSER_H

#include <getopt.h>


static struct option long_options[] = 
{
    // FILE FLAGS:
    {"append",      no_argument, 0, 'p'},
    {"cloexec",     no_argument, 0, 'x'},
    {"creat",       no_argument, 0, 'e'},
    {"directory",   no_argument, 0, 'i'},
    {"dsync",       no_argument, 0, 'n'},
    {"excl",        no_argument, 0, 'l'},
    {"nofollow",    no_argument, 0, 'f'},
    {"nonblock",    no_argument, 0, 'b'},
    {"rsync",       no_argument, 0, 'y'},
    {"sync",        no_argument, 0, 's'},
    {"trunc",       no_argument, 0, 't'},    
    
    // FILE OPENING:
    {"rdonly",      required_argument, 0, 'r'},
    {"wronly",      required_argument, 0, 'w'},
    {"rdwr",        required_argument, 0, 'd'},
    {"pipe",        no_argument,       0, 'o'},

    // SUBCOMMANDS
    {"command",     required_argument, 0, 'c'},
    {"wait",        optional_argument, 0, 'a'}, 
   
    // MISC:
    {"close",       required_argument, 0, 'j'},
    {"verbose",     no_argument,       0, 'v'},
    {"profile",     no_argument,       0, 'm'},
    {"abort",       no_argument,       0, 'z'},
    {"catch",       required_argument, 0, 'g'},
    {"ignore",      required_argument, 0, 'q'},    
    {"default",     required_argument, 0, 'u'},
    {"pause",       no_argument,       0, 'h'},

    {0,             0,                 0,  0} 
};

/////////////////////////////////
/*  PARSER FUNCTIONS */
/////////////////////////////////
int parser(int argv, char** argc);

#endif 
