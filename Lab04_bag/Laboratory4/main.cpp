#include "Bag.h"
#include "MyShortTest.h"
#include "ShortTest.h"
#include "ExtendedTest.h"

int main()
{
	my_short_test();
	test_prime();
	test_next_prime();

	testAll();
	testAllExtended();
	test_new_functionality();
	return 0;
}