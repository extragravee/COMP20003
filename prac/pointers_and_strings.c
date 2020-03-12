#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	char strA[80] = "a string to be used";
	char strB[80] = "4985308250480928585432098543908904325";

	char *pA;
	char *pB;

	//file handinling function, outputs a line to the screen
	puts(strA);

	//assign a char pointer to the string we made
	pA = strA;
	puts(pA); //print the same string, strings are arrays of characters in C

	pB = strB; //assign the new pointer to the other uninitialised string
	puts(pB); //prints a blank line

	putchar('\n'); //move down a line on screen
	putchar('\n');
	putchar('\n');


	while(*pA!='\0'){ //while we don't reach the end of the first string
		*pB++ = *pA++; //copy the derefenced character from string A to string B
	//then append the values of the two pointers by 1 (char so 1 byte here)
	}
	*pB = '\0'; //end the string B with nul <<<<<<<<<<<<------------- if thisline is removed then we see that that since stringB was llonger
	//istring A is overwritten on string B, and since we put no nul in the end, the rest of string B still remains.

	puts(strB); //strB points to the start of the second string still, so print that string
	puts(pB); //as now pB has been appended in the loop above, it no longer points
	//to the start of the string.
	return 0;
}