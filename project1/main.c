#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main(int argc, char** argv){

	char* buffer = (char *)malloc(sizeof(char)*256);
	assert(buffer); //confirm if enough momery was available for buffer

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

	while((linesize = getline(&buffer, &bufsize , datafile))!=-1){
		printf("%lu: %s", linesize, buffer);
	}
	
	fclose(datafile); //to clear out the file pointer
	free(buffer); //to clear out the temp buffer memory allocated
	puts("==================================OUTPUT==================================");
	return 0;
}