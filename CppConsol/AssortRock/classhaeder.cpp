//classhaeder파일 구현
#include "classhaeder.h"

StudentInfo::StudentInfo() : mName(), mAge(0),mId (0),
 mKor(0),mEng(0), mMath(0),
 mAverage(0), mSum(0) 
{}

StudentInfo::~StudentInfo(){}

string StudentInfo::getName(string _nm) {
	mName = _nm;
	return mName;
}
void StudentInfo::setAge(int _age)
{
	mAge = _age;
}
//학번 멤버 함수
int StudentInfo::getId() {
	return mId;
}
void StudentInfo::setID(int _id) {
	mId = _id;
	getId();
}
//시험점수 멤버 함수 
void StudentInfo::getSum(float _kor, float _eng, float _math){
	
	mKor = _kor;
	mEng = _eng;
	mMath = _math;

	mSum = mKor + mEng + mMath;

}
void StudentInfo::getAverage() {
	mAverage = (mSum / 3);
}
void StudentInfo::printStudentInfo() const {
	cout << "학생의 정보 출력 \n";
	cout << "학생 이름 : " << mName << endl;
	cout << "학생 학번 : " << mId << endl;
	cout << "학생 나이 : " << mAge << "살" << endl;
	cout << "국어 점수 : " << mKor << " 수학 점수 : " << mMath << " 영어 점수 : " << mEng << endl;
	cout << "합계 : " << mSum << " 평균 : " << mAverage << endl;
}

//한방에 다 받는 함수 작성하기 
void  StudentInfo::inputAll() {

	cout << " 학생 정보 입력하세요 \n";
	cout << " 학생 이름 입력 : ";
	cin >> mName;
	cout << " 학생 나이 입력 : ";
	cin >> mAge;	
	cout << " 학생 학번 입력 : ";
	cin >> mId;

	cout << " 학생 시험 점수 입력 (국 영 수로 순서대로 입력하세요): ";
	cin >> mKor >> mEng >> mMath;

	mSum = mKor + mEng + mMath;
	mAverage = (mSum / 3);
	
}