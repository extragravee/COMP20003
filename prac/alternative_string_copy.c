#include <stdio.h>
#include <stdlib.h>


char *my_strcpy(char *destination, const char* source);

int main(int argc, char* argv[]){
	char *mystring = "leapords are dope";
	char *copy_it_here = malloc(sizeof(char)*10);
	my_strcpy(copy_it_here, mystring);
	puts(copy_it_here);
	free(copy_it_here);

	return 0;
}


/* personal implementation of strcpy() */
char *my_strcpy(char *destination, const char* source){ //const here to ensure to the user
	//that the string in source won't be modified

	int i=0;
	// *source = 'X'; // trying this to see if adding const above will help.
	while(source[i] !='\0'){
		destination[i] = source[i]; //using this array notation eleminated the need for the pointer in my_str_copy() file
		i++;
	}
	return destination; //still need this as destination still points to the start, but now *p points
	//to the end of the string!

}