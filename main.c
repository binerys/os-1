#include "parser.h"

int exit_status;

int main(int argc, char** argv)
{
    exit_status = parser(argc, argv);


    exit(exit_status);    
}
