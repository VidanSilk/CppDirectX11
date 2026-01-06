/*
	템플릿 (제네릭 프로그래밍)
	함수를 하나만 작성해도 여러 자료형에 적용되는 함수를 여러 개를 자동으로 만들 수 있음
	Template Programming를 하지 않는다면, 여러 개의 함수를 정의 해야함
	그럼 코드의 유지보수나 가독성이 떨어짐
	클래스도 템플릿 가능 
*/
#include <iostream>
#include <vector>

using namespace std; 
template<typename T>
T add(T _n2, T _n3) {
	return _n2 + _n3;
}
template<typename T>
T mirus(T _n2, T _n3) {
	return _n2 - _n3;
}

template<typename T1, typename T2>
T1 Multfunc(T1 _n1, T2 _n2) {
	T1 result;
	result = _n1 * _n2;
	return result;
}

template<typename T1, typename T2>
T1 Divfunc(T1 _n1, T2 _n2) {
	T1 result;
	result = _n1 / _n2;
	return result;
}


template<typename T>
class numbers {
public: 
	std::vector <T> arr;
	T mData;

	T addFunc(T _a, T _b) {
		return _a + _b;
	}

};



int main(void) {


	cout << add<int>(10, 20) << endl;
	cout << mirus(30, 6) << endl;
	cout << Multfunc(10.2, 20.4f) << endl;
	cout << Divfunc<char, int>('z', 2) << endl;


}