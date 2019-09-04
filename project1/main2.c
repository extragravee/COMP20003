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
			// printf("%s, %d\n", key, keylen);
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

