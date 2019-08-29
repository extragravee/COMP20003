/*
Binary Search Tree implementation:
Structures
Functions
Function declerations abstracted to header file "bst.h"

Code here has been adapted from Worksheet3 and the authors of Worksheet 3 provided to us
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bst.h"

struct bst{
	struct bst* left;
	struct bst* right;
	char* key;
};

struct bst; 

/*
Takes parent pointer (null for the root), and returns tree with the 
inserted node at the right position. Returns item in tree with it's
left and right pointers set to NULL
*/
struct bst* insert_node(struct bst* parent, struct trip* new_trip);

/*
Takes node pointer and frees all of its children and itself
by default (if pointer is NULL), does nothing
frees children recursively
*/
void free_tree(struct bst* parent);
/* inserts a new node into the bst dictionary */
struct bst* insert_node(struct bst* parent, struct trip* trip){
	int result;

	//pointer to the insert location
	struct bst** insert_here = &parent;

	//till an empty node isn't reached, keep looking
	while(*insert_here != NULL){
		//if new node's key >, go right, if < go left, if == then add node in linkedlist
		// result = strcmp((new_trip->pu_datetime), ((*insert_here)->key));
		result = strcmp((trip->pu_datetime), ((*insert_here)->key));
		if(result < 0){
			insert_here = &((*insert_here)->left);
		} else if(result > 0){
			insert_here = &((*insert_here)->right);
		} else {
			/*IMPLEMENT LINKED LIST HERE*/
			printf("Duplicate! Handle!");
			return parent;
		}
	}
	(*insert_here)->left = NULL;
	(*insert_here)->right = NULL;
	(*insert_here)->key = trip->pu_datetime;
	(*insert_here)->trip = trip;

	printf("New node inserted! Key: %s, Trip: %s", trip->pu_datetime, trip->trip_distance);
	return parent;
}

/* recursively free the nodes of the tree */
void free_tree(struct bst* parent){
	if(!parent){
		return;
	}
	free_tree(parent->left);
	free_tree(parent->right);
	free_members_of_struct(parent->trip); //first free all members of the struct
	free(parent); //then free the struct
}



