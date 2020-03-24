#include <stdio.h>
#include <stdlib.h>

void printArray(int* array, int size);
void modify_array(int* array, int increment, int size);


int main (int argc, char** argv){

	int* myArray = (int*) malloc (sizeof(int)*10);

	for (int i=0; i<10; i++){
		myArray[i] = i;
	}

	printArray(myArray, 10);
	puts("=========");

	modify_array(myArray, -6, 10);
	printArray(myArray, 10);
	
	puts("=========");

	return 0;
}

void printArray(int* array, int size){
	for(int i = 0; i<size; i++){
		printf("%d\n", array[i]);
	}
}

void modify_array(int* array, int increment, int size){
	for(int i=0; i<size; i++){
		array[i]+=increment;
	}
}