#include<stdio.h>

float sum_elements(float a[], unsigned length);

int main()
{
	unsigned x = 0;
	int i = 0;

	printf("%u", x-1);
	
	float a[10];

//	sum_elements(a, 0);
}


float sum_elements(float a[], unsigned length) 
{
	int i;
	float result = 0;

	for (i=0; i <= length-1; i++)
	{
		result += a[i];
	}
	return result;
}
