// Alexander Gompper
// AEG6X6
// June 20 2016
// Lab 3


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void collatz(int x);
int hexConverter(int x);

int main(void) {
	int col = 0, hex = 0;
	
	printf("\nEnter a number for Collatz list: ");
	printf("\n?");
	scanf("%d", &col);
	collatz(col);

	printf("\nEnter a hexadecimal number to convert to decimal: ");
	printf("\n?");
	scanf("%d", &hex);
	printf("\n%d in hexadecimal <-> %d in decimal", hex, hexConverter(hex));
	return 0;
}

void collatz(int x) {
	printf("%d", x);
	if(x == 1) {
		return;
	} else {
		printf(" -> ");
		if((x % 2) == 0) {
			collatz(x / 2);
		} else {
			collatz((x * 3) + 1);
		}
	}
}

int hexConverter(int x) {
	if(x < 10) {
		return x;
	}
	return 16 * hexConverter(x / 10) + x % 10;
}	



