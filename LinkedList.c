/**
 *  LinkedList.c
 *  17/10/2018
 *  Kevin Le - 19472960
 */

#include"LinkedList.h"

/**
 * IMPORTS: N/A
 * 
 * EXPORTS:
 *      Linked List 
 * 
 * ASSERTION
 *      Returns a new Linked List when called. 
 */
LinkedList* newList()
{
    /*Allocate memory for a new empty Linked List. Containing a head and tail*/ 
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

    /*Set head (first) and tail (last) to NULL (Nothing in list yet)*/
    list->head = NULL;
    list->tail = NULL;

    /*return initialized list back to calling function.*/
    return list; 
}

/**
 * IMPORTS: 
 *      LinkedList to insert newNode. 
 *      Data struct to point value of newNode to. 
 *
 * ASSERTION: 
 *      Function to create and insert a newNode with a pointer to the Data struct, mallocs
 *      memory for a new node, then points nodeData() in node struct to the address of cmdLine
 *      (a Data Struct). 
 *
 * Based on code from Curtin University Department of Computing, Data Structures and Algorithms (COMP1002)
 * "Lecture 4: Linked Lists, Insert Last Pseudocode" (2017) - (Accessed 9 Oct 2018)
 */
void insertLast(LinkedList* list, Data* cmdLine)
{
    /*Allocate memory for a new node, to be inserted into the Linked List*/
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    /*Point nodeData of node to address of cmdLine struct*/ 
    newNode->nodeData = cmdLine; 
    /*nodes next is null, no node after it.*/ 
    newNode->next = NULL; 
    
    /*If it is an empty linked list, then make the head and tail point to the new node. */
    if(list->head == NULL)
    {
        list->head = newNode; 
        list->tail = newNode; 
    }
    /*If it is not empty, set the current tails next value to the new node to be inserted.
    Then set new node as the new tail. */
    else
    {
        list->tail->next = newNode; 
        list->tail = newNode; 
    }
}

/**
 * IMPORTS: 
 *      Linked List to print out. 
 * 
 * ASSERTION: 
 *      Prints values of Linked List Node in Linked List. 
 */ 
void printList(LinkedList* list)
{
    /*Creates a new node, set to the lists head. */
    LinkedListNode* current = list->head; 

    /*Starts while loop, if the end of the linked list hasn't been reached yet. Print the nodeData contents.*/
    while(current != NULL)
    {
        printf("%s %s\n", current->nodeData->command, current->nodeData->value);

        /*Set current to the next node.*/ 
        current = current->next; 
    }
}

/**
 * IMPORTS: 
 *      Linked List to free
 * 
 * ASSERTION: 
 *      Frees the linked list, nodes in the linked list, and any data in the linked list that requires freeing. 
 */ 
void freeList(LinkedList* list) 
{
    /*Creates a new node, set to the lists head.*/
    LinkedListNode *current = list->head;

    /*Create a temporary variable to facilitate deleting nodes*/ 
    LinkedListNode* temp;

    /*Iterate through linked list, node by node.*/ 
    while(current != NULL)
    {
        /*Free command malloc at nodeData*/ 
        free(current->nodeData->command);
        /*Free value malloc at nodeData*/ 
        free(current->nodeData->value); 

        /*Free command struct at nodeData (cmdLine)*/ 
        free(current->nodeData); 

        /*Point the current node to a temporary node*/ 
        temp = current;

        /*set current node to the next node*/ 
        current = current->next;

        /*free the temporary node (now the previous node)*/ 
        free(temp);
    }
    /*Free the list*/ 
    free(list); 
}

        
