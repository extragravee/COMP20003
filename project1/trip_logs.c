/*
Defines the structure and functions for the trip log records provided in
the input file.
Function declerations abstracted to header file "trips_log.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "trip_logs.h"

#define DELIM_REGEX "\r,"
#define SECOND_FIELD 2
#define NULLBYTE_SPACE 1

/* 
1. Accepts the buffer (contains one full trip row from the input data)
2. Transforms it into the a trip struct type object
3. Passes the pointer to this new trip object back to main.c
*/
struct trip* create_trip_record(char *buffer, char* field){ 
	int cell_length;
	int counter = SECOND_FIELD;

	//allocate memory for new trip struct
	struct trip* new_trip = (struct trip*) malloc(sizeof(struct trip));

	//Store first column, must be outside loop due to strtok functionality
	field = strtok(buffer, DELIM_REGEX);
	cell_length = (int)strlen(field); 
	(new_trip->vendor_id) = (char *)malloc((sizeof(char)*cell_length)+NULLBYTE_SPACE);
	strcpy(new_trip->vendor_id, field);

	char **temp;
	while ((field = strtok(NULL, DELIM_REGEX))!=NULL){
		cell_length = (int)strlen(field);
		temp = get_struct_member(new_trip, counter);
		*temp = (char *)malloc(sizeof(char)*cell_length+1);
		strcpy(*temp, field);
		counter++;
	}
	
	return new_trip;
}

void print_trip(struct trip* new_trip){
	int counter = 1;
	puts("Printing=================");
	while(counter<=18){
		char **temp;
		temp = get_struct_member(new_trip, counter);
		printf("%s\n", *temp);
		counter++;
	}
}

void free_members_of_struct(struct trip* trip){
	int counter = 1;

	while(counter<=18){
		char **temp;
		temp = get_struct_member(trip, counter);
		counter++;
		free(*temp);
	}
}

char** get_struct_member(struct trip* new_trip, int i){
	switch(i){
		case 1: return &(new_trip-> vendor_id);
		case 2: return &(new_trip-> passenger_count);
		case 3: return &(new_trip-> trip_distance);
		case 4: return &(new_trip-> rate_code_ID);
		case 5: return &(new_trip-> store_and_fwd_flag);
		case 6: return &(new_trip-> pu_location_id);
		case 7: return &(new_trip-> do_location_id);
		case 8: return &(new_trip-> payment_type);
		case 9: return &(new_trip-> fare_amount);
		case 10: return &(new_trip-> extra);
		case 11: return &(new_trip-> mta_tax);
		case 12: return &(new_trip-> tip_amount);
		case 13: return &(new_trip-> tolls_amount);
		case 14: return &(new_trip-> improvement_surcharge);
		case 15: return &(new_trip-> total_amount);
		case 16: return &(new_trip-> pu_datetime);
		case 17: return &(new_trip-> do_datetime);
		case 18: return &(new_trip-> trip_duration);
	}

	return NULL;
}