/*
Created by Sidakpreet Mann - 921322
sidakpreetm@student.unimelb.edu.au

Header file for duplicate_ll.c includes linked list structure and functional definitions
Purpose is to link together duplicates when inserting into the bst dictionary
Structure
Function declarations
*/

#ifndef DUPLICATE_LL_H
#define DUPLICATE_LL_H

/*
structure of linked list node
*/
struct duplicate_ll{
	struct trip* duplicate_trip;
	struct duplicate_ll* next;
};

/*
inserts trip record when duplicate key detected
*/
struct duplicate_ll* insert_duplicate(struct duplicate_ll* head, struct trip* trip);

/*
prints out all duplicates starting at the first duplicate
*/
void print_duplicates(struct duplicate_ll* head, FILE* out_file);


/*
frees entire linked list built for duplicates at a starting node
*/
void free_duplicates(struct duplicate_ll* head);

#endif
