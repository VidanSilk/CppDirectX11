/*
메이즈 스택 구현은 너무 날먹한 것같다
1. 대부분 int쓰는데 굳이 템플릿화 해야할까? -> 여기서 이유 끝
2. 다시 구현 해보자 
*/

#include "stackInfo2.h"

int main(void) {

	myStack<int> myStack;
	myStack.push(1);
	std::cout << myStack.top() << std::endl;
	myStack.push(10);
	myStack.push(20);
	std::cout << myStack.top() << std::endl;
	myStack.push(12);
	myStack.pop();
	myStack.push(22);
	
	std::cout << myStack.top() << std::endl;

	std::stack<int> Teststack; 

	return 0;

}