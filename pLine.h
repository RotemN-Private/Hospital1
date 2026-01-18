#ifndef pLine_h
#define pLine_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"
 /*
#define LIST_END NULL
#define EMPTY_LIST NULL

#define LIST_POINTER_ERROR "Error - NULL pointer.\n"
#define BAD_ALLOC "Error - allocation error.\n"
*/
/*
Queue
- patient that in line for emergency room
- lpatient - pointer to struct Patient 
*/
typedef struct plnLine {
	Patient* lpatient;
	struct plnLine* next;
} plnLine;

/*
Struct Line is the managing structure for the ADT List
Head - pointer to an sll plnLine. this is the list's head
Tail - pointer to an sll plnLine. this is the list's tail
 */
typedef struct pLine {
	struct plnLine* head; //!< pointer to an sll Node. this is the list's head
	struct plnLine* tail; //!< pointer to an sll Node. this is the list's tail
} pLine;

#endif //pLine_h 