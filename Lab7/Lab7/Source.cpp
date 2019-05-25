#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>
int main() {
	testAll();
	std::cout << "Passed short tests" << std::endl;
	testAllExtended();
	std::cout << "Passed extended tests" << std::endl;
	return 0;
}