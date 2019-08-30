/*
Provides the skeleton tasks for the project
1. Opens a file
2. Facilitates creation of trip objects
3. Adds trip objects to the BST dictionary
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "trip_logs.h"
#include "bst.h"


#define MAXFIELDSIZE 128
#define MAXBUFFERSIZE 256
#define INFILE_ARG 1

int main(int argc, char** argv){

	char* buffer = (char *)malloc(sizeof(char)*MAXBUFFERSIZE);
	assert(buffer); //confirm if enough memory was available for buffer

	puts("==================================OUTPUT==================================");
	// for (int i = 0; i < argc; i++) {
	// 	printf("argv[%d] = \"%s\"\n", i, argv[i]);
	// }

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
		print_trip(new_trip);
		bst = insert_node(bst, new_trip);
	}

	free_tree(bst);//frees all nodes, structs, and struct members, and pointers
	fclose(datafile); //to clear out the file pointer
	free(buffer); //to clear out the temp buffer memory allocated
	free(field); //to clear the temp storage to store fields one by one within a single row
	
	puts("==================================OUTPUT==================================");
	return 0;
}
