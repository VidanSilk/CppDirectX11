/*
기본 자료형
포인터 자료형
레퍼런스 자료형

사용자 정의 자료형
	struct  구조체
	enum 열거형
	class 클래스

클래스 구성
	내부에 선언되는 변수나 함수 앞에 멤버라고 붙임
	변수 -> 멤버 변수 (데이터)
	함수 -> 멤버 함수 (기능)

클래스 특징 (면접 단골 질문) 
	캡슐화, 상속, 추상화, 다형성

	접근지정자
	public -> 외부에서 접근 가능 (공공재, 모두)
	private -> 외부에서 사용 불가, 클래스 내부에서만 사용 가능 
	protected -> 상속된 클래스 내부에서만 사용 가능 

	클래스는 기본 접근 지정자가 private이고, 구조체는 public:
	
	생성자와 소멸자
	생성자는 객체가 생성되었을때, 자동으로 호출되는 함수
	소멸자는 객체가 소멸될 떄, 자동으로 호출되는 함수 

	멤버함수에서 멤변수로 접근할 떄는 그냥 사용 가능
	클래스 내부에서 사용될 떄 this 라는 키워드가 숨겨져있음


	이름, 나이, 학번, 국 영수,
	평균 합계 한번에 입력 받거나, 각자 입력 받아서 
	해보기
	
	get set 함수를 만들어서 인터페이스를 제공 

	*/


#include "classhaeder.h"

int main(void) {
	//각각의 입력을 받는 학생 1
	StudentInfo student1;
	student1.getName("Jeon");
	student1.setAge(27);
	student1.setID(202509011);
	student1.getSum(50.5, 60.8, 77.7);
	student1.getAverage();
	student1.printStudentInfo();

	cout << endl; 
	cout << endl;
	//한번에 입력을 받는 학생 2 
	StudentInfo student2;
	student2.inputAll(); //이코드를 했을 때 전부 출력하게 하라  
	// 하지만 재사용은 객체지향의 묘미
	cout << endl;
	student2.printStudentInfo();
	return 0;

}