#include <stdio.h>
#include <stdlib.h>
#include "trip_logs.h"
#include "duplicate_ll.h"


struct duplicate_ll* insert_duplicate(struct duplicate_ll* head, struct trip* trip){

	printf("\n Trip received, Duration: %s\n",trip->trip_duration );
	// //find the next available node space to insert duplicate trip in
	// 
	if(!head){
		head = (struct duplicate_ll*)malloc(sizeof(struct duplicate_ll));
		head->next = NULL;
		head->duplicate_trip = trip;
	} else {
		struct duplicate_ll* tail;
		tail = head;
		while(tail){
		tail = tail->next;
		}
		tail = (struct duplicate_ll*)malloc(sizeof(struct duplicate_ll));
		tail->next = NULL;
		tail->duplicate_trip = trip;
	}
	

	return head;
}

void print_duplicates(struct duplicate_ll* head){
	while(head){
		printf("\n\nKey: %s %s<<<<<<<<<<<<<<<\n", ((head->duplicate_trip)->trip_duration), ((head->duplicate_trip)->vendor_id));
		head = head->next;
	}
}
