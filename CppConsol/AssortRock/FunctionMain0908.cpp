/*
	함수란
	기능을 묵는것 즉, 구현되어 있는 기능을 동작시키고결과를 얻는다 

*/

#include <iostream>
#include <string>

using namespace std;

void printfvoid() {
	cout << "hello wolrd\n";
}

int printfint() {
	cout << "Hello world2\n";
	return 0; 
}

int main(int argc, char* argv[]) {

	printfvoid();
	printfint();
	return 0;
}

