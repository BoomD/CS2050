#include <stdio.h>
#include <stdlib.h>

int sumOfDigits(int x);
void reverseArray(int* x, int firstIndex, int lastIndex);
int fib(int x);

int main(void) {
	int sum = 0, fibb = 0, i = 0;
	int *array = malloc(sizeof(int) * 5);

	printf("\nEnter a number to sum the digits of: ");
	printf("\n?");
	scanf("%d", &sum);
	printf("\nSum of digits is: %d\n", sumOfDigits(sum));

	printf("\nEnter a series of 5 numbers: ");
	for(i = 0; i < 5; i++) {
		printf("\n?");
		scanf("%d", &array[i]);
	}
	reverseArray(array, 0, 4);
	printf("\nArray in revers order is: ");
	for(i = 0; i < 5; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	printf("\nEnter a number to find that index in the Fibbonacci Sequence: ");
	printf("\n?");
	scanf("%d", &fibb);
	printf("\nThat index in Fibbonacci Sequence is: %d\n", fib(fibb));

	free(array);
	

	return 0;
}

int sumOfDigits(int x) {
	int sum = 0;
	if(x == 0) {
		return 0;
	}
	sum = x%10 + sumOfDigits(x/10);

	return sum;
}

void reverseArray(int *x, int firstIndex, int lastIndex) {
	int swap;
	if(firstIndex >= lastIndex) return;
	swap = x[firstIndex];
	x[firstIndex] = x[lastIndex];
	x[lastIndex] = swap;
	reverseArray(x, firstIndex+1, lastIndex-1);	
	
}

int fib(int x) {
	if(x == 0) {
		return 0;
	} else if(x == 1) { 
		return 1;
	} else {
		return(fib(x-1) + fib(x-2));
	}
}
	
