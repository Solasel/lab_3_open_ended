/* We exploit speculative loading by loading an address immediately
 * 	after storing to it.
 *
 * The difference is that the store has a complex address (multiply
 * 	then divide), while the load is just a simple offset. Therefore,
 * 	the store address should not be known before the load fires off.
 *
 * The load will be optimistically fired to memory, and will then be found
 * 	wrong (the store was to the same address). This constitutes an LSU
 * 	failure. */

#include "util.h"

//--------------------------------------------------------------------------
// lsu_failure function

void lsu_failure( /* args */ )
{
	/* recursively generates an array with the first i natural numbers */
	int nats[100];
	nats[0] = 0;

	volatile int i, j, dest, val;

	for (i = 1; i < 100; i++) {
		//nats = malloc(i*sizeof(int));

		/* every natural number is the previous natural number +1. */
		for (j = 1; j < i; j++) {
			val = nats[j-1] + 1;

			/* divides are slow, so we use them to clog up
			 * the calculation of store address. */
			dest = 16 * j;
			dest /= 2;
			dest /= 2;
			dest /= 2;
			dest /= 2;

			nats[dest] = val;
		}

		//free(nats);
	}
}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  setStats(1);
  lsu_failure();
  setStats(0);

  // Check the results
  return 0;
}
