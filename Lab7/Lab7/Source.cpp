#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <assert.h>

bool rel(TKey k1, TKey k2) {
	return k1 <= k2;
}

void testExtraFunctionality()
{
	SortedMultiMap s(rel);
	s.add(1, 3);
	s.add(1, 4);
	s.add(2, 3);
	s.add(3, 4);
	vector<TValue> v = s.removeKey(1);
	assert(v[0] == 3);
	assert(v[1] == 4);
	assert(s.size() == 2);
}

int main() {
	testExtraFunctionality();
	testAll();
	std::cout << "Passed short tests" << std::endl;
	testAllExtended();
	std::cout << "Passed extended tests" << std::endl;
	return 0;
}