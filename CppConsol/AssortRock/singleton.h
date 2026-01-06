#pragma once
#ifndef SINGLETON_H
#define	SINGLETON_H
#include <string>
#include <iostream>
#include <iomanip>
class singleton{
private:
	static singleton* instance;
	std::string mPrelog;

	singleton() = default;
	singleton(const singleton& _other) = delete;
	singleton(const singleton&& _other) = delete; //delete를 해주는 이유는 컴파일러가 자동적으로 복사생성자를 만드는 경우가 있기 때문에
	//명시적으로 막을려고 delete를 해주는것일까?
	singleton& operator=(const singleton&) = delete;
	~singleton();
	                                                                                                               
public:
	static singleton* getInstance();
	static singleton& getInstance2();
	void LogPrint(std::string _log);
	void prelogPrint();
};


#endif // !1


