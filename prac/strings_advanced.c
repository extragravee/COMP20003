#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	/*
	Can assign strings using below without explicitly stating the length,
	compiler can count
	*/
	char my_str[] = "hi!"; //this takes up just 4 bytes of static memory to store the array, string plus nullbyte
	//in the static memory, so the location of the array is fixed at runtime. Since that's the case, my_str variable is actually
	// A CONSTANT

	/*
	alternatively we can use the pointer approach
	*/

	char *my_str2 = "bye!"; //this takes up 5 bytes in memory 
	//string plus nullbyte PLUS 4 bytes for the pointer variable
	//BUT IN THE POINTER NOTATION MY_STR2 IS A VARIABLE
	
	return 0;
}

void my_function_A(char *ptr)
{
char a[] = "ABCDE";
// in this function the content of the array a[] is considered to be data. array is initialised to the values ABCDE
// as a[] is within a function hence a local variable, the string "ABCDE" is stored on the stack
}

void my_function_B(char *ptr)
{
char *cp = "FGHIJ";
//in this function the value of the pointer cp is considered data. Pointer has been initialised to point to the string "FGHIJ"
//as cp is within a function hence local variable, the value of cp is stored on the stach
//BUT THE VALUE OF THE STRING IT POINTS TO "FGHIJ" CAN BE STORED ANYWHERE (NOT ON STACK TOO, USUALLY IN DATA SEGMENT)
}


