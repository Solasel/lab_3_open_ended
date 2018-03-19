/* Set MAX_SIZE to be larger than you really expect the LSU queue
 * 	to be.
 *
 * Then, vary TEST from the minimum possible size upwards. It should
 * 	be fairly similar across iterations, until there is a huge
 * 	drop in performance. This occurs when TEST is equal to the
 * 	size of the LSU queue. */

#include "util.h"
#define MAX_SIZE (64)
#define ITERS (100)

/* Change this value, and see when the
 * benchmark gets significantly slower */
#define TEST (4)

//-------------------------------------------------------------------------
// lsu_size_test function

void lsu_size_test( /* args */ )
{
	int values[MAX_SIZE];
	volatile int i, j, val;

	for (i = 0; i < ITERS; i++) {
			
		for (j = 0; j <= TEST; j++)
			values[j] = j;

		val = values[TEST];

		for (; k < MAX_SIZE; j++)
			values[j] = j;
	}
}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  setStats(1);
  lsu_size_test();
  setStats(0);

  // Check the results
  return 0;
}
