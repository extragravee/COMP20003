/*
Defines functions for the trip log records provided in
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
#define FIRST_COLUMN 1
#define MAX_COLS 18
#define NEWLINE_CHAR '\n'
#define OUTPUT_BUFFER 300

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
	assert(new_trip);

	//Store first column, must be outside loop due to strtok functionality
	field = strtok(buffer, DELIM_REGEX);
	cell_length = (int)strlen(field); 
	(new_trip->vendor_id) = (char *)malloc((sizeof(char)*cell_length)+NULLBYTE_SPACE);
	assert(new_trip->vendor_id);
	strcpy(new_trip->vendor_id, field);

	//store all the other columns in the relevant fields within the struct
	char **temp;
	while ((field = strtok(NULL, DELIM_REGEX))!=NULL){
		cell_length = (int)strlen(field);
		temp = get_struct_member(new_trip, counter);
		*temp = (char *)malloc(sizeof(char)*cell_length+NULLBYTE_SPACE);
		assert(*temp);
		if (cell_length > 0 && field[cell_length-1] == NEWLINE_CHAR) field[cell_length-1] = '\0';
		strcpy(*temp, field);
		counter++;
	}
	
	return new_trip;
}

//actual function <<<<<<<<<<<<<<<<
// /*
// Prints all fields of a single trip
// */
// void print_trip(struct trip* new_trip, FILE *out_file){
// 	int counter = FIRST_COLUMN;
// 	fprintf(out_file, "%s -->", new_trip->pu_datetime);
// 	while(counter<=MAX_COLS){
// 		char **temp;
// 		temp = get_struct_member(new_trip, counter);
		//don't print out the key, still recorded for stage 2, completion, and modularity for future uses
// 		if(counter!=16){
// 			printf("%s : %s\n", get_field_name(counter), *temp);
// 			fprintf(out_file, " %s: %s ||", get_field_name(counter), *temp);
// 		}
// 		counter++;
// 	}
// 	fprintf(out_file, "\n");
// }

void print_trip(struct trip* new_trip, FILE *out_file){
	int counter = FIRST_COLUMN;
	// fprintf(out_file, "%s -->", new_trip->pu_datetime);
	while(counter<=MAX_COLS){
		char **temp;
		temp = get_struct_member(new_trip, counter);
		if(new_trip){
			//testing
			printf("%s : %s\n", get_field_name(counter), *temp);
			// fprintf(out_file, " %s: %s ||", get_field_name(counter), *temp);
		}
		counter++;
	}
	// fprintf(out_file, "\n");
}

/*
frees all members of a given trip record
*/
void free_members_of_struct(struct trip* trip){
	int counter = FIRST_COLUMN;
	while(counter<=MAX_COLS){
		char **temp;
		temp = get_struct_member(trip, counter);
		counter++;
		free(*temp);
	}
}

/*
retrieves the memory address of the relevant field by row number
*/
char** get_struct_member(struct trip* new_trip, int column_number){
	switch(column_number){
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

/*
these are inconsistent in terms of camelCase and underscores to accomodate
the assignment spec and the testfile online
*/
char* get_field_name(int column_number){
	switch(column_number){
		case 1: return "VendorID";
		case 2: return "passenger_count";
		case 3: return "trip_distance";
		case 4: return "RatecodeID";
		case 5: return "store_and_fwd_flag";
		case 6: return "PULocationID";
		case 7: return "DOLocationID";
		case 8: return "payment_type";
		case 9: return "fare_amount";
		case 10: return "extra";
		case 11: return "mta_tax";
		case 12: return "tip_amount";
		case 13: return "tolls_amount";
		case 14: return "improvement_surcharge";
		case 15: return "total_amount";
		case 16: return "pu_datetime";
		case 17: return "DOdatetime";
		case 18: return "trip_duration";
	}

	return NULL;
}