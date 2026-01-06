/*
	정적 변수 
	static 메모리 데이터 영역에 공간을 만들고
	함수 호출시 할당 받고, 프로그램이 종료될 때 메모리 할당
	초기화를 딱 1번만 하고, 값을 지정하지 않으면 0으로 초기화 

	숫자를 입력 받고 숫자가 큰지 작은지 알려주기 
	조건
	변수들은 전역 변수
	함수로 입출력(?)
	메인에서 함수 하나만 호출해서 게임을 시작되게 만든다 
	*/

#include <iostream>
#include <random>
#include <time.h>
using namespace std;

//전역 변수 선언 
int playerSelcetNum = 0;
int RandomNum = 0;
int tryCount = 0;
// 함수 선언 
void playGame(); // 게임을 플레이 하는 함수
void print_gameResult(); //게임 결과를 출력 하는 함수 

//Main Func
int main(void) {
	
	cout << "----------게임을 시작 하겠습니다!-------------------------- \n";
	srand((unsigned int)time(0));
	RandomNum = rand() % 100 + 1;
	cout << "Test_RandomNum 정답지 : " << RandomNum << endl << endl;

	//게임 플레이 (함수 호출)
	playGame();
	return 0;
}

//게임을 플레이하는 함수 (게임 로직)
void playGame() {

	cout << "숫자를 입력 해주세요 : ";
	cin >> playerSelcetNum;

	while (1) {

		if (playerSelcetNum < 0 || playerSelcetNum > 100) {
			tryCount++;
			cout << "0~100사이 숫자를 다시 입력해주세요 " << endl;
			return playGame();
		}
		else if (playerSelcetNum > RandomNum) {
			tryCount++;
			cout << "Down! " << endl;
			return playGame();
		}
		else if (playerSelcetNum < RandomNum) {
			tryCount++;
			cout << "UP!" << endl;
			return playGame();
		}
		else {
			tryCount++;
			cout << "정답! " << endl;
			break;
		}
	}
	//게임 결과 출력 함수 호출
	print_gameResult();
}

// 게임 결과를 알려주는 함수 
void print_gameResult() {
	cout << endl;
	cout << "시도한 횟수 : " << tryCount << endl;
	cout << "정답 숫자 : " << RandomNum << endl;

}