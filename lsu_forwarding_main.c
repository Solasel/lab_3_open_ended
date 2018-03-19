/* We exploit load forwarding by loading an address immediately
 * 	after storing to it.
 *
 * Because there is no address calculation, none of the loads
 * 	are speculative, and so all the values can be forwarded. */

#include "util.h"

//--------------------------------------------------------------------------
// lsu_forwarding function

void lsu_forwarding( /* args */ )
{
	/* recursively generates an array with the first i natural numbers */
	int nats[100];
	nats[0] = 0;

	volatile int i, j;

	for (i = 1; i < 100; i++) {
		//nats = malloc(i*sizeof(int));

		/* every natural number is the previous natural number +1. */
		for (j = 1; j < i; j++)
			nats[j] = nats[j-1] + 1;

		//free(nats);
	}
}

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  setStats(1);
  lsu_forwarding();
  setStats(0);

  // Check the results
  return 0;
}
