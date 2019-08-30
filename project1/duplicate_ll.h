#ifndef DUPLICATE_LL_H
#define DUPLICATE_LL_H
/*
Header file for duplicate_ll.c includes linked list structure and functional definitions
Purpose is to link together duplicates when inserting into the bst dictionary
Structure
Function declarations
*/

struct duplicate_ll{
	struct trip* duplicate_trip;
	struct duplicate_ll* next;
};

struct duplicate_ll* insert_duplicate(struct duplicate_ll* head, struct trip* trip);

void print_duplicates(struct duplicate_ll* head);

#endif
