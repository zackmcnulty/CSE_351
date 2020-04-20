#include<stdio.h>
#include<stdlib.h>


int main() {

	char str[20] = "12 3 4 5 hello world";
	long ret = strtol(str, 0x0, 10);
	printf("%ld\n", ret);
}
