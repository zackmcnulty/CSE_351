#include<stdio.h>

int main(int argc, char* argv[])
{


	int* ptr1 = (int*) 0x40;
	int* ptr2 = (int*) 0x0;
	
	long add1 = (long) ptr1;
	long add2 = (long) ptr2;
	add1 >>= 6;
	add2 >>= 6;

	printf("add1 %u", add1);
	printf("ptr1: %p\n", ptr1);
	printf("ptr2: %p\n", ptr2);

	//ptr1 >> 6;
	//ptr2 >> 6;

	printf("%d\n", add1 == add2);
}
