#include <stdio.h> 
#include <stdlib.h> 

struct Node { 
	int data; 
	struct Node* link; 
}; 
struct Node* top = NULL; 

void push(int data){ 
	struct Node* temp; 
	temp = (struct Node*)malloc(sizeof(struct Node)); 
	if (!temp) { 
		exit(1); 
	} 
	temp->data = data; 
	temp->link = top; 
	top = temp; 
} 

void pop(){ 
	struct Node* temp; 
	if (top == NULL) { 
		printf("\nStack Underflow"); 
		exit(1); 
	} 
	else { 
		temp = top; 
		top = top->link; 
		temp->link = NULL; 
		free(temp); 
	} 
} 
