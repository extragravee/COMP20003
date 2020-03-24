/*
Created by Sidakpreet Mann - 921322
sidakpreetm@student.unimelb.edu.au

main file for stage 2 of project 1

function declerations and common constants abstracted to header file "bst.h"

1. Constructs the bst dictionary
2. Reads in key, calls traverse_bst function from bst.c, writes to output file
3. Determines if a match was found, if not, writes to output file
4. Resets counters and match found flag variable in bst.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bst.h"
#define ONE_CHAR 1

int main(int argc, char** argv) {
	//reads input file and returns bst dictionary
	struct bst* bst = NULL;
	bst = construct_bst(argv);

	size_t bufsize = MAXFIELDSIZE;
	size_t linesize;

	//Open file to write output
	FILE *out_file = fopen(argv[OUTFILE_ARG], "w");
	int keylen; 
	char *key = (char *)malloc(sizeof(char)*MAXFIELDSIZE+NULLBYTE_SPACE);

	//obtain keys, traverses bst to find matches
	while((linesize = getline(&key, &bufsize , stdin))!=END_OF_LINE) {
		keylen = strlen(key);

		//strip newline chars from end of line
		if (keylen > EMPTY_STRING_LEN && key[keylen-LAST_CHAR] == NEWLINE) {
			key[keylen-LAST_CHAR] = '\0';
		}

		keylen=strlen(key);
		//if key length > 0
		if(keylen>=ONE_CHAR) {
			traverse_bst(key,bst,out_file);
			if(!get_match_found()) {
				fprintf(out_file, "%s --> NOTFOUND\n", key);
			}
			//required stdout
			printf("%s --> %d\n", key, get_search_count());
		}
		reset_static_vars();

	}


	//free out all temporary pointers and buffers
	free(key);	
	free_tree(bst); 
	fclose(out_file);
	return 0;
}

