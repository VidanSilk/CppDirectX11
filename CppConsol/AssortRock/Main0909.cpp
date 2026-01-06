/*
	시간 남으면 해보기 피보나치 수열 → 1 1 2 3 5 8 13 21.....

int Fibonachi(int n) {

	if (n <= 1) return 1;

	return Fibonachi(n - 2 ) + Fibonachi(n - 1);

}

 실습 전역변수 와 함수 이용
 calcuate 함수 : 전역변수로 사칙 연산 결과 받기
 resultprint 함수 사칙연산 결과 출력하기
*/
#include <iostream>

using namespace std;

//함수 선언
int calculate(int n1, int n2);
void resultPrint();

//전역 변수 선언
int globalAdd = 0;
int globalMirus = 0;
int globalDiv = 0;
int globalMulti = 0;

//Main Func
int main(void) {
	int inputNum1, inputNum2;
	cout << "정수를 입력 하세요 : ";
	cin >> inputNum1 >> inputNum2;
	
	//사칙연산 함수 호출 
	calculate(inputNum1, inputNum2);
	//계산결과 함수 호출
	resultPrint();
	return 0;
}

//사칙 연산 함수 구현 
// 버그(예외 처리) -> 1. n1이 0일 땐 예외처리 제대로함 n2가 0일 떈 예외처리 -> 위치 때문 try부터 시도해서 해결
// 2. 곱하기도 2 * 0 or 0 * 2하면 0을 출력해야함 출력문에서 잡음 

int calculate(int n1, int n2) {
	
	char symbol; 
	cout << "사칙연산 부호를 입력하세요 : ";
	cin >> symbol;

	switch (symbol) {
	case '+':
		globalAdd = n1 + n2;
		return globalAdd;
		break;
	case '-':
		globalMirus = n1 - n2;
		return 	globalMirus;
		break;
	
	case '/':
		try {
			if(n1 == 0 || n2 == 0)
				throw runtime_error(" \n Division by zero is not allowed.");
		}
		catch (const exception& e) {
			cout << "나누기는 0으로 나눌 수 없습니다. " << e.what() << endl;
		}
		globalDiv = n1 / n2;
		return globalDiv;
		break; 

	case '*' :
		globalMulti = n1 * n2;
		return globalMulti;
		break;

	default:
		break;
	}

}
void resultPrint() {
	
	if (globalAdd) {
		cout << "더하기 값은 : " << globalAdd << endl;
	}
	else if (globalMirus) {
		cout << "빼기 값 : " << globalMirus << endl;
	}
	else if (globalDiv) {

		cout << "나누기 값은 : " << globalDiv << endl;
	}
	else if (globalMulti != 0) {
		cout << "곱하기 값은 : " << globalMulti << endl;
	}
	if (globalMulti == 0) {
		cout << "0을 곱한 값은 : " << globalMulti << endl;
	}
}