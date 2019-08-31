#include <stdio.h>
#include <stdlib.h>
#include "trip_logs.h"
#include "duplicate_ll.h"


struct duplicate_ll* insert_duplicate(struct duplicate_ll* head, struct trip* trip){

	// printf("\n Trip received, Duration: %s\n",trip->trip_duration );
	// //find the next available node space to insert duplicate trip in
	// 
	if(head == NULL){
		head = (struct duplicate_ll*)malloc(sizeof(struct duplicate_ll));
		head->next = NULL;
		head->duplicate_trip = trip;
	} else {
		struct duplicate_ll* tail;
		tail = head;

		while((tail->next)!=NULL){
		tail = tail->next;
		}

		tail->next = (struct duplicate_ll*)malloc(sizeof(struct duplicate_ll));
		tail = tail->next;
		tail->next = NULL;
		tail->duplicate_trip = trip;
	}
	

	return head;
}

void print_duplicates(struct duplicate_ll* head){
	struct duplicate_ll* temp;
	temp = head;
	puts("Printing duplicate LL so far: ");
	while(temp){
		printf("cKey: %s %s\n", ((temp->duplicate_trip)->trip_duration), ((temp->duplicate_trip)->vendor_id));
		temp = temp->next;
	}
}

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
