/*
 구조체로 이름, 학번 국어 영어 수학 점수 받아
 총점,평균 계산하기.

 로직
 1. 구조체 선언 
 이름 학번 시험점수
 2. 구조체 함수로 입출력 ()?
*/

#include <iostream>
#include <string>

using namespace std;
//구조체 선언
struct Students {
	string Sname;
	int ID = 0;
	float kor = 0, eng = 0, math = 0;
	float sum = 0, average = 0;

}student;

//학생 정보 입력 
struct Students studentInput() {
	
	cout << " 학생의 이름 입력 : ";
	cin >> student.Sname;
	cout << " 학생의 학번 입력 : ";
	cin >> student.ID;
	cout << endl;
	return student;

};

//시험 점수 합산 및 평균
struct Students studentExamInfo() {

	cout << " 학생의 국어 시험 점수 입력 : ";
	cin >> student.kor;
	cout << " 학생의 수학 시험 점수 입력 : ";
	cin >> student.math;
	cout << " 학생의 영어 시험 점수 입력 : ";
	cin >> student.eng;
	cout << endl;

	//점수 합산 
	student.sum = student.kor + student.math + student.eng;
	student.average = student.sum / 3.f;
	return student;

};

//학생 정보 출력 
struct Students studentPrint(){

	cout << "학생의 학생 이름 : " << student.Sname << endl;
	cout << "학생의 학번 : " << student.ID << endl;
	cout << "학생의 총 점수 : " << student.sum << endl;
	cout << "학생의 평균 : " << student.average << endl;
	return student;
};

//메인 함수
int main(void) {

	Students S1, S2, S3, per[3];
	S1 = studentInput();
	S1 = studentExamInfo();
	S1 = studentPrint();
	cout << endl; 
	
	S2 = studentInput();
	S2 = studentExamInfo();
	S2 = studentPrint();
	cout << endl;
	
	S3 = studentInput();
	S3 = studentExamInfo();
	S3 = studentPrint();
	cout << endl; 

	for (int i = 0; i < 3; i++) {
	
		per[i] = studentInput();
		per[i] = studentExamInfo();
		per[i] = studentPrint();
	}

	return 0;
}