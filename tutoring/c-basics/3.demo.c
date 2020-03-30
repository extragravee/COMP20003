#include <stdio.h>

//these variables here are GLOBALLY DEFINEd, MEANS THAT THEY ARE
//AUTOMATICALLY SET TO THE NULL TYPE FIRST. HERE CHAR, SO '\0'
//after that, in string A we get the rest of the chars

//never define globals anyway unles absolutely necesarry (in projects
//you will always lose marks)


char strA[80] = "A string to be used for demonstration purposes";
char strB[80];
int main(void){
	char *pA;
	/* a pointer to type character */
	char *pB;
	/* another pointer to type character */
	puts(strA); //this is the same as printf("%s", string_var);
	/* show string A */
	pA = strA;
	/* point pA at string A */
	puts(pA);
	/* show what pA is pointing to */
	pB = strB;
	/* point pB at string B */
	putchar('\n');


	/* move down one line on the screen */

	//copy string a to string B using pointer arithmetic
	while(*pA != '\0')
	/* line A (see text) */
	{
		*pB++ = *pA++;
		/* line B (see text) */
	}

	//gotta close of string B too
	*pB = '\0';

	/* line C (see text) */
	puts(strB);
	/* show strB on screen */
	return 0;
}

//the above is how C's strcpy() function operates. We can 
//write our own prototype like dis


//const means the contents of source can NOT be modified in this function
//it's treated as a CONSTANT or stored in the data element, immutable!
char *my_strcpy(char *destination, const char *source)
	{
	char *p = destination;
	while (*source != '\0')
	{
		*p++ = *source++; //*p, then p++, whereas if we did 
		//(*p)++, this gives *p, then appends 1 to *p, which is
		//not the pointer mem value, but the value held at p!!!
	}
	*p = '\0';
	return destination;
}

/* QUIZ TIME
=========================

if we had (*p)++ above, and the value at *p before the increment
was 'T', what would the new value be?
*/

// go back to 3.pointers_and_strings.c