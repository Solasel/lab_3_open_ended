/* We test how large the lsu queues are by noticing the following property:
 *
 * 	Say the queue has n entries. If we issue n+1 stores, followed by
 * 	a load to the same address as the last store, we will get a memory
 * 	ordering failure.
 *
 * Note that n+1 stores followed by a load will also break queues of size
 * 	k < n.
 *
 * So, this program goes through series of 1 store followed by a load,
 * 	two stores followed by a load, all the way up to MAX_LSU stores 
 * 	followed by a load.
 *
 * 	Note that each iteration is repeated ITERS times
 * 	to make the difference more apparent.
 *
 * Because we always store MAX_LSU times, and only vary when we load,
 * 	every iteration takes the same amount of time, UNLESS there is
 * 	a memory ordering failure, in which case it takes longer.
 *
 * Therefore, we can easily separate out how big the lsu queues are by
 * 	figuring out what percentage of the iterations it failed. For
 * 	instance, if the lsu queue was of size MAX_LSU/2, it would have been
 * 	fast for half of the iterations, and slow for the other half. */

#include "util.h"
#define MAX_LSU (64)
#define ITERS (25)

//-------------------------------------------------------------------------
// lsu_size_test function

void lsu_size_test( /* args */ )
{
	int values[MAX_LSU];
	volatile int i, j, k, val;

	for (i = 0; i < MAX_LSU; i++) {

		for (j = 0; j < ITERS; j++) {
			
			for (k = 0; k <= i; k++)
				values[k] = k;

			val = values[i];

			for (; k < MAX_LSU; k++)
				values[k] = k;
		}
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
