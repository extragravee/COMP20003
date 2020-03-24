#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tag{
	char lname[20];
	char fname[20];
	float rate;
	int age;
};



int main(int argc, char *argv[]){

	struct tag my_struct;
	strcpy(my_struct.lname, "Mann");
	strcpy(my_struct.fname, "Sidak");

	// puts(my_struct.lname);
	// puts(my_struct.fname);

	printf("%s ", my_struct.fname);
	printf("%s\n", my_struct.lname);


	return 0;
}