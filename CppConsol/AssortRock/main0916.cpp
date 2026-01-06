#include<iostream>
#include "singleton.h"
#include "dog.h"
using namespace std;
//
//
//namespace Tuesday {
//	int g_num;
//	void F() {
//		cout << "09-16 화요일.... 피곤" << endl;
//	}
//
//}
//
//void F() {
//	cout << "너는 누구니?" << endl;
//
//}
//
//int F(int a, int b) {
//	cout << "계산 \n";
//	return a + b;
//}
//
//enum class Week {
//	Mon, Tues, Wen, Tus, Fir, Shu, Sun
//
//};
//
//class printLib {
//private:
//	string name;
//	static int staticNum;
//public:
//	void print() { 
//		this->name = "Vidan";
//		cout << "객체의 print\n"; }
//
//	static void myStaticPrint() {
//		cout << "나는 printLib의 클래스 myStaticPrint 객체 입니다 " << endl;
//	}
//	/*
//		static 멤버 함수 
//		-> 클래스 객체에 종속되지 않고 호출할 수 있는 함수 
//		객체에 귀속 되지않음 (this가 없어
//		고유의 멤버 변수에 접근 불가)
//		즉, this -> name;
//		this->print();가 불가
//		대신 스테틱 변수는 가능 근데 외부에 알려줘야함 
//		그리고 메인함수에 하면 복잡해지니깐 
//		객체지향을 특징을 잘 이용해서 분리해서 선언하자 
//		GoF에서 자주 쓰인다
//	*/
//};

int main(void) {
	//int a = F(10, 2);
	//cout << a << endl;
	//F();
	//Tuesday::g_num = 10;
	//Tuesday::F();
	//Week::Mon;
	//printLib b; 
	//b.print();
	//b.myStaticPrint();
	//
	singleton* sigle1 = singleton::getInstance();
	singleton* sigle2 = singleton::getInstance();
	cout << "sigle1의 가리키는 주소" << sigle1 << endl;
	cout << "sigle2의 가리키는 주소" << sigle2 << endl;

	singleton& sigle3 = singleton::getInstance2();
	singleton& sigle4 = singleton::getInstance2();
	cout << "sigle3의 가리키는 주소" << &sigle3 << endl;
	cout << "sigle4의 가리키는 주소" << &sigle4 << endl;

	sigle1->LogPrint("1st log ");
	sigle1->LogPrint("2nd log ");
	sigle2->prelogPrint();
	dog dog; 
	dog.moung();
	sigle1->prelogPrint();
	return 0;
}