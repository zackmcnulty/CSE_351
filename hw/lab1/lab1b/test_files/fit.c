#include<stdio.h>


int main(int argc, char* argv[]) {

	int x =  atoi(argv[1]);
	int n = atoi(argv[2]);
	int smallest = ~0x0 << (n-1);
	int largest = ~smallest;

	printf("x: %d  n: %d\n", x, n);
	printf("smallest: %d\n", smallest);
	printf("largest: %d\n", largest);

	int diff1 = x + (~smallest + 1);
	int diff2 = largest + (~x + 1);

	printf("diff1: %d\n", diff1);
	printf("diff2: %d\n", diff2);


	int mask = 0x1 << 31;
	int result = !(diff1 & mask) & !(diff2 & mask);

	printf("result: %d\n", result);
}

