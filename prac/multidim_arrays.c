#include <stdio.h>
#define ROWS 5
#define COLS 10

int multi[ROWS][COLS];

int main(void)
{
	int row, col;
	for (row = 0; row < ROWS; row++){
		for (col = 0; col < COLS; col++){
			multi[row][col] = row*col;
			printf("%3d", row*col);
		}
		printf("\n");
	}
	puts("\n");

	printf("%p\n", &multi);	//WHY ARE THESE THE SAME
	printf("%p\n", *multi); //WHYHWYHWY	
	puts("\n");

	printf("multi [2][4] = %d\n", multi[2][4]);
	printf("multi [2][5] = %d\n", multi[2][5]);

	printf("&multi [2][4] = %p\n", &multi[2][4]); //start of the third row
	printf("multi [2][4] (pointer method) = %d\n", *(*(multi+2)+4));
	printf("&multi [2][5] (pointer method) = %p\n", (*(multi+2)+6));
	printf("multi [2][5] (pointer method) = %d\n", *(*(multi+2)+5));

	return 0;
}