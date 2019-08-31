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
#include "trip_logs.h"
#include "bst.h"
#include "duplicate_ll.h"

/* inserts a new node into the bst dictionary */
struct bst* insert_node(struct bst* parent, struct trip* trip){
	int result;

	//pointer to the insert location
	struct bst** insert_here = &parent;
	//till an empty node isn't reached, keep looking
	while(*insert_here != NULL){
		result = strcmp((trip->pu_datetime), ((*insert_here)->key));
	
		if(result < 0){
			insert_here = &((*insert_here)->left);
		} 
		else if(result > 0){
			insert_here = &((*insert_here)->right);
		} 
		else if(result==0){	

			puts("Inserting duplicate: ");
			// printf("%p<<<<<<<<<<\n", (*insert_here)->duplicates);
			printf("New node inserted! Key: %s, Trip: %s\n", trip->pu_datetime, trip->trip_duration);
			(*insert_here)->duplicates = insert_duplicate((*insert_here)->duplicates, trip);
			
			// printf("%p<<<<<<<<<<\n", (*insert_here)->duplicates);
			print_duplicates((*insert_here)->duplicates);
			// free((*insert_here)->duplicates);
			return parent;
		}
	}

	(*insert_here) = (struct bst*)malloc(sizeof(struct bst));
	(*insert_here)->left = NULL;
	(*insert_here)->right = NULL;
	(*insert_here)->key = trip->pu_datetime;
	(*insert_here)->trip = trip;
	printf("\n%p\n", trip);
	(*insert_here)->duplicates = NULL;

	printf("New node inserted! Key: %s, Trip: %s\n", trip->pu_datetime, trip->trip_duration);

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
	free(parent->trip); //free pointer
	free_duplicates(parent->duplicates);
	free(parent); //then free the struct
}

// struct bst* search_dictionary(char* key, struct bst* root){

// }



