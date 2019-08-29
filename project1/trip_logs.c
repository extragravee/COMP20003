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

char** get_struct_member(struct trip* new_trip, int i);
void print_the_fuckers(struct trip* new_trip);

struct trip{
	char* vendor_id; //Code to indicate the vendor which produced the record
	char* passenger_count; //Number of passengers
	char* trip_distance; //Length of the trip in miles
	char* rate_code_ID; //Code to represent the fare rate for the trip
	char* store_and_fwd_flag; //Indicates whether trip records were stored locally
	char* pu_location_id; //TLC Taxi Zone where passengers were picked up
	char* do_location_id; //TLC Taxi Zone where passengers were dropped off
	char* payment_type; //Code to indicate payment type (e.g., cash)
	char* fare_amount; //Fare for the trip in USD
	char* extra; //Extra charges in USD
	char* mta_tax; //MTA tax in USD
	char* tip_amount; //Tip in USD
	char* tolls_amount; //Tolls in USD
	char* improvement_surcharge; //Improvement surcharge in USD
	char* total_amount; //Total cost of the trip in USD
	char* pu_datetime; //Date/time passengers were picked up
	char* do_datetime; //Date/time passengers were dropped off
	char* trip_duration; //Duration of the trip in minutes
};

/* 
1. Accepts the buffer (contains one full trip row from the input data)
2. Transforms it into the a trip struct type object
3. Passes the pointer to this new trip object back to main.c
*/
struct trip* create_trip_record(char *buffer, char* field){ 
	int cell_length;
	// int counter = 2;

	//create new trip struct object
	struct trip* new_trip = (struct trip*) malloc(sizeof(struct trip));
	//Store first column 
	field = strtok(buffer, DELIM_REGEX);
	cell_length = (int)strlen(field); 
	printf("\nField: %s, Length: %d\n", field, cell_length);

	//==================================
	(new_trip->vendor_id) = (char *)malloc((sizeof(char)*cell_length)+1);
	strcpy(new_trip->vendor_id, field);

	char **temp;
	temp = get_struct_member(new_trip, 2);
	printf("\n temp: %p, struct->passenger_count: %p", temp, get_struct_member(new_trip, 2));
	*temp = (char *)malloc(sizeof(char)*5);
	strcpy(*temp, "heyo");
	printf("\n *temp %s, struct->passenger_count %s", *temp, new_trip->passenger_count);
	free(*temp);
	// char *temp;
	// store the rest of the columns in the new struct
	// while((field = strtok(NULL, DELIM_REGEX))!=NULL){
	// 	// cell_length = (int)strlen(field); 
	// 	// printf("\nField: %s, Length: %d\n", field, cell_length);
		
	// 	// printf("temp: %p, struct %p\n", temp, new_trip->passenger_count);
	// 	// temp = (char *) malloc((sizeof(char)*cell_length)+1);
	// 	// printf("temp: %p, struct %p\n", temp, new_trip->passenger_count);
	// 	// strcpy(*temp, field);
	// 	// strcpy(get_struct_member(new_trip, counter), temp);
	// 	// printf("%s \n", get_struct_member(new_trip, counter));
	// 	// printf("%s\n", new_trip->passenger_count);
	// 	// printf("Counter = %d\n", counter);
	// 	counter++;
	// }

	// print_the_fuckers(new_trip);

	free(new_trip->vendor_id); //for memtesting
	puts("\n");
	return new_trip;
}

void print_the_fuckers(struct trip* new_trip){
	int counter = 1;
	puts("Printing=================\n");
	while(counter<=18){
		printf("%s\n", (char *)get_struct_member(new_trip, counter));
		counter++;
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