#include "myList.h"
#include <list>

using namespace std;
int main(void) {
  
	//Test
	myList<int> test;
	test.push_back(100);
	test.push_back(200);
	test.push_back(400);
	test.push_back(300);
	test.push_front(1);
	test.push_front(2);
	test.push_front(3);


	cout << "리스트 크기 확인 : " << test.size();
	cout << endl; 
	test.pop_back();
	cout << "리스트 크기 확인 : " << test.size() << endl;	
	test.pop_front();
	cout << "리스트 크기 확인 : " << test.size() << endl;
	test.pop_front();
	cout << "리스트 크기 확인 : " << test.size() << endl;
	myList<int>::iterator iter = test.begin();
	++iter;
	--iter;
	iter--;
	std::cout << *iter << std::endl;

	iter = test.begin();
	++iter;
	++iter;
	iter = test.insert(iter, 10);

	test.erase(iter);

	//iter++;
	cout << "리스트 요소(원소) 확인 : \n";
	test.printList();

	return 0; 
}

