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
#include "trip_logs.h"
#include "bst.h"
#include "duplicate_ll.h"

#define MATCH 0
#define INFILE_ARG 1

struct bst* construct_bst(int argc, char **argv){

	struct bst* bst = NULL;
	//buffer for each line
	char* buffer = (char *)malloc(sizeof(char)*MAXBUFFERSIZE);
	assert(buffer);	

	//reading in the infile
	FILE *datafile;
	if((datafile = fopen(argv[INFILE_ARG], "r"))==NULL){
		printf("File does not exist in the current directory!\n");
		exit(EXIT_FAILURE);
	}
	//now the file is open, and we have a pointer to the start of the file
	size_t bufsize = MAXBUFFERSIZE;
	size_t linesize;

	//buffer for each field
	char *field = (char *) malloc(sizeof(char)*MAXFIELDSIZE);
	assert(field);
	
	//Add all trip records from csv to trip_record structs, create bst with those structs
	struct trip* new_trip;
	
	while((linesize = getline(&buffer, &bufsize , datafile))!=-1){ 
		new_trip = create_trip_record(buffer, field);
		bst = insert_node(bst, new_trip);
	}

	fclose(datafile); //all input sorted
	free(buffer);
	free(field);
	return bst;
}

/* iteratively inserts a new node into the bst dictionary */
struct bst* insert_node(struct bst* parent, struct trip* trip){
	int result;

	//pointer to the insert location
	struct bst** insert_here = &parent;
	//till an empty node isn't reached, keep looking
	while(*insert_here != NULL){
		result = strcmp((trip->pu_datetime), ((*insert_here)->key));
	
		if(result < MATCH){
			insert_here = &((*insert_here)->left);
		} 
		else if(result > MATCH){
			insert_here = &((*insert_here)->right);
		} 
		else if(result==MATCH){	
			(*insert_here)->duplicates = insert_duplicate((*insert_here)->duplicates, trip);
			return parent;
		}
	}

	//once location of new node to be inserted obtained, create that node
	(*insert_here) = (struct bst*)malloc(sizeof(struct bst));
	assert(*insert_here);
	(*insert_here)->left = NULL;
	(*insert_here)->right = NULL;
	(*insert_here)->key = trip->pu_datetime;
	(*insert_here)->trip = trip;
	(*insert_here)->duplicates = NULL;

	return parent;
}

/* 
recursively free the nodes of the tree 
*/
void free_tree(struct bst* parent){
	if(!parent){
		return;
	}
	free_tree(parent->left);
	free_tree(parent->right);
	free_members_of_struct(parent->trip); //first free all members of the struct
	free(parent->trip); //free pointer
	free_duplicates(parent->duplicates);
	free(parent); //then free the struct
}

/*
Find trip in dictionary, write results to output file and comparisons to stdout
*/
void find_in_bst(char* find_key, struct bst* bst, FILE *out_file){

	int result;
	struct bst** temp = &bst;
	int counter =0; //only records the number of string comparisons
	while(*temp){
		counter++;
		result = strcmp(find_key, (*temp)->key);
		if(result<MATCH){
			temp = &((*temp)->left);
		} else if(result>MATCH){
			temp = &((*temp)->right);
		} else if(result==MATCH){
			print_trip((*temp)->trip, out_file);
			printf("%s --> %d\n", find_key, counter);
			if((*temp)->duplicates){
				print_duplicates((*temp)->duplicates, out_file);
			}
			return;
		}

	}
	/*since the duplicates being printed require no more string searches
	only the count of string searches is stdout, i.e., where the first match
	was found*/
	printf("%s --> %d\n",find_key, counter);
	fprintf(out_file, "%s --> NOTFOUND\n", find_key);
}




