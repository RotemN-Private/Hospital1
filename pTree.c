#include <stdlib.h>
#include "common.h"
#include "pTree.h"


void insertNode(plnTree* root, Patient* patient);
void freeTree(plnTree* root);
plnTree* createBstNode(plnTree* left, plnTree* right, Patient* patient);
int isBstEmpty(pTree* tree);
//int heightTree(plnTree* root);//IMPLEMENT THIS

plnTree* createBstNode(plnTree* left, plnTree* right, Patient* patient)
{
	plnTree* newNode = calloc(1, sizeof(plnTree));//Rotem calloc or malloc?
	if (newNode != NULL)
	{
		newNode->tpatient = patient;
		newNode->left = left;
		newNode->right = right;
	}

	return newNode;
}


void insertNode(plnTree* root, Patient* patient)
{
	if (atoi(patient->ID) <= atoi(root->tpatient->ID)) //Rotem: I changed to atoi
	{
		if (root->left == NULL)//no left child
			root->left = createBstNode(NULL, NULL, patient);
		else insertNode(root->left, patient);
	}
	else
	{
		if (root->right == NULL)//no right child
			root->right = createBstNode(NULL, NULL, patient);
		else insertNode(root->right, patient);
	}
}

/*void freeTree(plnTree* root)
{
	if (root == NULL) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}*/

void freePatient(Patient* patient) {
/*	if (patient == NULL) return;
	free(patient->name);
	for (int i = 0; i < patient->nVisits; i++) {
		Visit* visit = &patient->Visits[i];
		free(visit->vSummary);
	}
	free(patient->Visits);
	free(patient);*/
}

void freeTree(plnTree* node) {
	if (node == NULL) return;
	freeTree(node->left);
	freeTree(node->right);
	freePatient(node->tpatient);
	free(node);
}

void initBST(pTree* tree)
{
	tree->root = NULL;
}


void insertBST(pTree* tree, Patient* patient)
{
	if (isBstEmpty(tree))
	{
		tree->root = createBstNode(NULL, NULL, patient);
		return;
	}

	insertNode(tree->root, patient);
}

void destroyBST(pTree* tree)
{
	freeTree(tree->root);
}

//int find(BST* tree, int toFind);

int isBstEmpty(pTree* tree)
{
	return tree->root == NULL;
}
/*
void printBST(pTree* tree)
{
	print_ascii_tree(tree->root);
}

int getHeight(pTree* tree)
{
	return heightTree(tree->root);
}
*/