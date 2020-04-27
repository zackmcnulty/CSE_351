/*
CSE 351 Lab 4, Part 1 - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*Mystery 0:
 *
 * Cache block size: 64 bytes
 * Cache size: 262144 bytes
 * Cache associativity: 1
 *
 * Mystery 1:
 *
 * Cache block size: 8 bytes
 * Cache size: 16384 bytes
 * Cache associativity: 4
 *
 * Mystery 2:
 *
 * Cache block size: 16 bytes
 * Cache size: 65536 bytes
 * Cache associativity: 16
 *
 * Mystery 3:
 *
 * Cache block size: 2 bytes
 * Cache size: 131072 bytes
 * Cache associativity: 2
 */







/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
	// all we have to do is sequentially access elements of data until we finally get a miss.
	// e.g. the initial access_cache(0), which generates a miss on the cold cache, loads in memory from address 0 to blocksize-1 into the cache,
	// so we just traverse these addresses one at a time until we get another miss.
	//
	flush_cache();

	int current_address = 1;

	access_cache(0);
	while (access_cache(current_address)) {
		current_address +=1;
	}

  	return current_address;
}

/*
   Returns the size (in B) of the cache.
*/
int get_cache_size(int block_size) {
	// We are allowed to assume the cache size is a power of two; e.g. 2^k
	// The basic idea here is that adjacent blocks map to different sets in memory.

	flush_cache();

	int size = block_size;
	access_cache(0);
	access_cache(block_size);

	while (access_cache(0)) {
		size *=2; // can assume cache size is power of two

		// keep adding consecutive blocks until we run out of space and evict the data at address 0!
		for(int i=0; i <= size; i+= block_size){
			access_cache(i);
		}
	}

	return size;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int cache_size) {
	// Note that the cache is modular in the sense that as long as we don't change the index bits
	// of an address, we know the result will still map to the same set. In the worst case scenario of a direct-mapped cache (one associativity)
	// the cache_size = block size * (num sets). Namely cache_size = 2^{index bits + offset bits}. Thus even if there is a block size of one 
	// (and hence offset bits = 0) we know 
	// the binary representation for the cache_size does not overlap with any of the index bits. Therefore the cache is modular the cache size.
	// Thus we know addresses 0, cache_size, 2*cache_size, ... all map to same set.
	


	flush_cache();

	int associative = 0;
	access_cache(0);

	while (access_cache(0)) {
		associative += 1;
		for (int i=1; i <= associative; i++){
			// we have to reaccess all the other addresses to ensure the block at zero
			// was the least recently used one (for the replacement policy)
			access_cache(cache_size * i);
		}
	}

	return associative;
	
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}
