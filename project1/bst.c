/*
Created by Sidakpreet Mann - 921322
sidakpreetm@student.unimelb.edu.au
Binary Search Tree implementation file
Includes functions relating to construction, search and traversal of the bst dictionary
Function declerations and common constants abstracted to header file "bst.h"

Code for the function 'insert_node' has been adapted from Worksheet3 and the authors of Worksheet 3 provided on JupyterHub
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
#define INITIAL_COUNT 0
#define TRUE_ 1
#define FALSE_ 0

struct bst* construct_bst(char **argv) {

	struct bst* bst = NULL;
	//buffer for each line
	char* buffer = (char *)malloc(sizeof(char)*MAXBUFFERSIZE);
	assert(buffer);	

	//reading in the infile
	FILE *datafile;
	if((datafile = fopen(argv[INFILE_ARG], "r"))==NULL) {
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
	
	while((linesize = getline(&buffer, &bufsize , datafile))!=-1) { 
		new_trip = create_trip_record(buffer, field);
		bst = insert_node(bst, new_trip);
	}

	fclose(datafile); //all input sorted
	free(buffer);
	free(field);
	return bst;
}

/* iteratively inserts a new node into the bst dictionary */
struct bst* insert_node(struct bst* parent, struct trip* trip) {
	int result;

	//pointer to the insert location
	struct bst** insert_here = &parent;
	//till an empty node isn't reached, keep looking
	while(*insert_here != NULL) {
		result = strcmp((trip->pu_datetime), ((*insert_here)->key));

		if(result < MATCH) {
			insert_here = &((*insert_here)->left);
		} 
		else if(result > MATCH) {
			insert_here = &((*insert_here)->right);
		} 
		else if(result==MATCH) {	
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
void free_tree(struct bst* parent) {
	if(!parent) {
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
void find_in_bst(char* find_key, struct bst* bst, FILE *out_file) {

	int result;
	struct bst** temp = &bst;
	int counter =0; //only records the number of string comparisons
	while(*temp) {
		counter++;
		result = strcmp(find_key, (*temp)->key);
		if(result<MATCH) {
			temp = &((*temp)->left);
		} else if(result>MATCH) {
			temp = &((*temp)->right);
		} else if(result==MATCH) {
			print_trip((*temp)->trip, out_file);
			printf("%s --> %d\n", find_key, counter);
			if((*temp)->duplicates) {
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

/*
Traverses the BST dictionary using PULocationID as a search key, writes 
the matching PUDatetimes to the output file and comprisons to stdout
static variables used due to recursive calls to function
*/
static int count_searches = INITIAL_COUNT;
static int match_found = FALSE_; 
void traverse_bst(char* key, struct bst* bst, FILE* out_file) {
	//recursion base case
	if(!bst) {
		return;
	}

	traverse_bst(key, bst->left, out_file);
	count_searches++;

	//find match within the bst node
	if(strcmp((bst->trip)->pu_location_id,key)==MATCH) {
		fprintf(out_file, "%s --> %s\n", key, (bst->trip)->pu_datetime);
		match_found = 1;
	}

	//find match within duplicates linked lists
	struct duplicate_ll* duplicates = bst->duplicates;
	while(duplicates) {
		count_searches++;
		if(strcmp((duplicates->duplicate_trip)->pu_location_id,key)==MATCH) {
			fprintf(out_file,"%s --> %s\n", key, (duplicates->duplicate_trip)->pu_datetime);
			match_found = 1;
		}
		duplicates = duplicates->next;
	}
	traverse_bst(key, bst->right, out_file);
}


int get_match_found() {
	return match_found;
}

int get_search_count() {
	return count_searches;
}

void reset_static_vars() {
	count_searches = INITIAL_COUNT;
	match_found = 0;
}
