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
#include "bst.h"

int main(int argc, char** argv){

	//reads input file and returns bst dictionary
	struct bst* bst = NULL;
	bst = construct_bst(argv);
	//Open file to write output
	FILE *out_file = fopen(argv[OUTFILE_ARG], "w");
	int keylen; 
	char *key; 

	//buffer for each field
	char *field = (char *) malloc(sizeof(char)*MAXFIELDSIZE);
	assert(field);
	size_t bufsize = MAXFIELDSIZE;
	size_t linesize;

	//obtain keys, perform search on bst, write to stdin and output
	while((linesize = getline(&field, &bufsize , stdin))!=END_OF_LINE){
		keylen=strlen(field);
		key = (char *)malloc(sizeof(char)*keylen+NULLBYTE_SPACE);
		assert(key);
		strcpy(key, field);

		//strip newline chars from end of line
		if (keylen > EMPTY_STRING_LEN && key[keylen-LAST_CHAR] == NEWLINE){
			key[keylen-LAST_CHAR] = '\0';
		}

		find_in_bst(key,bst, out_file);
		free(key);
	}

	//free out all temporary pointers and buffers
	fclose(out_file);	
	free_tree(bst);
	free(field); 
	
	return 0;
}


