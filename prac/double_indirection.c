#include <stdlib.h>
#include <stdio.h>

void add_five_to_number(int* number);

int main(int argc, char** argv){

	int* number = (int*) malloc (sizeof(int));
	*number = 8;

	printf("Value of number is: %d\n", *number);

	add_five_to_number(number);

	printf("Value of number is: %d\n", *number);

	return 0;
}

void add_five_to_number(int* number){
	(*number)+= 5;
	puts("5 has been added to the number");
}