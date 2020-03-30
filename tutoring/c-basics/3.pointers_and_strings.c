#include <stdio.h>
#include <stdlib.h>

void copy_ints(int* dest, const int* array, int n);

int main(int argc, char **argv){
	/*
	1. Defining strings
	=============================
	- Strings are not a primitive type, they are array of chars
	- strings must ALWAYS end in nullbyte because they are an array of 
	chars and so that the compiler finds out when to stop reading
	memory
	- nullbyte is the binary 0 character written as '\0'
	- not the same as (NULL which is a macro defined in our compiler
	to assign a value not pointing anywhere)
	*/

	//can define strings as either
	char my_string[40] = {'J', 'O', 'o', 'l', 's', '\0',};
	//or with double quotes, which automatically addes nul,
	//also not defining the size with double quotes gives automatic size
	char my_string2[] = "JOols";

	//why are the sizes what they are??
	printf("%ld, %ld\n",sizeof(my_string), sizeof(my_string2) );

//REFER TO 3.DEMO.C

	/* 2. Copying things
	===========================
	normally copying an array of positive ints, marks the end with
	a negative int

	also it's normal to pass the number of elements too, like

	int copy_ints(int* dest_array, const int* src_array, int nbr );
	where nbr is the number of items that need to be copied over.


	*/

	int int_array[10] = {1,2,3,4,5,6,7,8,9,10};
	int* dest = (int *)malloc(sizeof(int) * sizeof(int_array)/sizeof(int_array[0]));


	//this num elements trick only works cause int_array is defined locally
	copy_ints(dest, int_array, sizeof(int_array)/sizeof(int_array[0]));
	
	free(dest);

	return 0;
}


//the benefit with c is the whole array is not copied on stack and
//passed to the function like in some languages, but just the mem address
//c is very very efficient!
void copy_ints(int* dest, const int* src, int n){
	for (int i=0; i<n; i++){
		*(dest+i) = src[i];
	}

	puts("The copied elements at destination are:");

	for (int i=0; i<n; i++){
		printf("%d\n", *(dest+i));
		// or we can do printf("%d", dest[i]);
	}

}