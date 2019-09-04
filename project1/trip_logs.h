/*
Created by Sidakpreet Mann - 921322
sidakpreetm@student.unimelb.edu.au

Header file for trip_log.c includes trip dictionary structure and functions

Includes:
Structure
Function declarations from 'trip_logs.c'

*/

#ifndef TRIP_LOGS_H
#define TRIP_LOGS_H

/*
delcares the structure of the trip, all columns as in the csv
*/
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
returns pointer to a (struct type object) trip based on the row of data provided (buffer)
Uses the once defined field (maxsize 128 char) to temporarily store the cell being copied
*/
struct trip* create_trip_record(char *buffer, char* field);

/*
obtains a pointer, to the pointer that points to the memory being used to store the cell
*/
char** get_struct_member(struct trip* new_trip, int column_number);

/*
prints all members of the struct
*/
void print_trip(struct trip* new_trip, FILE* out_file);

/*
frees all the memory allocated for each member in the struct
*/
void free_members_of_struct(struct trip* trip);

/*
returns name of field based on column number
*/
char* get_field_name(int column_number);


#endif
