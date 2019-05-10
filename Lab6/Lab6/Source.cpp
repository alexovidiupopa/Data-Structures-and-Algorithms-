#include "ExtendedTest.h"
#include "ShortTest.h"
#include <iostream>
#include <Windows.h>
#include <crtdbg.h>
int main() {
	testAll();
	std::cout << "passed short tests" << std::endl;
	testAllExtended();
	std::cout << "passed extended tests" << std::endl;
	_CrtDumpMemoryLeaks();
	return 0;
}