/*
Provides the skeleton tasks for the project
1. Opens a file
2. Facilitates creation of trip objects
3. Adds trip objects to the BST dictionary
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "trip_logs.h"

#define MAXFIELDSIZE 128

int main(int argc, char** argv){

	char* buffer = (char *)malloc(sizeof(char)*256);
	assert(buffer); //confirm if enough memory was available for buffer

	puts("==================================OUTPUT==================================");
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
	}

	//reading in the infile
	FILE *datafile;
	if((datafile = fopen(argv[1], "r"))==NULL){
		printf("File does not exist in the current directory!\n");
		exit(EXIT_FAILURE);
	}
	//now the file is open, and we have a pointer to the start of the file
	size_t bufsize = 256;
	size_t linesize;

	//to clear the temp storage to store fields one by one within a single row
	char *field = (char *) malloc(sizeof(char)*MAXFIELDSIZE);
	assert(field);
	

	//Loop through csv
	while((linesize = getline(&buffer, &bufsize , datafile))!=-1){ //obtains one row from csv
		printf("%lu: %s", linesize, buffer);
		struct trip* trip = create_trip_record(buffer);
	}
	
	fclose(datafile); //to clear out the file pointer
	free(buffer); //to clear out the temp buffer memory allocated
	free(field); //to clear the temp storage to store fields one by one within a single row
	
	puts("==================================OUTPUT==================================");
	return 0;
}
