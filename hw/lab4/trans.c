/*
CSE 351 Lab 4, Part 2 - Matrix Transposes
*/

/* 
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {

// Since the block sizes are 32 bits, we can fit 4 ints per block
// The cache itself is 2^10 = 1024 bits = 256 ints large. Since this is a direct mapped cache, this
// implies elements of our 2D array that get mapped to same set in cache are 256 ints apart: 8 rows down in the 32 x 32 case
// and 4 rows down in the 64 x 64 case. Hence 8 x 8 blocks and 4 x 4 blocks will work decently in the 32 x 32 and 64 x 64 cases respectively.


	int block_height;
	int block_width;

	if (N == 32){ // 32 x 32 case
		block_height = 8;
		block_width = 8;
	} else { // 64 x 64 case
		block_height = 4;
		block_width = 4;
	}

	int blocks_tall = M / block_height;
	int blocks_wide = N / block_width;

	for (int i=0; i < blocks_wide; i++){
		for (int j=0; j < blocks_tall; j++){
			for (int ii = i*block_width; ii < (i+1)*block_width; ii++){
				for (int jj  = j*block_width; jj < (j+1)*block_width; jj++) {
					B[jj][ii] = A[ii][jj];
				}
			}
		}
	}

}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

