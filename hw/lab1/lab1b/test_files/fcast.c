#include<stdio.h>
#include<stdlib.h>



int main(int argc, char* argv[]) {
	unsigned result;
	int x = atoi(argv[1]);
	int exp;
	int sign;

	if (!x) {
		result = 0;

	} else {

		sign = !!(x & (0x1 << 31));
		printf("sign: %d\n", sign);

		if (sign) { // if negative, convert to positive
			x = ~x + 1;  // x = -x = ~x + 1  *** this will have issues with Tmin
		}


		// Find E
		exp = -1;
		int current = x;
		while (!!current) {
			current = current >> 1;
			exp += 1;
		}

		int E = exp + 127;

		printf("exp, E: %d,  %d\n", exp, E);
		int M = x >> 9;


		printf("new sign: %d\n", sign << 31);
		result = (sign << 31) + (E << 23) + M;


	}



	printf("result: %d\n", result);
}
