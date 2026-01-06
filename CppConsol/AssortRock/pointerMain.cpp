/*
	포인터
	메모리를 저장하는 변수
	다른 변수나 객체의 주소를 들고 있는 변수 
	
	& 주소를 알려줌
	&a -> a의 주소를 알려줌 
	
	* 
	포인터가 가리키는 주소의 값을 가져온다.

	포인터 배열
	a[] {};
	
	배열 데이터 접근할 때 사용자는 []
	둘다 같은 의미 
	a[0]; == *(a+0);
	a[1] == *(a+1);
*/

#include<iostream>
#include <string>

using namespace std;

void setArray(int* arr, int size);
void printarr(int arr[], int size);

//Main Func
int main(void) {
	const int ArraySize = 5;
	int numArr[ArraySize] = {};

	setArray(numArr, ArraySize);
	printarr(numArr, ArraySize);
	cout << endl;

	return 0;
}


void setArray(int* arr, int size) {
	for (int i = 0; i < size; i++) {
		*(arr + i) = i;

	}
}


void printarr(int arr[], int size) {

	for (int i = 0; i < size; i++)
	{
		cout << *(arr + i) << ' ';
	}
}