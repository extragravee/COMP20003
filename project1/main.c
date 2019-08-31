/*
Provides the skeleton tasks for the project
1. Opens a file
2. Facilitates creation of trip objects
3. Adds trip objects to the BST dictionary (handles duplicates with linked list)
4. Performs search and writes to output file
5. Closes file and frees all memory being used by the tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "trip_logs.h"
#include "bst.h"
#include "duplicate_ll.h"

#define MAXFIELDSIZE 128
#define MAXBUFFERSIZE 256
#define INFILE_ARG 1
#define OUTFILE_ARG 2
#define NULLBYTE_SPACE 1

int main(int argc, char** argv){
	char* buffer = (char *)malloc(sizeof(char)*MAXBUFFERSIZE);
	assert(buffer); //confirm if enough memory was available for buffer

	for (int i = 0; i < argc; i++) {
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
	}

	char *input;
	input = (char*)malloc(sizeof(char)*MAXFIELDSIZE);
	assert(input);
	size_t buffsize = MAXFIELDSIZE;
	size_t ls;
	// int num = ftell(stdin);
	// printf("%d\n", num);
	// if(stdin){

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

	//Add all trip records from csv to trip_record structs
	while((linesize = getline(&buffer, &bufsize , datafile))!=-1){ 
		new_trip = create_trip_record(buffer, field);
		// print_trip(new_trip);
		bst = insert_node(bst, new_trip);
	}

	int keylen;
	char *key;
	while((ls = getline(&input, &buffsize , stdin))!=-1){
		keylen=strlen(input);
		key = (char *)malloc(sizeof(char)*keylen+NULLBYTE_SPACE);
		assert(key);
		strcpy(key, input);
		if (keylen > 0 && key[keylen-1] == '\n') key[keylen-1] = '\0';
		find_in_bst(key,bst);
		free(key);
	}

	free(input);
	free_tree(bst);//frees all nodes, structs, and struct members, and pointers
	fclose(datafile); //to clear out the file pointer
	free(buffer); //to clear out the temp buffer memory allocated
	free(field); //to clear the temp storage for each field
	
	return 0;
}


