#include<stdio.h>

int main() {
	

	int x = 10;
	int* ptr = &x;

	char* bytePtr = ptr;

	*bytePtr = 119;
	bytePtr += 1;
	*bytePtr = 92;
	bytePtr += 1;
	*bytePtr = 5;
	bytePtr += 1;
	*bytePtr = 0;

	printf("%d\n", *ptr);
}
