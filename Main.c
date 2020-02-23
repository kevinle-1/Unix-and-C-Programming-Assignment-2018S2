/**
 *  Main.c
 *  17/10/2018
 *  Kevin Le - 19472960
 */

#include <stdio.h>
#include"FileIO.h"

/**
 * IMPORTS: 
 *      User command line arguments
 * 
 * ASSERTION: 
 *      Begins program, calls readFile() to start process of running commands.
 */
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Invalid number of arguments!\n");
    }
    else
    {
        readFile(argv);
    }

    return 0; 
}
