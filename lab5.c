#include <stdio.h>
#include <stdlib.h>

// -- Structures

typedef struct n_ {
	int x;
	int y;
	struct n_* nextNode;
} Node;

// -- Function prototypes

Node* importList(char* filename);
Node* removeNodes(Node* start, int x);
void printList(Node* start);
void freeList(Node* start);

// -- Main

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("\nCorrect usage: ./a.out <filename.txt>");
		exit(1);
	}	

	Node* start = importList(argv[1]);
	if(start == NULL) {
		printf("\nEmpty list");
		return 0;
	}
	int input = 0;
	while(1) {
		
		printList(start);

		printf("\nEnter an x value(-1 to exit): ");
		scanf("%d", &input);
		switch(input) {
			case -1:
				freeList(start);
				return 0;
				break;
			default:
				start = removeNodes(start, input);
		}
	}

	freeList(start);
	return 0;
}


// -- Function definitions


Node* importList(char* filename) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("\nFile reading error");
		exit(1);
	}

	Node* start = NULL;
	Node* t = NULL;
	int x = 0, y = 0;
	
	while(fscanf(fp, "%d %d", &x, &y) == 2) {
		Node* n = (Node*)malloc(sizeof(Node));
		n->x = x;
		n->y = y;
		n->nextNode = NULL;

		if(start == NULL) {
			t = start = n;
		} else {
			t = t->nextNode = n;
		}
	}

	fclose(fp);

	return start;
}

Node* removeNodes(Node* start, int x) {
	Node* t;
	if(start == NULL) {
		return NULL;
	} else if(start->x == x) {
		t = start->nextNode;
		free(start);
		t = removeNodes(t, x);
		return t;
	} else {
		start->nextNode = removeNodes(start->nextNode, x);
		return start;
	}
}

void printList(Node* start) {
	if(start == NULL) {
		printf("NULL\n");
		return;
	}
	
	printf("(%d,%d) -> ", start->x, start->y);
	printList(start->nextNode);
}

void freeList(Node* start) {
	Node* t = start;
	while(start != NULL) {
		t = start;
		start = start->nextNode;
		free(t);
	}
}
