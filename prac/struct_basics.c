#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tag{
	char lname[20];
	char fname[20];
	int age;
	float rate;
};

void show_name(struct tag *p);

int main(int argc, char* argv[]){
	struct tag my_struct;
	strcpy(my_struct.lname, "Mann");
	strcpy(my_struct.fname, "Sidakpreet");
	my_struct.rate = 47.73;
	my_struct.age = 21;

	printf("%s %s\n", my_struct.fname, my_struct.lname);
	// puts(my_struct.fname);
	struct tag *str_ptr;
	str_ptr = &my_struct;
	show_name(str_ptr);
	return 0;
}


void show_name(struct tag *p){
	printf("%s %s is %d years old and earns at a rate of %02.2f. \n", p->fname, p->lname, p->age, p->rate);
}