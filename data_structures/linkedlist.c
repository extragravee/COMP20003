#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ll_node{
	int data;
	struct ll_node* next;
} node;

int main(int argc, char* argv[]){
	int intarray[] = {5,6,543,6,2,45,24,54,12,4,124,1};

	//initial linked list root building
	node* head = NULL;
	node* tail = NULL;
	
	//building root for linked list



	for (int i=0; i<sizeof(intarray)/sizeof(int); i++){
		if(head == NULL){
			head = (node *) malloc(sizeof(node));
			tail = head;
			head->data = intarray[i];
			head->next = NULL;
		}
		else{
			tail->next = (node *) malloc(sizeof(node));
			tail = tail->next;
			tail->data = intarray[i];
			tail->next = NULL;
		}

		
	}

	node *temp = head;
	while(head){
		temp = head;
		printf("%p\n", head);
		printf("|%6d | %p|-->  \n", head->data, head->next);
		puts("----------------------------\n");
		head = head->next;
		free(temp);
	}

	puts("\n");


	return 0;
}