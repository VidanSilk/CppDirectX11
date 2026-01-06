/*
	구조체(struct) → 여러 종류의 데이터를 하나로 묶은 집합체
	std::cin.ignore(1000, '\n'); 입력 버퍼를 지워준다. 
	바이트 패딩을 하기 때문에 
	구조체의 크기는 사람이 생각하는 크기랑 다를 수 있음
	선언시 크기가 큰 자료형부터 작은 자료형 순서대로 선언하는게 좋음 
*/

#include <iostream>
#include <string>
using namespace std; 

// 아침 실습 
//학생 정보 만들어 보기 (이름, 학번, 국어, 영어, 수학, 점수 합계 및 평균)
// 배열로 3명정도 for문으로 받아 입출력 
struct PID_STUDENT {

public:
	int Sid = 0; //4 
	float korea = 0, english = 0, math = 0; // 12
	float examSum = 0, average = 0; // 8
	string Sname; // 1 

};


int main(void){
	
	PID_STUDENT Student1;
	cout << "사이즈 : " << sizeof(PID_STUDENT) << endl;
	cout << "학생1의 이름을 입력하세요 : ";
	cin >> Student1.Sname;
	cout << "학생1의 학번을 입력하세요 : (int) ";
	cin >> Student1.Sid;
	cout << "학생1의 국어, 수학, 영어 점수를 입력 하세요 : ";
	cin >> Student1.korea >> Student1.math >> Student1.english;

	
	//학생의 점수 합계
	cout << "학생 1의 국어 점수는 : " << Student1.korea << " 점, 수학 점수 : " << Student1.math << " 점, 영어 점수 : " << Student1.english << "점 \n";
	Student1.examSum = Student1.korea + Student1.math + Student1.english;
	cout << "학생1의 점수 합계는 : " << Student1.examSum << " 점 \n";

	//학생1의 평균 
	Student1.average = Student1.examSum / 3;
	cout << "학생1의 점수 합계는 : " << Student1.average << " 점 \n";

	cout << endl << endl; 

	//for문을 이용한 학생 출력
	PID_STUDENT Students[3];

	//학생 정보 입력 : 
	cout << "학생들의 이름 입력하세요 : ";
	for (int i = 0; i < 3; i++) {
		cin >> Students[i].Sname;
		cout << "학생들의 이름은 " << Students[i].Sname << " 입니다 \n";
	}

	cout << endl; 

	cout << "학생들의 ID 입력하세요 : ";
	for (int i = 0; i < 3; i++) {
		cin >> Students[i].Sid;
		cout << Students[i].Sname << "의 id는 " << Students[i].Sid << " 입니다 \n";
	}
	cout << endl;

	cout << "학생들의 국어 점수 입력하세요 : ";
	for (int i = 0; i < 3; i++) {
		cin >> Students[i].korea;
	}
	cout << endl;

	cout << "학생들의 영어 점수 입력하세요 : ";
	for (int i = 0; i < 3; i++) {
		cin >> Students[i].english;
	}
	cout << endl;

	cout << "학생들의 수학 점수 입력하세요 : ";
	for (int i = 0; i < 3; i++) {
		cin >> Students[i].math;
	}
	cout << endl;
	
	
	cout << "학생들의 점수 합계는  " << endl;
	for (int i = 0; i < 3; i++) {
		Students[i].examSum = Students[i].korea + Students[i].english + Students[i].math;
		cout << "학생 " << Students[i].Sname <<"의 점수는 " << Students[i].examSum << "점 입니다 \n";
	}
	cout << endl;

	cout << "학생들의 시험 점수 평균은 " << endl;
	for (int i = 0; i < 3; i++) {
		Students[i].average = (Students[i].examSum / 3);
		cout << "학생 " << Students[i].Sname << "의 평균 " << Students[i].average << "점 입니다 \n";
	}

	return 0;

}
