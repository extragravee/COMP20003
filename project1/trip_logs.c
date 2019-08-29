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

#define DELIM ','

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

	field = strtok(buffer, "\r,");
	// strcpy(field, strtok(buffer, delim)); //copy first part of buffer into 'field' column
	cell_length = (int)strlen(field); 
	printf("\n%s, %d <<<<<<<<<<<<<<<\n", field, cell_length);

	// while((field)!=NULL){
	// 	strcpy(field, strtok(NULL, delim));
	// 	cell_length = (int)strlen(field); 
	// 	printf("\n%s, %d <<<<<<<<<<<<<<<", field, cell_length);
	// }
	
}