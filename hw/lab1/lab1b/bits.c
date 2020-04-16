/* 
 * CS:APP Data Lab 
 * 
 * Zachary McNulty
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#ifndef COMMON_H
#include "common.h"
#endif

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However, you are allowed to combine constants to values greater
     than 255 or less than 0. e.g. 250 + 250 = 500, so long as
     the operator you're using to combine the constants is listed as
     "legal" at the top of the method you're writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "legal" at the top of the method you're writing.
  4. Shorthand versions of "legal" operators (ex. you can use ++ and += if + is legal)
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */
#endif

/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	// x AND y is logically equivalent to NOT (NOT x or NOT y)
  	return ~(~x | ~y);
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	// x XOR y is logically equivalent to NOT( NOT x AND NOT y) AND NOT (x AND y)
	// The first condition checks that x,y aren't both zero and the latter condition checks that x,y aren't both one
	
  	return (~(~x & ~y)) & (~(x & y));
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  // Since we have a 32-bit machine, words are 32 bits long
  // 0x1F = 0b1001
  // Here we reuse the repeating structure and a series of shifts to generate the large number
  int x;
  int y;
  int z;
  int result;

  x = 0x49; // 0b 0100 1001
  y = x | (x << 6); // y = 0b1001001001
  z = y | (y << 12); // z = 0b10 0100 1001 0010 0100 1001
  result = z | (y << 24); // here we rely on modular arithmetic

  return result;


}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // shift the bit representation of x so that the desired byte lies in the least signficant bit, then mask that byte out.
  // Note that n << 3 == 2^3 * n == 8n
  return (x>> (n <<3)) & 0xFF;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	int mask;
	mask = ((!!n) << 31); // binary representation 0b10000000... if n is nonzero, or 0b0000 if n is zero

	// issue: n-1 is negative if n=0
	mask = mask >> (n-1); //binary representation 0b111111...11000 with n ones
	mask = ~mask;
    return (x >> n) & mask; //shift right arithmetically, and wipe away the possible ones added to the front with mask
}
/*
 * invert - Return x with the n bits that begin at position p inverted
 *          (i.e., turn 0 into 1 and vice versa) and the rest left
 *          unchanged. Consider the indices of x to begin with the low-order
 *          bit numbered as 0.
 *   Can assume that 0 <= n <= 31 and 0 <= p <= 31
 *   Example: invert(0x80000000, 0, 1) = 0x80000001,
 *            invert(0x0000008e, 3, 3) = 0x000000b6,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
*/
int invert(int x, int p, int n) {
	int mask;
	mask = ~((~0x0) << n); // 0b00000...0011111 with n ones
	mask = mask << p; // 0b0000...00111110000...00 with n ones starting at position p

	// First part just takes all the bits of x outside the n,p portion 
	// second part flips all the bits inside the n,p portion
    return (x & ~mask) | (~x & mask);
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	// Zero and Tmin are the only elements where the sign changes from positive to negative when we subtract one.
	// (Tmin changes to Tmax when we subtract one due to overflow)
	int mask;
	int sign_x;
	int sign_x_minus_one;

	mask = 0x1 << 31; // for extracting the most significant bit which encodes sign

	// Extract sign bits for both x and x-1
	// sign(x) = 0b100000.... if x is negative and sign(x) =0 if x is nonnegative
	sign_x = x & mask;
	sign_x_minus_one = (x + ~0x0) & mask;

	// sign(x) ^ sign(x-1) = 0b10000... if x is zero (or Tmin) and 0 if x is nonzero
	// Hence (sign(x) ^ sign(x-1)) >> 31 = 0b1111... = -1 if x is zero (or Tmin) and 0 if x is nonzero
	// Thus we just have to negate this and we are done! Remember -x = ~x + 1
	// ~(sign(x) ^ sign(x-1)) >> 31) + 1
	// The extra & ~sign_x below handles the Tmin case by changing the most significant bit to a zero 
	return ~(((sign_x ^ sign_x_minus_one) & ~sign_x) >> 31) + 1;
}
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
	// !!x handles the x=0 case
	// The number x is negative if the most significant bit is a one, and nonnegative if it is a zero
	// (x >> 31) = 0b111.. = -1 if x is negative, and zero if x is nonnegative
	// Hence the code breaks into three cases:
	// x is negative:  -1 + -1 + 1 = -1
	// x == 0 : 0 + 0 + 0
	// x is postive : 0 + 0 + 1
    return ((x>>31) + (x>>31) + !!x);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int largest;
  int smallest;
  int diff1;
  int diff2;
  int mask;
  int sign_x;

  // Largest and smallest integers representable by n bits (2 complement)
  // Here we use sign extension to represent the smallest n-bit number as a 32 bit integer.
  smallest = ~0x0 << (n-1);
  largest = ~smallest;

  // check whether or not  smallest <= x <= largest. Namely that x - smallest, largest - x are nonnegative
  // Remember -y = ~y + 1
  diff1 = x + (~smallest +1);
  diff2 = largest + (~x + 1);

  mask = 0x1 << 31;
  sign_x = !!(x & mask);

  // To avoid possible overflow, it is easier to also consider the sign of x
  // If diff1 is nonnegative and x is negative,  or if diff2 is nonnegative and x nonnegative
  return (!(diff1 & mask) & sign_x) |  (!(diff2 & mask) & !sign_x);
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  	// Remember that over flow will occur if x,y have same sign but x + y has a different sign (L5 slide16)
	// For signed integers, the sign is encoded by the most significant bit: 0 represents positive and 1 negative
		
	int mask;
	int sign_x;
	int sign_y;
	int sign_sum;

	mask = 0x1 << 31; // 0b100000...

	// The !! converts all nonzero entries to 0x1
	sign_x = !!(x & mask);
	sign_y = !!(y & mask);
	sign_sum = !!((x+y) & mask);

	// If sign(x) =/= sign(y) then overflow cannot occur. If sign(x) == sign(y) == sign(x+y), then no overflow occurs.
	// NOT (sign_x == sign_y) OR (sign_x == sign_sum)  --> true if no overflow occurs
	return !!(sign_x ^ sign_y) | !(sign_x ^ sign_sum);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
	// To be a power of two, x must have a single one in its binary representation and it cannot
	// be in the most significant bit
  return 2;
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
	unsigned mask;
	
	// Determine whether or not we fall into the NaN case.
	// first condition checks if E == 0xFF (actually checks that ~E == 0x0)
	// second condition checks if M is nonzero.
	if (!((~uf << 1) >> 24) &&  !!(uf << 9)) { //NaN Case
		return uf;

	} else {

		//here we use the modular arithmetic of unsigned integers to complement the most significant bit.
		// namely 1000 + 0101 = 1101 and 1000 + 1101 = 0101
		mask = ~0x0 << 31;
		return uf + mask;
	}
}



