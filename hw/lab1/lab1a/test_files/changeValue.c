#include<stdio.h>


int main()
{
	int intArray[10];
	int* intPtr1 = intArray;

	intPtr1 += 5;
	*intPtr1 = 351; 

	printf("%d\n", intArray[5]);


}
