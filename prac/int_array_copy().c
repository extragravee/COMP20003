#include <stdio.h>
#include <stdlib.h>


int *my_intcpy(int *destination, const int* source, int nbr);

int main(int argc, char* argv[]){
	int myNumbers[] = {5,4532,234,4,52121,43,4,2,32112,3,2,3,2,1};
	// char *copy_it_here;
	int *copy_it_here = malloc(sizeof(int)*20);
	my_intcpy(copy_it_here, myNumbers, 14);

	//print out the copied array
	for(int i=0; i<14; i++){
		printf("%d\n", *(copy_it_here+i));
	}

	free(copy_it_here);
	return 0;
}


/* copies an array of integers */
int *my_intcpy(int *destination, const int* source, int nbr){ //const here to ensure to the user
	//that the string in source won't be modified
	int *p = destination; //we make this so we can step through the memory using *p
	int ctr = 0;

	while(ctr<nbr){
		*p++ = *source++;
		ctr++;
	}

	return destination; //still need this as destination still points to the start, but now *p points
	//to the end of the string!

}