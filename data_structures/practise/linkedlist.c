#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char* name;
	struct node* next;
} node_t;

node_t* insert_node(node_t* node, char *name);
void print_free_ll(node_t* head);

int main(int argc, char* argv[]){
	node_t* head = NULL;
	node_t* tail = NULL;

	char names[][10] = {"Sidak\0", "Angelina\0", "Theresa\0", "Kishan\0", "Liam\0"};

	for (int i=0; i<5; i++){
		tail = insert_node(tail, names[i]);
		if(head==NULL){
			head = tail;
		}
	}
	print_free_ll(head);
	return 0;
}


node_t* insert_node(node_t* tail, char *name){
	if(tail==NULL){
		tail = (node_t*) malloc(sizeof(node_t));
		tail->name = (char *)malloc(sizeof(char)*strlen(name)+1);
		strcpy(tail->name, name);
		tail->next = NULL;
	} else {
		tail->next = (node_t *) malloc(sizeof(node_t));
		tail = tail->next;
		tail->name = (char *)malloc(sizeof(char)*strlen(name)+1);
		strcpy(tail->name, name);
		tail->next = NULL;
	}
	return tail;
}

void print_free_ll(node_t* head){
	node_t* temp = NULL;
	while(head){
		printf("%s  -->  ", head->name);
		temp = head;
		head = head->next;
		free(temp->name);
		free(temp);
	}
	printf("%p\n", head);

}