/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
	// See floatNegate for explanation of this conditionals
	if ((!((~uf << 1) >> 24) &&  !!(uf << 9))  || (!((~ug << 1) >> 24) &&  !!(ug << 9))){  //NaN Case
		return 0;
	}

	if (!(uf << 1) && !(ug << 1)) { // +-0 case
		return 1;
	}

	// The representation for a floating point is unique (besides the above edge cases) and so now all
	// we have to do is check these binary representations are identical.
	return !(uf ^ ug);
}
/* 
 * floatInt2Float - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatInt2Float(int x) {
	
	// float = (-1)^{sign}*2^{exp} * 1.M with exp = E - Bias
	// 1 bit for sign, 8 for E, 23 for M
	
	// Note since we are only dealing with integers, we can assume we are always using normalized
	// numbers after we handle the x=0 case
	unsigned sign
	int exp;
	unsigned E;
	int M;
	int current;

	if (!x ) { //handles the x=0 case 
		return 0;
	}

	sign = (unsigned) !!(x & (0x1 << 31));

	// Since x is an integer, we don't have to worry about the exponent being negative
	// After right shifting (arithmetically) negative numbers are going to collapse down to -1 = 0b11111
	// and positive numbers are going to collapse to
	exp = -1;
	while (!current) { // while current != 0
		current = current >> 1;
		exp += 1;
	}
	
	E = (unsigned) (exp + 127);  // exp + Bias = E with Bias = 2^7-1 =127
	
	
  return 2;
}




