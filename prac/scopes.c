#include <stdio.h>
#include <stdlib.h>

void change(int *ptr_x){
	int y = 6;
	printf("ptr_x: %p | &ptr_x: %p | *ptr_x: %4d\n", ptr_x, &ptr_x, *ptr_x);
	*ptr_x = y;
}


int main(int argc, char* argv[]){
	int *x;
	x = (int *)malloc(sizeof(int));
	*x = 5;
	printf("x: %p | &x: %p | *x: =%4d\n", x, &x, *x);
	change(x);
	printf("x: %p | &x: %p | *x: =%4d\n", x, &x, *x);
	free(x);
}





// int main(int argc, char* argv[]){
// 	int x = 4;
// 	int *ptr_x = &x;
// 	printf("x: %4d | &x: %4p | ptr_x: %p | &ptr_x: %p \n", x, &x, ptr_x, &ptr_x);
// 	change(ptr_x);
// 	// printf("x: %4d | &x: %4p | ptr_x: %p | &ptr_x: %p \n", x, &x, ptr_x, &ptr_x);
// }