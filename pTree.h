#ifndef pTree_h
#define ptree_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common.h"

/*
Binary Search Tree 
 - keeps information of all patients 
 tPatient - info of patient from struct Patient
*/
typedef struct plnTree {
	Patient* tpatient;
	struct plnTree* left;
	struct plnTree* right;
}plnTree;

typedef struct pTree
{
	plnTree* root;
}pTree;

#endif //pTree.h