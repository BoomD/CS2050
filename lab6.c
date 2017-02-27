#include <stdio.h>
#include <stdlib.h>

typedef struct n_ {
	int num;
	struct n_* next;
}Node;

// -- prototypes

Node* addToStack(Node* start, int num);
int removeFromStack(Node** start);
void freeStack(Node* start);

// --

int main(void) {

	int input = 0, toAdd = 0, currNum = 0;

	// list will go here, initialized as null
	Node* start = NULL;	

	while(1) {
		// peek into the stack and see what the current number is
		if(start != NULL) {
			Node* c = start;
			while(c->next != NULL) {
				c = c->next;
			}
			currNum = c->num;
		}

		if(start != NULL) {
			printf("\nYour number right now is: %d", currNum);
		} else {
			printf("\nList is currently empty");
		}
		printf("\n1: undo the last number");
		printf("\n2: add another number");
		printf("\n3: end");
		printf("\n> ");

		scanf("%d", &input);
		
		switch(input) {
			case 1:
				// undo last number
				if(start == NULL) {
					printf("\nNothing to undo");
				} else {
					printf("\nUndoing the %d", removeFromStack(&start));
				}
				break;
			case 2:
				// add another number
				
				printf("\nWhat number do you want to add?");
				printf("\n> ");
				
				scanf("%d", &toAdd);
	
				start = addToStack(start, toAdd);				

				break;
			case 3:
				// quit
				
				freeStack(start);
				
				return 0;

				break;
			default:
				printf("\nUnexpected input, try again");	
		}


	}

	return 0;
}

Node* addToStack(Node* start, int num) {
	Node* newNode = malloc(sizeof(Node));
	newNode->num = num;
	newNode->next = NULL;

	if(start == NULL) {
		start = newNode;
		return start;
	} else {
		Node* current = start;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;

	
	}

	return start;
}

int removeFromStack(Node** start) {
	int undone = 0;
	Node* c = *start;
	while(c->next != NULL) {
		c = c->next;
	}
	undone = c->num;
	

	// fix null ptr to end of list


	Node* x = *start;
	if(x == NULL) {
		return undone;
	} else {
		while(x->next != c && x->next != NULL) {
			x = x->next;
		}
		x->next = NULL;

		if(c != *start) {
			free(c);
		} else {
			*start = NULL;
		}
	}

	return undone;
}

void freeStack(Node* start) {
	if(start == NULL) {
		return;
	}
	Node* c = start;
	while(start->next != NULL) {
		c = start;
		start = start->next;
		free(c);
	}

	free(start);
}
