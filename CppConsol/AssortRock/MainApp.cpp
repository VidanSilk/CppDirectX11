#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;

int main(void) { 
	
	// 베이스 볼 게임
	// 1. 랜덤한 숫자 3개를 만들기 
	// 2. 각각의 숫자는 1~9사이의 숫자고, 중복X
	// 3. 숫자를 맞추면 볼, 숫자의 위치도 같이 맞추면 스트라이크
	// 4. 숫자가 하나도 안 맞으면 아웃
	// 5. 스트라이크가 3개면 삼진 아웃으로 게임을 종료

	srand((unsigned int)time(0));
	
	int randomNum[3] = { }; //맞춰야 할 숫자 모음
	int playerNum[3] = { }; //플레이어가 맞춰야할 숫자 모음 

	// 1. 랜덤한 숫자 3개 이것도 (범위가 1~9까지), 중복수는 없어야함 
		
		for (int i = 0; i < 3; i++) {
				randomNum[i] = (rand() % 9) + 1;
			//중복검사 
				for (int j = 0; j < i; j++) {
					if (randomNum[i] == randomNum[j]) {
						i--;
						break;
					}
				}
		}
		//테스트용
		cout << "생성한 랜덤 값이 저장되었는지 확인 : " << randomNum[0] << ", " << randomNum[1] << ", " << randomNum[2] << endl << endl;

	// 맞출 때 까지 반복 
	// 2. 각각의 숫자는 1~9사이의 숫자고, 중복X  -> 입력 2 1 3
	int strike = 0, ball = 0, out = 0;
	int total = 0; // 시도한 횟수
	
	while (1) {
		cout << "숫자를 입력 합니다 (1~9, 중복 제외) : ";
		for (int i = 0; i < 3; i++) {
			cin >> playerNum[i];
		}
		cout << "입력한 숫자는 " << playerNum[0] << ","
			<< playerNum[1] << "," << playerNum[2] << "입니다 \n";

		//조건문으로 게임 규칙 만들어 보기 
		// 3. 숫자를 맞추면 볼, 숫자의 위치도 같이 맞추면 스트라이크
		// 4. 숫자가 하나도 안 맞으면 아웃
		// 5. 스트라이크가 3스트르아크면 아웃으로 게임을 종료 (구현)
		//게임 시작 
		strike = 0;
		ball = 0; 

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//스트라이크, 스트라이크는 인덱스(위치)와 데이터(값)이 같아야 한다.
				if (playerNum[i] == randomNum[j]) {
					if (i == j) {
						strike++;
					}//볼, 볼은 인덱스 위치가 달라도, 데이터가 같으면 볼이다.
					else {
						ball++;
					}
				}
				
			}
		}
		//out 둘 다 아닌 경우
		if (strike == 0 && ball == 0) {
			out++;
		}
		cout << "스트라이크 개수 : " << strike << " 볼 개수 : " << ball << endl;

		//스트라이크가 3개면 게임 종료
		if (strike == 3) {
			cout << "스트라이크 3개로 게임 오버입니다 \n";
			cout << " 총 시도한 횟수 : " << total << endl;
			cout << "아웃 개수 : " << out << endl;
			return 0; 
		}
		else {
			total++;
		}
	}
	
	return 0;
}




