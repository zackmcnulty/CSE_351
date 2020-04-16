#include<stdio.h>

int main(int argc, char* argv[]){

	int x = atoi(argv[1]);

	int mask = 0x1 << 31;
	int sign_x = x & mask;
	int sign_x_minus_one = (x + ~0x0) & mask;

	printf("sign(x): %d\n", sign_x);
	printf("sign(x-1): %d\n", sign_x_minus_one);
}
