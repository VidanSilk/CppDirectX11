/*
	함수란
	기능을 묵는것 즉, 구현되어 있는 기능을 동작시키고 결과를 얻는다

	매개변수(Prarameter)
	함수에 data를 전달하고 싶을 때 사용
*/

// 실습 
// 구조체 이용, 함수 하나만 사용
#include <iostream>
#include <string>

using namespace std;

struct Numbers
{
	int n1 = 0, n2 = 0;
	int sum = 0;
	int mirus = 0;
	int multipul = 0;
	int divNum = 0;

}; 

struct Numbers Computing(int num1, int num2) {
	Numbers Results;

	Results.sum = num1 + num2;
	Results.mirus = num1 - num2;
	Results.multipul = num1 * num2;
	Results.divNum = num1 / num2;
	try
	{
		if (num1 == 0 || num2 == 0) {
			throw runtime_error(" \n Division by zero is not allowed.");
		}

	}
	catch (const std::exception& e)
	{
		cout << "나누기는 0으로 나눌 수 없습니다. " << e.what() << endl;
	}
	cout << "더하기 : " << Results.sum << endl;
	cout << "빼기 : " << Results.mirus << endl;
	cout << "곱하기 : " << Results.multipul << endl;
	cout << "나누기 : " << Results.divNum << endl;
	
	return Results;
};

//함수 선언 
//int plusFunc(int num1, int num2);
//int mirusFunc(int num1, int num2);
//int multiFunc(int num1, int num2);
//int divFunc(int num1, int num2);


//메인
int main(void) {

	////간단한 사칙 연산
	//int n1, n2;
	//cout << "정수 숫자를 입
	// 력하세요 : ";
	//cin >> n1 >> n2;
	//plusFunc(n1, n2);
	//mirusFunc(n1, n2);
	//cout << "곱하기 : " << multiFunc(n1, n2) << "입니다 \n"; 
	//cout << "나누기 : " << divFunc(n1, n2) << "입니다 \n";
	Numbers one;
	cout << "정수를 입력 하세요 : ";
	cin >> one.n1 >> one.n2;

	Computing(one.n1, one.n2);

	return 0;
}

////함수 구현
//int plusFunc(int num1, int num2) {
//	int sum = 0;
//	sum = num1 + num2;
//	cout << "더하기 : " << sum << "입니다 \n";
//	return sum;
//}
//int mirusFunc(int num1, int num2) {
//	int mirusNum = 0; 
//	mirusNum = num1 - num2;
//	cout << "빼기 : " << mirusNum << "입니다 \n";
//	return mirusNum;
//}
//int multiFunc(int num1, int num2) {
//	return num1 * num2;
//}
//
//int divFunc(int num1, int num2) {
//	//예외 처리 하자
//	try
//	{
//		if (num1 == 0 || num2 == 0) {
//			throw runtime_error(" \n Division by zero is not allowed.");
//		}
//		
//	}
//	catch (const std::exception& e)
//	{
//		cout << "나누기는 0으로 나눌 수 없습니다. " << e.what() << endl;
//	}
//	return num1/ num2;
//}
