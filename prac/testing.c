#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]){

//===========================================
	int n=5;
	int *ptr; //delcares variable of the type int pointer
	ptr = &n; //stores memory address within the pointer

	printf("%p\n", &n);
	printf("%p\n", ptr);
	printf("%d\n", *ptr); //dereferencing the pointer to get the value at that memory address (value of n)

//===========================================

	char name[5] = "sidak";
	printf("%s\n", name); //name by itself is a memory address to the start of the string
	printf("%c\n", name[0]); //dereferncing like that actually gets the value, this is the equivalent of *(name + 0) where name is the pointer/memory reference

	char *ptr2 = name; //this makes a new pointer equals to the variable name, which is already a memory address so don't need the "&"
	printf("%s\n", ptr2); //therefore this statement works as a char * is being supplied to %s

	char *namez = "ang"; //allocates a char pointer and stores the string in it
	printf("%s\n", namez);

	char names[2][6];
	for (int i=0; i<2; i++){
		strcpy(names[i], "sidak");
	}

	for (int i=0;i<2;i++){
		printf("%s", names[i]);
	}
//===========================================


	return 0;

}
