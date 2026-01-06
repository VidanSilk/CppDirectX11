#include <iostream>

using namespace std;
//팩토리얼 재귀 함수를 이용해서 구현

int Factorial(int n) {

	if (n == 0) return 1;

	return n * Factorial(n - 1);
	
}

int main(void) {
	int num;
	cout << "숫자를 입력하세요 : ";
	cin >> num;
	cout << num << "! 의 값은 " << Factorial(num) << "입니다 \n";

	return 0;
} 