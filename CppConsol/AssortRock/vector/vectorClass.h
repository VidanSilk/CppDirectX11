#pragma once
#include <iostream>
#include <vector>
//인스턴스화 때문에 템플릿은 헤더에 
//.이동생성자는 주소값을 넘기기떄문에  &&해줘야함 
//이동 생성자 완료 후 기존의 데이터를 초기화해줘야한다.
//capacity 성질 -> 늘리는건 되는데 줄이는건 불가능하다. 

template<typename T>
class vectorClass {
private:
	//벡터 선언 
	std::vector<T> Vec;
public:
	vectorClass() : Vec() {}
	~vectorClass() {}
	void Input(); //벡터에 값을 채운다. 
	void vecSearch(); //벡터 탐색 
	void RvecSearch(); //역으로 벡터 탐색 후 출력 
	void VecOutPut(); //벡터 값 출력 
	void vecResize(); //벡터 재정의후 출력 
	//또 구현할 게 뭐가 있을까?

};


template<typename T>
void vectorClass<T>::Input()
{
	for (int i = 0; i < 10; i++) {
		Vec.push_back( i * 10);
	}
	std::cout << "벡터 맨앞 : " << Vec.front() << std::endl;
	std::cout << "벡터 맨앞 : " << Vec.back() << std::endl;
	std::cout << "at 사용해서 7번째 원소에 접근 : " << Vec.at(7) << std::endl;
	std::cout << std::endl;

}

template<typename T>
void vectorClass<T>::vecSearch()
{
	typename std::vector<T>::iterator iter;

	std::cout << "정방향 탐색: ";
	for (iter = Vec.begin(); iter != Vec.end(); ++iter) {
		std::cout << *iter << " ";
	}
	std::cout << std::endl;
;

}

template<typename T>
void vectorClass<T>::RvecSearch()
{
	typename std::vector<T>::reverse_iterator rIter;
	std::cout << "역방향 탐색: ";
	for (rIter = Vec.rbegin(); rIter != Vec.rend(); ++rIter) {
		std::cout << *rIter << " ";
	}
	std::cout << std::endl;

}

template<typename T>
void vectorClass<T>::VecOutPut()
{
	std::cout << "벡터 값 출력: ";
	for (const auto& val : Vec) {
		std::cout << val << " ";
	}

	std::cout << "\n";
	std::cout << "벡터 사이즈 : " << Vec.size() << std::endl;
	std::cout << "capacity : " << Vec.capacity() << std::endl; //왜 13이 나왔지? 
	std::cout << std::endl;
}

template<typename T>
inline void vectorClass<T>::vecResize()
{	
	Vec.clear(); //000000으로 초기화 근데 리사이즈 해도 왜 5개가 아니라 10개가 남을까? 
	Vec.resize(5);
	Vec.reserve(5); //리사이즈와 리저브의 개념에 차이에 대해 숙지하자 
	//벡터 입력 
	Vec.push_back('A');
	Vec.push_back('B');
	Vec.push_back('C');
	Vec.push_back('D');
	Vec.push_back('E');


	std::cout << "\n";
	std::cout << "벡터 문자 맨앞 : " << Vec.front() << std::endl;
	std::cout << "벡터 문자 맨앞 : " << Vec.back() << std::endl;
	std::cout << "at 사용해서 문자 2번째 원소에 접근 : " << Vec.at(2) << std::endl;

}

