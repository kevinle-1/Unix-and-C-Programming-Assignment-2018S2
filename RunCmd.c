/**
 *  RunCmd.c
 *  17/10/2018
 *  Kevin Le - 19472960
 */

#include"RunCmd.h"
#include"effects.h"
#include"FileIO.h"

/**
 * IMPORTS: 
 *      Linked List containing node pointing to structs containing commands to be read. 
 *      Number of lines successfully read from the file. 
 * 
 * ASSERTION: 
 *      Iterates through linked list, reading each nodeValue, validating and determinining command to run. 
 * 
 * ROTATE - append ROTATE comamnd value to data->currAngle
 * MOVE/DRAW - see updateCoord() comment block. 
 * FG - calls setFgColour
 * BG - calls setBgColour
 * PATTERN - sets data->currPattern to PATTERN command value
 */

void runCmd(LinkedList* list, int numLines)
{
	/*Point the PlotFunc to address of the function plotter*/
    PlotFunc funcPtr = &plotter; 
    
    #ifndef SIMPLE
    int iValue; 
    #endif

    /*Values for sscanf to be assigned to*/ 
    double rValue; 
    char cValue; 
    FILE* append;
    int read; 

    /*valid condition for while loop to check, to cont. or stop. If invalid command found, program exited.*/ 
    int valid = 1; 

    /*Set current node pointer to the head.*/ 
    LinkedListNode* current = list->head; 

    /*Init a struct called Info to keep track of the changing values (angle, x1, y1, x2, y2,
    pattern, fg, bg). Used to update values and parse to functions*/
    Info* data = (Info*)malloc(sizeof(Info));

    /*Initialize struct keeping track of data to default values*/
    data->currAngle = 0.0;
    data->x1 = 0;
    data->y1 = 0; 
    data->x2 = 0; 
    data->y2 = 0;
    data->currPattern = '+';
    data->currFG = 7; 
    data->currBG = 0; 

    /*Set BG to black, FG to white if SIMPLE defined*/ 
    #ifdef SIMPLE
    setFgColour(0);
    setBgColour(15);
    #endif

    printf("Running commands\n");
    append = fopen("graphics.log", "a");

	/*Append to graphics.log a new seperator, as it is new run*/ 
    fprintf(append, "%s\n","---");

    /*Clear screen to prep printing.*/ 
    clearScreen(); 

    /*note: if %lf changed to %f - charizard fails to print
    
    Iterates through each node in the list, Head to tail order (first to last), checking commands in 
    if-else-if conditions if a command is matched its value (currently a string) is retrieved using sscanf 
    and typecast into required datatype then required operation is run.*/
    while(current != NULL && valid == 1)
    {
        if(strcmp(current->nodeData->command, "ROTATE") == 0)
        {
            read = sscanf(current->nodeData->value, "%lf", &rValue);
            /*append ROTATE command angle on top of current angle.*/

            valid = validateSScanf(read, 1); 
            data->currAngle += rValue; 
        }

        else if(strcmp(current->nodeData->command, "MOVE") == 0)
        {
            read = sscanf(current->nodeData->value, "%lf", &rValue);
            /*Calls updateCood() to update X/Y values with MOVE command value*/ 

            /*Check if sscanf has read in the correct number of variables, allowing the while loop to continue iterating*/
            if((valid = validateSScanf(read, 1)) == 1)
            {
                /*calls updateCoord passing in data struct, modifies relevant x/y values using MOVE command value*/ 
                updateCoord(rValue, data, 0);
            }
        }

        else if(strcmp(current->nodeData->command, "DRAW") == 0)
        {
            read = sscanf(current->nodeData->value, "%lf", &rValue);
            /*Calls updateCood() to update X/Y values with DRAW command value*/ 

            if((valid = validateSScanf(read, 1)) == 1)
            {
                /*Decrease distnace by 1 to prevent double print*/
                updateCoord(rValue-1, data, 1);

                /*Draws line using struct data passing in origin point to destination point. 
                function pointer, and currPattern*/ 
                line(data->x1, data->y1, data->x2, data->y2, *funcPtr, &data->currPattern);

                /*Move cursor along by 1 to prevent double print*/ 
                updateCoord(1, data, 2);
            }
        }

        /*FG/BG commands ignored if SIMPLE defined*/
        else if(strcmp(current->nodeData->command, "FG") == 0)
        {
            #ifndef SIMPLE
            read = sscanf(current->nodeData->value, "%d", &iValue);

            /*Validate if successfully read command*/ 
            if((valid = validateSScanf(read, 1)) == 1)
            {
                setFgColour(iValue);               
            }
            #endif
        }

        else if(strcmp(current->nodeData->command, "BG") == 0)
        { 
            #ifndef SIMPLE
            sscanf(current->nodeData->value, "%d", &iValue);

            /*Validate if successfully read command*/ 
            if((valid = validateSScanf(read, 1)) == 1)
            {
                setBgColour(iValue);               
            }
            #endif
        }

        else if(strcmp(current->nodeData->command, "PATTERN") == 0)
        {
            sscanf(current->nodeData->value, "%c", &cValue);
            /*sets current pattern as PATTERN value*/ 
 
            if((valid = validateSScanf(read, 1)) == 1)
            {
                /*set current pattern to new pattern*/ 
                data->currPattern = cValue;              
            }
        }
        else
        {
            /*Command is invalid. Quit the program and free everything*/
            printf("Invalid command found! Exiting.\n");

            /*set valid condition to 0, exits while loop*/ 
            valid = 0; 
        }

        /*if no invalid command is found, continue to next node*/ 
        if(valid == 1)
        {
            current = current->next;
        }
        else
        {
            printf("Invalid command value! Exiting.\n");
        }
    }
    
    fclose(append);
    free(data); 

    /*Drawing successfully completed if valid stays at 1. Therefore finish up*/ 
    if(valid == 1)
    {
        penDown(); 
        printf("Done\n");
    }
}

