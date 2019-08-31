/*
Defines functions for the duplicate records that will be inserted from the input file
Function declerations abstracted to header file "trips_log.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "trip_logs.h"
#include "duplicate_ll.h"

/*
if a node already exists with a certain key, then creates linked list of duplicates
*/
struct duplicate_ll* insert_duplicate(struct duplicate_ll* head, struct trip* trip){
	//if no duplicates, make a new node
	if(head == NULL){
		head = (struct duplicate_ll*)malloc(sizeof(struct duplicate_ll));
		assert(head);
		head->next = NULL;
		head->duplicate_trip = trip;
	} 
	//if there are duplicates, go to end of linked list, insert new node
	else {
		struct duplicate_ll* tail;
		tail = head;

		while((tail->next)!=NULL){
		tail = tail->next;
		}

		tail->next = (struct duplicate_ll*)malloc(sizeof(struct duplicate_ll));
		assert(tail->next);
		tail = tail->next;
		tail->next = NULL;
		tail->duplicate_trip = trip;
	}
	
	return head;
}

/*
Prints entire linked list of duplicates in a given node. 
*/
void print_duplicates(struct duplicate_ll* head){
	struct duplicate_ll* temp;
	temp = head;

	while(temp){
		print_trip(temp->duplicate_trip);
		temp = temp->next;
	}
}

/*
free all memory allocated to duplicates in a certain given node
*/
void free_duplicates(struct duplicate_ll* head){
	struct duplicate_ll* temp;

	while(head){
		temp = head;
		head = head->next;
		free_members_of_struct(temp->duplicate_trip);
		free(temp->duplicate_trip);
		free(temp);
	}
}
