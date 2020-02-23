/**
 *  RunCmd.c
 *  17/10/2018
 *  Kevin Le - 19472960
 */

#include<math.h>
#include<stdio.h>
#include<string.h>
#include"LinkedList.h"

/*Define constant Pi*/ 
#define M_PI 3.14159265358979323846

/*Define Degrees to Radian conversion macro*/ 
#define RAD(deg) ((deg) * ((M_PI)/(180.0)))

/*Define constant for max sizes expected for command and value (used when mallocing sizeof(char))*/ 
#define CMDSIZE 8
#define VALSIZE 5

/*Struct to keep track of constantly changing data*/ 
typedef struct Info
{
    double currAngle;

    int y2;
    int x2;

    int y1;
    int x1;

    char currPattern; 

    int currFG;
    int currBG;

} Info; 

void runCmd(LinkedList* list, int numLines);
void updateCoord(double d, Info* data, int type);
void plotter(void* plotData);
int roundValue(double value);
int validateSScanf(int success, int required);