/**
 * IMPORTS:
 *      Success - Integer returned by sscanf (Number of successfully read values)
 *      Required - Parameter manually set in calling function. Number of values sscanf should HAVE successfully read. 
 * 
 * ASSERTION: 
 *      Returns 1 if sscanf read correctly, 0 if not. 
 */
int validateSScanf(int success, int required)
{
    int retVal = 0; 

    /*check if sscanf matches assertion*/ 
    if(success == required)
    {
        retVal = 1; 
    }
    
    return retVal; 
}

/**
 * IMPORTS: 
 *      d - Value of command. (e.g. MOVE 5, d = 5)
 *      Info* data - data struct with values to update/ append
 *      type - Integer to allow FileIO.c writeTo() to determine what command was run to print. 0 = MOVE, 1 = DRAW, 2 = IGNORE
 * 
 * ASSERTION: 
 *      Updates the X/Y Coordinates.  
 */

void updateCoord(double d, Info* data, int type)
{
    /*Real static variables for writing to the log file, need a seperate variable due
    to data struct having values stored as real, while log file requires reals
    --
    Use of Static variable to make it easier to append, instead of requiring loop as it
    stays in one function*/

    double logX1;
    double logY1;
    static double logX2;
    static double logY2;

    /*Radians required*/
    double radian; 
    double resultX, resultY;

    /*Retrieves current angle from struct, using macro RAD to convert to radians, 
    stores in variable radians. */
    radian = RAD(data->currAngle); 

    /*uses a seperate log variable to keep track of the REAL values to write*/ 
    logX1 = logX2;
    logY1 = logY2;

    /*Sets x1, y1 of Data struct to current x2, y2 values 
    (e.g. the origin/ previous point to draw/move from after previous draw/move was finished).*/ 
    data->x1 = data->x2;
    data->y1 = data->y2;

    /*Runs COS/ SIN calculation for X/Y, storing result into resultX/resultY*/ 
    resultX = d*(cos(radian)); 
    resultY = d*(sin(radian));

    /*appends real resultX/resultY to Log variables*/ 
    logX2 += resultX; 
    logY2 -= resultY; 
    
    /*Appends rounded resultX/resultY Integers (after parsed to roundValue) to data struct x2, y2*/
    data->x2 += roundValue(resultX); 
    data->y2 -= roundValue(resultY); 

    /*If the move command meant to resolve the double printing wasn't run*/ 
    if(type != 2)
    {
        /*Sends log variables to writeTo to write calculation to logfile.*/
        writeTo(logX1, logY1, logX2, logY2, type);
    }
}

/**
 * IMPORTS: void pointer to accomodate any datatype that can be printed
 * 
 * Prints plotData.
 */ 
void plotter(void* plotData)
{
    printf("%c", *((char *) plotData)); 
}

/**
 * IMPORTS: 
 *      Real value to round.
 * 
 * EXPORTS:
 *      Rounded value as an integer. 
 * 
 * ASSERTION: 
 *      Rounds value to nearest integer. e.g. 1.2 -> 1, 2.6 -> 3. 
 * 
 * Algorithm based on Marcelo Cantos' answer via Stack Overflow, "How to round floating point 
 * numbers to the nearest integer in C?" 
 * https://stackoverflow.com/questions/2570934/how-to-round-floating-point-numbers-to-the-nearest-integer-in-c
 * (Accessed 10 Oct 2018).
 */
int roundValue(double value)
{
    double retVal; 
    /*If value is positive, add 0.5 to it, if > .5 then it will round to the next highest integer
     if it is < .5 it will round to the closest integer. Gets rounded after typecast to Integer. */
    if(value < 0)
    {
        retVal = value - 0.5; 
    }
    else
    {
        retVal = value + 0.5; 
    }

    return (int)retVal; 
}