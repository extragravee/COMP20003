/*
Binary Search Tree implementation:
Structures
Functions
Function declerations abstracted to header file "bst.h"
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"


struct bst{
	struct bst* left;
	struct bst* right;
	char *key;
	struct record* trip;
};

struct bst* insert_node(struct bst* parent, struct trip* new_trip){


}

void free_tree(struct bst* parent){

	
}



