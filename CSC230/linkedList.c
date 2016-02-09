#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	// Node for building trees. 
	struct NodeTag { // Value in this node. 
	int value; // Pointer to the left and right subtrees. 
	struct NodeTag *left, *right; }; // A short type name to use for a node. 

	typedef struct NodeTag Node;  // Building a little tree on the stack. 

	Node n1 = { 20, NULL, NULL }; 
	Node n3 = { 85, NULL, NULL }; 
	Node n2 = { 57, &n1, &n3 }; // A pointer to the root node. 
	Node *root = &n2; // A pointer to the root pointer. 
	Node **rootPtr = &root;


	int val = root->right->value;
	int val2 = (*rootPtr)->left->value;
	printf("%d\n", val );
	printf("%d\n", val2 );
}