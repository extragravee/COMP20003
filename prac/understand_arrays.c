#include <stdio.h>

int main(int argc, char* argv[]){

	int myArray[] = {1,4,6,7,-5,100};
	int* ptr;

	ptr = myArray;
	printf("%p, %p\n", ptr, myArray);

	for (int i=0; i<6; i++){
		printf("\n myArray[%d] = %d" ,i, myArray[i]);
		printf("\n ptr + %d = %d", i, *ptr++);
	}

	printf("\n");

	return 0;
}