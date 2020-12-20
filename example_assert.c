
#include "beam.h"

int main(int argc, char **argv) {
	if (B_ASSERT(argc == 1)) {
		B_SKIP();
	}
	else {
		if (B_ASSERT(argc % 2)) {
			B_FAILm("even_params");
		}
		else {
			B_PASSm("odd params");
		}
	}
	B_SUMMARY();
	return 0;
}
