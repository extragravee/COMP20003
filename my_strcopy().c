#include <stdio.h>
#include <stdlib.h>


char *my_strcpy(char *destination, const char* source);

int main(int argc, char* argv[]){
	char *mystring = "bleh";
	// char *copy_it_here;
	char *copy_it_here = malloc(sizeof(char)*10);
	my_strcpy(copy_it_here, mystring);
	puts(copy_it_here);
	free(copy_it_here);
	return 0;
}


/* personal implementation of strcpy() */
char *my_strcpy(char *destination, const char* source){ //const here to ensure to the user
	//that the string in source won't be modified
	char *p = destination; //we make this so we can step through the memory using *p


	// *source = 'X'; // trying this to see if adding const above will help.
	while(*source !='\0'){
		*p++ = *source++;
	}
	*p='\0';
	return destination; //still need this as destination still points to the start, but now *p points
	//to the end of the string!

}