/***************************************************************

# 랜덤한 정수 가져오기 
srand() 패턴 시드를 설정
rand() 랜덤한 정수를 가지고 옴 

# 배열 array
같은 자료형으로 선언된 연속된 메모리를 가진 공간
int 변수명[인덱스]
	// 1. input에 문자열 이름 입력 받고
	char input[15] = {'J','e', 'o', 'n',
					'Y','u',
					'S','u','n','g','\0'};

	std::cout << " input으로 이름 받은 영어 이름 : " << input << std::endl;

	// 2. name을 선언하여, for문으로 하나씩 복사
	// 3. for의 조건은 접근한 인덱스가 '\0'이 아닌 경우까지
	char name[15] = {} ;//초기화를 안하면 덤프 값이 발생

	for (int i = 0; !input[i] == '\0'; i++) {
		name[i] = input[i];
		std::cout << " 복사한 name [" << i << "]의 값은 "
			<< name[i] << std::endl;
	}
	std::cout << "for으로 이름 받은 name : " << name << std::endl;
	return 0;

-------------------------------------------------
오전 실습 문제 
조건1 while문으로 원할때 까지 반복
점수를 입력하면 학점을 출력하는 프로그램 

이름 입력 받아서 배열에 
 코드 내용 
	float score;
	//점수를 입력
	cout << "점수를 입력하세요 : ";

	//while문과 if문 사용
	while (cin >> score) {
		if (score >= 90 && score <= 100) {
			cout << "gpa : a,  원 점수 : " << score << endl;
			break;
		}
		else if (score >= 80 && score < 90) {
			cout << " gpa : b,  원 점수 : " << score << endl;
			break;
		}
		else if (score >= 70 && score < 80) {
			cout << " gpa: c,  원 점수 : " << score << endl;
			break;
		}
		else if (score >= 60 && score < 70 ) {
			cout << " gpa : d,  원 점수 : " << score << endl;
			break;
		}
		else if (score >= 0 && score < 60) {
			cout << " gpa : f,  원 점수 : " << score << endl;
			break;

		}
		else if (score == -99) {
			cout << "프로그램 종료 \n";
			return 0;
		}
		else {
			cout << "잘못된 입력 입니다. 다시 0~100 사이를 입력하세요 \n";
		}
	}

	//스위치 문 사용
	int gpaScore;
	char gpa;

	cout << "점수를 입력 하세요 : ";
	while (cin >> gpaScore) {

		if (gpaScore == -99) {
			cout << "프로그램을 종료하겠습니다 \n";
			return 0;
		}
		else if (gpaScore < 0 || gpaScore > 100) {
			cout << "0~100사이의 값을 다시 입력하세요 \n";
			continue;
		}

			switch (gpaScore / 10) {
			case 10: case 9:
				gpa = 'A';
				break;
			case 8:
				gpa = 'B';
				break;
			case 7:
				gpa = 'C';
				break;
			case 6:
				gpa = 'D';
				break;
			default:
				gpa = 'F';
				break;
			}
		cout << "학점은 " << gpa << ", 원점수는 " << gpaScore << " 입니다" << endl;
		break;
	}

		// 베이스 볼 게임
	// 1. 랜덤한 숫자 3개를 만들기
	// 2. 각각의 숫자는 1~9사이의 숫자고, 중복X
	// 3. 숫자를 맞추면 볼, 숫자의 위치도 같이 맞추면 스트라이크
	// 4. 숫자가 하나도 안 맞으면 아웃
	// 5. 스트라이크가 3개면 삼진 아웃으로 게임을 종료

	srand((unsigned int)time(0));

	int randomNum[3] = { }; //맞춰야 할 숫자 모음
	int playerNum[3] = { }; //플레이어가 맞춰야할 숫자 모음

	// 1. 랜덤한 숫자 3개 이것도 (범위가 1~9까지), 중복수는 없어야함

		for (int i = 0; i < 3; i++) {
				randomNum[i] = (rand() % 9) + 1;
			//중복검사
				for (int j = 0; j < i; j++) {
					if (randomNum[i] == randomNum[j]) {
						i--;
						break;
					}
				}
		}
		//테스트용
		cout << "생성한 랜덤 값이 저장되었는지 확인 : " << randomNum[0] << ", " << randomNum[1] << ", " << randomNum[2] << endl << endl;

	// 맞출 때 까지 반복
	// 2. 각각의 숫자는 1~9사이의 숫자고, 중복X  -> 입력 2 1 3
	int strike = 0, ball = 0, out = 0;
	int total = 0; // 시도한 횟수

	while (1) {
		cout << "숫자를 입력 합니다 (1~9, 중복 제외) : ";
		for (int i = 0; i < 3; i++) {
			cin >> playerNum[i];
		}
		cout << "입력한 숫자는 " << playerNum[0] << ","
			<< playerNum[1] << "," << playerNum[2] << "입니다 \n";

		//조건문으로 게임 규칙 만들어 보기
		// 3. 숫자를 맞추면 볼, 숫자의 위치도 같이 맞추면 스트라이크
		// 4. 숫자가 하나도 안 맞으면 아웃
		// 5. 스트라이크가 3스트르아크면 아웃으로 게임을 종료 (구현)
		//게임 시작
		strike = 0;
		ball = 0;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				//스트라이크, 스트라이크는 인덱스(위치)와 데이터(값)이 같아야 한다.
				if (playerNum[i] == randomNum[j]) {
					if (i == j) {
						strike++;

					}//볼, 볼은 인덱스 위치가 달라도, 데이터가 같으면 볼이다.
					else {
						ball++;
					}
				}

			}
		}
		//out 둘 다 아닌 경우
		if (strike == 0 && ball == 0) {
			out++;
		}
		cout << "스트라이크 개수 : " << strike << " 볼 개수 : " << ball << endl;

		//스트라이크가 3개면 게임 종료
		if (strike == 3) {
			cout << "스트라이크 3개로 게임 오버입니다 \n";
			cout << " 총 시도한 횟수 : " << total << endl;
			cout << "아웃 개수 : " << out << endl;
			return 0;
		}
		else {
			total++;
		}
	}

	*/
