#include <stdio.h>
#include <stdlib.h>
 
typedef struct n_
{
	int num;
	struct n_* left;
	struct n_* right;
} Node;

// Prelab 7 functions
Node* addNodeToTree(Node* root, int x);
void printTree(Node* root);
int calcPrint(Node* root, int is_left, int offset, int depth, char s[20][255]);
void freeTree(Node* root);

// Lab 7 functions
void printSortedList(Node* root);
Node* removeLeaves(Node* root);
Node* flipTree(Node* root);


int main(void) {
	
	Node* root = NULL;
	int input = 0;
	while(1) {
		// PRINT THE LIST (flat)
		system("clear");
		printTree(root);
		printSortedList(root);
		
		printf("\n1: add a node");
		printf("\n2: remove leaves");
		printf("\n3: flip tree");
		printf("\n-1: quit");
		printf("\n> ");
		scanf("%d", &input);

		switch(input) {
			case 1:
				printf("\nAdd a node: ");
				scanf("%d", &input);

				root = addNodeToTree(root, input);
				system("clear");
				break;
			case 2:
				root = removeLeaves(root);
				break;
			case 3:
				root = flipTree(root);
				break;
			case -1:
				freeTree(root);
				exit(0);
				break;
			default:
				printf("\nIncorrect selection, please choose a number 1-3");
		}

		
	}
	
	
	freeTree(root);
	return 0;
}

Node* addNodeToTree(Node* root, int x) {
   	if(root == NULL) {
       		 Node* newNode = (Node*)malloc(sizeof(Node));

        	newNode->num = x;
        	newNode->left = NULL;
        	newNode->right = NULL;
        	
		return newNode;
	} else {
		if(x > root->num) {
			root->right = addNodeToTree(root->right, x);
		}
		if(x < root->num){
			root->left = addNodeToTree(root->left, x);
		}
	}

	return root;
}

void freeTree(Node* root) {
	if(root == NULL) {
		return;
	}
    	
	freeTree(root->left);
	freeTree(root->right);
	
	free(root);
}

// -- LAB 7 FUNCTIONS BELOW --
// ---------------------------


void printSortedList(Node* root) {
	if(root == NULL) {
		return;
	}
	printSortedList(root->left);
	printf("%d ", root->num);
	printSortedList(root->right);
	
}

Node* removeLeaves(Node* root) {
	if(root == NULL) {
		return NULL;
	}

	if(root->left == NULL && root->right == NULL) {
		free(root);
		return NULL;
	}

	root->left = removeLeaves(root->left);
	root->right = removeLeaves(root->right);

	return root;
}

Node* flipTree(Node* root) {
	if(root != NULL) {
		Node* t = root->left;
		root->left = flipTree(root->right);
		root->right = flipTree(t);
	}
	return root;
}



// -- GIVEN PRINT FUNCTIONS BELOW--
// -------------------------------

//DON'T TOUCH UNLESS YOU WANT TO EXPERIMENT
int calcPrint(Node* root, int is_left, int offset, int depth, char s[20][255])
{
	char b[20];
    int width = 5;
	
 	if (!root) return 0;
    sprintf(b, "(%03d)", root->num);
	int left  = calcPrint(root->left,  1, offset, depth + 1, s);
    int right = calcPrint(root->right, 0, offset + left + width, depth + 1, s);

	int i;
    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {
        for (i = 0; i < width + right; i++)
	       s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }

	return left + width + right;
}

//SAME AS THE FUNCTION ABOVE
void printTree(Node* root)
{
	char s[20][255];
	int i;
	for(i = 0; i < 20; i++)
		sprintf(s[i], "%80s", " ");
	
	calcPrint(root, 0, 0, 0, s);
	for(i = 0; i < 20; i++)
	{
		printf("%s\n", s[i]);
	}
}
