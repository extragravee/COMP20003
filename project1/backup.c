/*
Binary Search Tree implementation:
Structures
Functions
Function declerations abstracted to header file "bst.h"

Code here has been adapted from Worksheet3 and the authors of Worksheet 3 provided to us
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXFIELDSIZE 128
#define MAXBUFFERSIZE 256
#define INFILE_ARG 1
#define OUTFILE_ARG 2

#define DELIM_REGEX "\r,"
#define SECOND_FIELD 2
#define NULLBYTE_SPACE 1
// #include "bst.h"


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

struct bst{
	struct bst* left;
	struct bst* right;
	struct trip* trip;
	char* key;
};


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

/*
Takes node pointer and frees all of its children and itself
by default (if pointer is NULL), does nothing
frees children recursively
*/

/* inserts a new node into the bst dictionary */
struct bst* insert_node(struct bst* parent, struct trip* trip){
	int result;

	//pointer to the insert location
	struct bst** insert_here = &parent;

	//till an empty node isn't reached, keep looking
	while(*insert_here != NULL){
		//if new node's key >, go right, if < go left, if == then add node in linkedlist
		// result = strcmp((new_trip->pu_datetime), ((*insert_here)->key));
		result = strcmp((trip->pu_datetime), ((*insert_here)->key));
		if(result < 0){
			insert_here = &((*insert_here)->left);
		} else if(result > 0){
			insert_here = &((*insert_here)->right);
		} else {
			/*IMPLEMENT LINKED LIST HERE*/
			printf("Duplicate! Handle!");
			return parent;
		}
	}
	(*insert_here)->left = NULL;
	(*insert_here)->right = NULL;
	(*insert_here)->key = trip->pu_datetime;
	(*insert_here)->trip = trip;

	printf("New node inserted! Key: %s, Trip: %s", trip->pu_datetime, trip->trip_distance);
	return parent;
}

/* recursively free the nodes of the tree */
void free_tree(struct bst* parent){
	if(!parent){
		return;
	}
	free_tree(parent->left);
	free_tree(parent->right);
	free_members_of_struct(parent->trip); //first free all members of the struct
	free(parent); //then free the struct
}

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

int main(int argc, char** argv){

	char* buffer = (char *)malloc(sizeof(char)*MAXBUFFERSIZE);
	assert(buffer); //confirm if enough memory was available for buffer

	puts("==================================OUTPUT==================================");

	//reading in the infile
	FILE *datafile;
	if((datafile = fopen(argv[INFILE_ARG], "r"))==NULL){
		printf("File does not exist in the current directory!\n");
		exit(EXIT_FAILURE);
	}
	//now the file is open, and we have a pointer to the start of the file
	size_t bufsize = MAXBUFFERSIZE;
	size_t linesize;

	//temp storage to store fields one by one within a single row
	char *field = (char *) malloc(sizeof(char)*MAXFIELDSIZE);
	assert(field);
	
	struct trip* new_trip;
	struct bst* bst = NULL;

	//Add all trip records to structs
	//at the moment frees all members of each struct, and the struct itself too.
	while((linesize = getline(&buffer, &bufsize , datafile))!=-1){ //obtains one row from csv
		new_trip = create_trip_record(buffer, field);
		// bst = insert_node(bst, new_trip);
		print_trip(new_trip);
		free_members_of_struct(new_trip); //function clears all mallocs inside the struct
		
		free(new_trip); // need for freeing all structs
		free_tree(bst);
	}

	fclose(datafile); //to clear out the file pointer
	free(buffer); //to clear out the temp buffer memory allocated
	free(field); //to clear the temp storage to store fields one by one within a single row
	
	puts("==================================OUTPUT==================================");
	return 0;
}
