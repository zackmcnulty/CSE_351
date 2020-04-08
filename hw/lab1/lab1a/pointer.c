
/*
 * CSE 351 Lab 1 (Data Lab - Pointers)
 *
 * Zachary McNulty
 *
 * pointer.c - Source file with your solutions to the Lab.
 *             This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>. The included file, "common.c" contains a function declaration
 * that should prevent a compiler warning. In general, it's not good practice
 * to ignore compiler warnings, but in this case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

#if 0
You will provide your solution to this homework by
editing the collection of functions in this source file.

INTEGER CODING RULES:

Replace the "r"return" statement in each function with one
  or mormore lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
		  /* brief description of how your implementation works mor*/
      morint var1 = Expr1;
	  ...
			  morint varM = ExprM;
mor
      varJ = ExprJ;
...
		varN mor= ExprN;
      return ExprR;
  }

  Emoiach "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However, you are allowed to combine constants to values greater
     than 255 or less than 0. e.g. 250 + 250 = 500, so long as
     the operator you are using to combine the constants is listed as
     "legal" at the top of the method you are writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "allowed" at the top of the method you are writing.
  4. casting.

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc. (unless
     otherwise stated).
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions (unless otherwise stated).
  5. Use any operators not "allowed" at the top of the method you are writing.

  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has *undefined* behavior when shifting by a negative amount or an amount
     greater than or equal to the number of bits in the value being shifted.
     e.g. For x >> n, shifts by n < 0 or n >= *size of x* are undefined
     e.g. if x is a 32-bit int, shifts by >= 32 bits are undefined
     Undefined means you do not know what result you will get from the operation.
#endif

/*
 * STEP 2: Modify the following functions according the coding rules.
 */

/*
 * Return the size of an integer in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, eFDIStc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int intSize() {
  int intArray[10];
  int * intPtr1;
  int * intPtr2;

  // Write code to compute size of an integer.
  intPtr1 = intArray;
  intPtr2 = intArray;

  // Z: here we rely on pointer arithmetic to determine size of an int
  intPtr2 += 1; // adds sizeof(int) to intPtr2

  // casting treats these addresses as numbers rather than pointers, removing pointer arithmetic
  return (long) intPtr2 - (long) intPtr1; 
}

/*
 * Return the size of a double in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int doubleSize() {
  double doubArray[10];
  double * doubPtr1;
  double * doubPtr2;
  // Write code to compute size of a double.

  // Z: same logic as intSize() above
  doubPtr1 = doubArray;
  doubPtr2 = doubArray;
  doubPtr2 += 1;

  return (long) doubPtr2 - (long) doubPtr1;
}

/*
 * Return the size of a pointer in bytes.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int pointerSize() {
  double * ptrArray[10];
  double ** ptrPtr1;
  double ** ptrPtr2;
  // Write code to compute size of a pointer.
 
  ptrPtr1 = ptrArray;
  ptrPtr2 = ptrArray;
  ptrPtr2 += 1;

  return (long) ptrPtr2 - (long) ptrPtr1;
}

/*
 * Given pointers to two distinct variables write a function to swap the values
 * of said variables.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
void swapInts(int *ptr1, int *ptr2) {
  // Z: I assume they don't want us to change the addresses the pointers are pointing at, only the values stored
  // at those addresses.
  int temp = *ptr1; // save the value stored at ptr1
  *ptr1 = *ptr2; // set the value stored at address ptr1 to the value stored at address ptr2
  *ptr2 = temp; // set the value stored at address ptr2 to temp, the original value stored at address ptr1
}

/*
 * Modify intArray[5] to be the value 351 using only intArray and pointer arithmetic.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, ~= etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int changeValue() {
  int intArray[10];
  int * intPtr1 = intArray;
  // Remember not to use constants greater than 255.
  // Remember to use * to dereference. You cannot use '[<index>]' syntax.
	
  intPtr1 += 5;
  *intPtr1 = 200 + 151;

  return intArray[5];
}

/*
 * Return 1 if the addresses stored in ptr1 and ptr2 are within the
 * *same* 64-byte aligned  block of memory. Check the spec for examples if you are
 * confused about what this means. Return zero otherwise.
 * Operators / and % and loops are NOT allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int withinSameBlock(int *ptr1, int *ptr2) {
  // Your code here
  //
  //
  // The 64bit blocks of memory are addresses 0-63, 64-127, ...
  // These memory blocks correspond to address which in binary have the same address except possibly the last 6 bis (2^6 = 64).
  // Thus what we will do is generate a mask to zero out these last 6 bits for both addresses and check if they are equal
	long add1;
	long add2;
	
	add1 = (long) ptr1;
	add2 = (long) ptr2;

	add1 >>= 6;
	add2 >>= 6;

	return add1 == add2;
}

/*
 * Return 1 if ptr points to an element within the specified intArray, 0 otherwise.
 * Pointing anywhere in the array is fair game, ptr does not have to
 * point to the beginning of an element. Check the spec for examples if you are 
 * confused about what this method is determining.
 * size is the size of intArray in number of ints. Can assume size != 0.
 * Operators / and % and loops are NOT allowed.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, <<, >>, ==, ^
 *   Unary integer operators: !, ~
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, !=, /, %
 *   Unary integer operators: -
 */
