#include<stdio.h>

int main() {


	int x = 0x87654321;
	int n = 0;

	printf("test: %\d\n", !10);
	printf("test: %\d\n", !!10);

	int mask; 
	mask = ~0x0;
	mask = mask << (32-n);
	printf("mask: %d\n", mask);
	mask = ~mask;

	printf("mask: %d\n", mask);

	printf("result: %d\n", (x >> n) & mask);

}
