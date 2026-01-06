/*
	이름, 나이, 학번, 국 영수,
	평균 합계 한번에 입력 받거나, 각자 입력 받아서
	해보기

	get set 함수를 만들어서 인터페이스를 제공
*/
#pragma once
#ifndef CLASSHAEDER_H
#define CLASSHADER_H

#include <iostream>
#include <string>

using namespace std;

class StudentInfo {

private:
	string mName; //이름 
	int mAge; //나이
 	int mId; //학번
	
	// 시험 점수 
	float mKor, mEng, mMath;
	float mAverage, mSum;

public:
	StudentInfo();
	~StudentInfo();
	//이름 멤버 함수 
	string getName(string _nm);
	//나이에대한 멤버함수
	void setAge(int _age);
	//학번 멤버 함수
	int getId();
	void setID(int _id);
	//시험점수 멤버 함수 
	void getSum(float _kor, float _eng, float _math);
	void getAverage();
	void printStudentInfo() const;
	void inputAll();
};

#endif // !CLASSHAEDER_H
