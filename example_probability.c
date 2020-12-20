
#include <stdlib.h>

#define B_PASS_SILENTLY
#define B_FAIL_SILENTLY
#define B_KEEP_COUNT

#include "beam.h"

#define rand_nr() ((double) rand())/RAND_MAX

#define NPOINTS 10000

int main() {
	int n = NPOINTS;
	while (n--) {
		if (rand_nr() < 0.7) {
			B_PASS();
		} else {
			B_FAIL();
		}
	}
	B_SUMMARY();
	printf("p = %.2lf\n", ((double) b_count_passed) / NPOINTS);
	printf("p' = %.2lf\n", ((double) b_count_failed) / NPOINTS);
	return 0;
}
