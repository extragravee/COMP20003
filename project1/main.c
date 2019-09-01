/*
Provides the skeleton tasks for the project
1. Opens a file
2. Facilitates creation of trip objects
3. Adds trip objects to the BST dictionary (handles duplicates with linked list), then closes file
4. Opens output file, performs search and writes to output file
5. Closes file and frees all memory being used by the tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "trip_logs.h"
#include "bst.h"

#define MAXFIELDSIZE 128
#define MAXBUFFERSIZE 256
#define INFILE_ARG 1
#define OUTFILE_ARG 2
#define NULLBYTE_SPACE 1


int main(int argc, char** argv){
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
	struct bst* bst = NULL;
	while((linesize = getline(&buffer, &bufsize , datafile))!=-1){ 
		new_trip = create_trip_record(buffer, field);
		bst = insert_node(bst, new_trip);
	}

	fclose(datafile); //all input sorted

	FILE *out_file = fopen(argv[OUTFILE_ARG], "w");
	bufsize = MAXFIELDSIZE;
	int keylen;
	char *key;
	while((linesize = getline(&field, &bufsize , stdin))!=-1){
		// printf("%s\n", input);
		keylen=strlen(field);
		key = (char *)malloc(sizeof(char)*keylen+NULLBYTE_SPACE);
		assert(key);
		strcpy(key, field);
		// printf("Typed in: '%s' size: %d", key, (int)strlen(key));
		if (keylen > 0 && key[keylen-1] == '\n') key[keylen-1] = '\0';
		// printf("%s", key);
		find_in_bst(key,bst, out_file);
		free(key);
	}

	//free out all temporary pointers and buffers
	fclose(out_file);	
	free_tree(bst);
	free(buffer); 
	free(field); 
	
	return 0;
}


