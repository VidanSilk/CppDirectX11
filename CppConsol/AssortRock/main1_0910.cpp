/*
	int n =10;
	int n2 = 11;

	const int* ptrNum = *&number;
	-> 자료형 앞에 붙으면 주소안의 데이터를 변경할 수 없다. 즉, 주소가 가르키는 데이터를 변경할 수 없다.  
	*ptrNum = 10; -> 에러
	 
	const 뒤, 가리키는 주소 값은 변경 가능  
	선언과 동시에 초기화 해야함 
	int* const ptrN = &number;

	*ptrN = 100; 
	
	//cpc : 무조건 n만 관찰할 거다 
	const int* const cpcNum = n;

	실습 
	레퍼런스 이용해서 사칙 연산 할 것 
	매개 변수로 래퍼런스 받고, 첫번째 래퍼런스로 출력할 것
	출력 바로 해주기 
*/
#include <iostream>
using namespace std;

//사칙 함수 연산 선언

void add(int& _number1, int& _number2);
void mirus(int& _number1, int& _number2);
void divition(int& _number1, int& _number2);
void multiple(int& _number1, int& _number2);

int main(void){
	
	int num1, num2;
	char calculate;
	
	cout << "정수를 입력하세요 : ";
	cin >> num1 >> num2;

	int& n1 = num1;
	int& n2 = num2;

	cout << "계산할 사칙 연산 부호를 입력 하세요 : ";
	cin >> calculate;
	switch (calculate)
	{
	case '+':
		add(n1,n2);
		cout << "add : " << n1 << endl;
		break;
	case '-':
		mirus(n1, n2);
		cout << "mirus : " << n1 << endl;
		break;
	case '/':
		if (n1 == 0 || n2 == 0) {
			cout << "0으로 나눌수 없습니다 \n";
		}
		else {
			divition(n1, n2);
			cout << "Divition : " << n1 << endl;
		} break;
	case '*':
		multiple(n1, n2);
		cout << "Multiple : " << n1 << endl;
		break;
	default:
		break;
	}
	return 0;
}

void add(int& _number1, int& _number2) {
	_number1 += _number2;
}

void mirus(int& _number1, int& _number2) {
	_number1 -= _number2;
}
void divition(int& _number1, int& _number2) {
		_number1 /= _number2; 
}

void  multiple(int& _number1, int& _number2) {
	_number1 *= _number2;
}
