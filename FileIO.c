/**
 *  FileIO.c
 *  17/10/2018
 *  Kevin Le - 19472960
 */

#include"FileIO.h"
#include"RunCmd.h"

/**
 * IMPORTS: 
 *      argv[] - Command line arguments array via Main
 * 
 * ASSERTION: 
 *      Opens file, reads contents, storing in struct, inserting into a LinkedList, calling runCmd(). 
 */

void readFile(char* argv[])
{
    FILE* inputFile;
    char line[15];

    /*Max command length would be 8 - Include N.T.*/ 
    char cmd[CMDSIZE];
    int numLines = 0;
    char val[VALSIZE]; 

    /*Open file specified by user*/
    inputFile = fopen(argv[1], "r");

    /*Check if Opening succeeded*/
    if(inputFile == NULL)
    {
        printf("Error opening file!\n");
    }
    else
    {
        /*LinkedList.c function newList() to initialize new list*/
        LinkedList* list = newList();  

        printf("Reading in commands\n");

        /*For the entire length of the file - Use of fgets() to read line */
        while(fgets(line, 15, inputFile) != NULL)
        {
            /* Data struct used to store the COMMAND and VALUE as Strings - Malloc in loop
             * The struct is to inserted into the linked list in a node.
             */
            Data* cmdLine = (Data*)malloc(sizeof(Data)); 

            /*read files from line - sscanf() to split line on String. */ 
            sscanf(line, "%s %s", cmd, val);

            /*Malloc memory for COMMAND and VALUE located inside Data struct*/ 
            cmdLine->command = malloc(CMDSIZE * sizeof(char));
            cmdLine->value = malloc(VALSIZE * sizeof(char));

            /*Convert command to Upper Case*/
            toUpper(cmd); 

            /*Copy values into COMMAND/VALUE inside Data Struct*/ 
            strcpy(cmdLine->command, cmd); 
            strcpy(cmdLine->value, val);

            /*Call insertLast() function in LinkedList.c to add node on end of list pointing to Data struct.*/ 
            insertLast(list, cmdLine); 

            numLines++; 
        }
        fclose(inputFile);

        /*Pass list to runCmd to run commands*/
        runCmd(list, numLines);

        freeList(list);
    }
}

/**
 * IMPORTS: 
 *      Takes Origin (x1, y1) to Destination (x2, y2) real valued coordinates.
 *      Parametre type (0, 1).
 * 
 * ASSERTION:
 *      Writes to log file in the format COMMAND(x1, y1)-(x2, y2)
 */
void writeTo(double x1, double y1, double x2, double y2, int type)
{
    FILE* logFile = NULL; 
    char cmd[10];

    /*Uses a type parametre to determine what command was called and to print. 0 = MOVE, 1 = DRAW.*/ 
    if(type == 0)
    {
        strcpy(cmd, "MOVE");
    }
    else if(type == 1)
    {
        strcpy(cmd, "DRAW");
    }
    else
    {
        strcpy(cmd, "INVALID");
    }

    /*opens file to append to, mode "a"*/
    logFile = fopen("graphics.log", "a");

    /*if successfully opened*/ 
    if(logFile != NULL)
    {
        /*Takes the real valued coordinates calculated in RunCmd.c function updateCoord() and appends to file
        uses width and precision specifier to pad with spaces/ decimal accuracy of 3d.p.*/ 
        fprintf(logFile, "%s (%7.3f, %7.3f)-(%7.3f, %7.3f)\n", cmd, x1, y1, x2, y2);
    }
    else
    {
        printf("Error Writing LogFile!");
    }

    /*If DEBUG is defined, print the DRAW log to the screen*/ 
    #ifdef DEBUG 
    if(type == 1)
    {
        fprintf(stderr, "%s (%7.3f, %7.3f)-(%7.3f, %7.3f)", cmd, x1, y1, x2, y2);
    }
    #endif

    fclose(logFile);
}

/**
 * IMPORTS: 
 *      Character array (String).
 * 
 * ASSERTION: 
 *      Changes all characters in array to uppercase. Ensures uniform case for all commands, 
 *      so strcmp() in RunCmd.c has no issues. 
 * 
 * Obtained from Programming Simplified, "C program to change case of a string",
 * https://www.programmingsimplified.com/c/program/c-program-change-case (accessed 12 Oct 2018). 
 */
void toUpper(char string[]) 
{
    int c = 0; 

    /*While the character array hasn't ended*/ 
    while (string[c] != '\0') 
    {
        /*For each lowercase value */
        if (string[c] >= 'a' && string[c] <= 'z') 
        {
            /*subtracts a value of 32 from the ASCII value of the lowercase character to convert to Upper.*/
            string[c] = string[c] - 32;
        }

        c++;
    }
}
