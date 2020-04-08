#include<stdio.h>

int main() 
{

		int intArray[10];
		int* intPtr1 = intArray;
		int* intPtr2 = intArray;
		
		intPtr2 += 1;

		printf("%ld\n", (long) intPtr2- (long)intPtr1);
		printf("%ld\n", sizeof(int));
//////////////////////////////////////////////////
//
//
		double doubleArray[10];
		double* doublePtr1 = doubleArray;
		double* doublePtr2 = doubleArray;
		
		doublePtr2 += 1;

		printf("%ld\n", (long) doublePtr2- (long)doublePtr1);
		printf("%ld\n", sizeof(double));


//////////////////////////////////////////
		double* ptrArray[10];
		double** ptrPtr1 = ptrArray;
		double** ptrPtr2 = ptrArray;
		
		ptrPtr2 += 1;

		printf("%ld\n", (long) ptrPtr2- (long)ptrPtr1);
		printf("%ld\n", sizeof(double*));


}
