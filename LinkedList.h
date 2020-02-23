/**
 *  LinkedList.c
 *  17/10/2018
 *  Kevin Le - 19472960
 */

#include <stdlib.h>
#include <stdio.h> 

/*Node contents of linked list*/ 
typedef struct LinkedListNode
{
    struct Data* nodeData; 
    struct LinkedListNode* next;
} LinkedListNode;

/*Main linked list, containing pointer to head node and tail node*/ 
typedef struct LinkedList
{
    LinkedListNode* head;
    LinkedListNode* tail; 
} LinkedList;

/*Struct that holds command and value of command. */ 
typedef struct Data
{
    char* command; 
    char* value; 
} Data; 

/*Create new list*/ 
LinkedList* newList();
/*Insert at the end of linked list. (Only have insertLast as only insert that places items
  in linked list in correct order. Insert first would never be used.)*/ 
void insertLast(LinkedList* list, Data* cmdLine);
/*Iterates list printing Data struct at each node*/ 
void printList(LinkedList* list);
/*Iterates through list freeing Data structs, then node, then linked list*/ 
void freeList(LinkedList* list);
