#include<stdio.h>

int main(){
	int y;
	int z;
	int result;
	int x = 0x49; // 0b0100 1001

	y = x | (x << 6);

	printf("y: %d\n", y);

	z = y | (y << 12);

	printf("z: %d\n", z);
	
	
	result = z | (y << 24);
	printf("result: %d\n", result);


}

