#include <stdio.h>
#include <stdlib.h>

void change(int *ptr_x, int y){
	*ptr_x = y;
}

void change_the_pointer(int **ptr_to_ptr, int z){
	**ptr_to_ptr
}

int main(int argc, char* argv[]){
	int x=5;
	int y=6;
	int z=7;
	printf("X: %d, y: %d", x, y);
	int* ptr_x = &x;

	change(ptr_x, y);
	puts("\n");
	printf("X: %d, y: %d\n", x, y);

	int **ptr_to_ptr = &ptr_x;
	printf("%p\n", **ptr_to_ptr);
	// change_the_pointer(ptr_to_ptr, z);
	// puts("\n");
	// printf("X: %d, y: %d", x, y);
	return 0;
}