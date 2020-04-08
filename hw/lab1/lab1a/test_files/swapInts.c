#include<stdio.h>

int main() 
{
	int x = 4;
	int y = 7;
	int* ptr1 = &x;
	int* ptr2 = &y; 

	// code from hw
	printf("ptr1: %x\n", ptr1);
	printf("ptr2: %x\n", ptr2);

	int temp = *ptr1;
	printf("temp: %d\n", temp);

	*ptr1 = *ptr2; 
	printf("*ptr1 : %d\n", *ptr1);

	*ptr2 = temp;
	printf("*ptr2 : %d\n", *ptr2);
	printf("*ptr1 : %d\n", *ptr1);

	printf("ptr1: %x\n", ptr1);
	printf("ptr2: %x\n", ptr2);
	
}

