#include "myVector.h"

int main(void) {

	//test vector
	myVector<int> t;

	//t.empty();
	t.push_back(10);
	t.push_back(2);
	t.push_back(40);
	t.push_back(35);
	t.push_back(123);
	t.push_back(49);
	t.push_back(203);
	t.push_back(1110);

	t.capacity();

	t.pop_back();

	t.resize(5);
	t.reserve(10);

	t.clear();
	return 0;
}