#include <stdio.h>

int main (int argc, char* argv[]) {
  // Declare then assign
  int x;
  x = 2;

  // Or do both
  int y = 5;

  // Print a formatted string 
  // Note that \n is a newline
  printf("Hello world!\nx + y = %d\n", x + y);
 
  // Note the return type of main is int
  // A program typically returns 0 if everything went ok
  return 0;
}
