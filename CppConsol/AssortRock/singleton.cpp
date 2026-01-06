#include "singleton.h"

//정적멤버 선언시 초기화는 필수 
singleton* singleton :: instance = nullptr;


singleton::~singleton(){
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

//힙 영역에 메모리 영역 올렸기 때문에 해제가 필수  
singleton* singleton::getInstance() {
	if (instance == nullptr) {
		instance = new singleton(); //동적 할당해서 사용하는 방식
	}
	return instance;
}

//마이어스 싱글톤, 해제를 안함 
singleton& singleton::getInstance2() {
	static singleton Instance; //정적 지역 변수를 사용하는 방식 
	return Instance;
	// TODO: 여기에 return 문을 삽입합니다.
}

void singleton::LogPrint(std::string _log)
{
	mPrelog = _log;
	std::cout << mPrelog << std::endl;

}

void singleton::prelogPrint()
{
	std::cout << mPrelog << std::endl;
}
