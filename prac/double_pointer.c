#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	int **c;

	c = (int **) malloc(sizeof(int) * 20);
	for (int i=0; i<20; i++){
		*(c+i) = (int *) malloc (sizeof(int)*10);
	}

	for (int i=0;i<10;i++){
		for (int j=0; j<10; j++){
			c[i][j] = 5+i+j;
			printf("%4d \n", *(*(c+i)+j));
		}
		
	}



	return 0;
}