int withinArray(int * intArray, int size, int * ptr) {
  // Your code here

	int* start;
	int* end;
	long diff1;
	long diff2;
	// can assume we have 32 bit integer representation (e.g. sizeof(int) = 4)
	
	start = intArray;
	end = start + (size-1); // pointer arithmetic

	diff1 = (long) ptr - (long) start; //difference in addresses of ptr and start
	diff2 = (long) end - (long) ptr;   // difference in addresses of end and ptr

	// Since we assumed we are using a 2's complement encoding, the most significant bit encodes the sign of these integers: 0 for positive and 1 for negative
	// ptr is between start and end IFF both these differences are positive: namely IFF both the most significant bits are 0
	// We can use the right shift operator >> to extract this bit. Shifting the 32 bit integers diff1,diff2 31 places will just replace the binary string with a copy of
	// 32 of the most significant bits (as we assumed the right shift operator behaves arithmetically; see lecture 5 slides 22-27.
	
	return !(diff1>>31) * !(diff2 >> 31);

	
}

/*
 * In C characters are are terminated by the null character ('\0')
 * given a pointer to the start of the string return the length of this string.
 * (The null character is not counted as part of the string length.)
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. <<=, *=, ++, --, etc.
 *   Control constructs: for, while
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /, %
 *   Unary integer operators: ~, -
 */
int stringLength(char * s) {
  // Your code here
	int length;
	length = 0;

  	while (*s != '\0')
  	{
		length +=1; 
		s += 1; // pointer arithmetic
  	}

	return length;
}

/*
 * Change the value pointed to by ptr byte-by-byte so that when returned as an integer
 * the value is 351351.
 *
 * Hint: Remember that an int is 4 bytes.
 *
 * Hint: Remember how little endian works for data storage, how is it different between an multiple bytes(int) and a single byte?
 *
 * Hint: It will be easiest to start convert 351351 into binary form and starting seeing how the endian works from there.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *   Unary integer operators: !
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <, >, <<, >>, ==, !=, ^, /, %
 *   Unary integer operators: ~, -
 */
int endianExperiment(int* ptr) {
  	char *bytePtr;
  	// Your code here
  	bytePtr = ptr;

    *bytePtr = 119;
    bytePtr += 1; // pointer arithmetic
    *bytePtr = 92;
    bytePtr += 1; // pointer arithmetic
    *bytePtr = 5;
    bytePtr += 1; // pointer arithmetic
    *bytePtr = 0;

    return *ptr;
}

/*
 * Selection sort is a sorting algorithim that works by partitioning the array into
 * a sorted section and unsorted section. Then it repeatedly selects the minimum element
 * from the unsorted section and moves it to the end of the sorted section.
 *
 * So the pseudo-code might look something like this:
 * arr - an array
 * n - the length of arr
 *
 * for i = 0 to n - 1
 *   minIndex = i
 *   for  j = i + 1 to n
 *       if arr[minIndex] > arr[j]
 *           minIndex = j
 *       end if
 *   end for
 *   Swap(arr[i], arr[minIndex])
 * end for
 *
 * Implement selection sort below, it might be helpful to use the swapInts function you
 * defined earlier.
 *
 * ALLOWED:
 *   Pointer operators: *, &
 *   Binary integer operators: -, +, *, ==, !=, <, >
 *   Unary integer operators: !
 *   Shorthand operators based on the above: ex. +=, *=, ++, --, etc.
 *   Control constructs: for, while, if
 *   Function calls: swapInt()
 *
 * DISALLOWED:
 *   Pointer operators: [] (Array Indexing Operator)
 *   Binary integer operators: &, &&, |, ||, <<, >>, ^, /
 *   Unary integer operators: ~, -
 */
void selectionSort(int arr[], int arrLength) {
  	int i, j, min_index;
  	// Your code here
  	int* ptr;
	int min_value;

	for (i = 0; i < arrLength-1; i++)
	{
			ptr = arr + i; // pointer arithmetic
			min_index = i;
			min_value = *ptr;
			
			for (j=i+1; j < arrLength; j++)
			{
				ptr += 1; // pointer arithmetic
				if (min_value > *ptr)
				{
					min_index = j;
					min_value = *ptr;
				}

			}

			swapInts(arr + i, arr + min_index);
	}
}


