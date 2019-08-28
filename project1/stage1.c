#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int main(int argc, char** argv){

	char* buffer = (char *)malloc(sizeof(char)*256);


	assert(buffer);
	for (int i = 0; i < argc; i++) {
		printf("argv[%d] = \"%s\"\n", i, argv[i]);
	}

	fgets(buffer, 256, stdin);
	puts("==================================OUTPUT==================================");
	printf("string: %s, length: %lu\n", buffer, strlen(buffer));
	int k = strlen(buffer);
	buffer = realloc(buffer, k);
	// printf("string: %s | length: %lu | size: %lu\n", buffer, strlen(buffer), sizeof(buffer));
	free(buffer);
	puts("==================================OUTPUT==================================");
	return 0;
}