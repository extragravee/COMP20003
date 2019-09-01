/*
Provides the skeleton tasks for the project
1. Opens a file
2. Facilitates creation of trip objects
3. Adds trip objects to the BST dictionary (handles duplicates with linked list), then closes file
4. Opens output file, performs search and writes to output file
5. Closes file and frees all memory being used by the tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bst.h"

int main(int argc, char** argv){
	//reads input file and returns bst dictionary
	struct bst* bst = NULL;
	bst = construct_bst(argc, argv);
	// traverse_tree(bst);

	//free out all temporary pointers and buffers	
	free_tree(bst); 
	return 0;
}