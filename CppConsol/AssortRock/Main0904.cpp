//실습 짝수 맞추기
// 1~10까지 숫자 2개씩 존재
// 숫자를 골고루 섞어 10* 2로 출력 
// 사용자는 인덱스 2개를 입력해서, 값이 같으면 해당 부분은 숫자로 출력
// 10개의 페어가 맞추면 게임은 종료
// -1을 입력하면 게임 끝 

#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
using namespace std;

int main(void) {


	// 1. 1~10 까지 숫자를 넣는 페어 만들기 
	int cardPair1[10] = {};
	int cardPair2[10] = {};

	srand((unsigned int)time(0));

	//카드1의 랜덤 난수 넣기. 
	for (int i  = 0; i < 10; i++) {
		cardPair1[i] = (rand() % 10) + 1;
		//중복 검사 
		for (int j = 0; j < i; j++) {
			if (cardPair1[i] == cardPair1[j]) {
				i--;
				break;
			}
		}
	}
	
	int card2_input[10] = {};
	// 카드2 랜덤 난수 넣기 이번엔 셔플 스왑 사용해보자
	for (int i = 0; i < 10; i++) {
		card2_input[i] = i + 1;
	}

	//카드 2 숫자를 1oo번 셔플하고 스왑해서 난수를 생성
	int N1, N2, temp;
	for (int i = 0; i < 100; i++) {
		N1 = rand() % 10;
		N2 = rand() % 10;
		// 스왑
		temp = card2_input[N1];
		card2_input[N1] = card2_input[N2];
		card2_input[N2] = temp;
	}
	
	//셔플한 로또 번호를 받아온다.
	for (int i = 0; i < 10; i++) {
		cardPair2[i] = card2_input[i];
	}

	// 카드페어 1와 카드 2를 합친 카드페어3 
	int cardPair3[20] = {};

	// 카드페어1 의 내용을 cardPair3에 복사
	for (int i = 0; i < 10; i++) {
		cardPair3[i] = cardPair1[i];
	}
	// cardPair2의 내용을 cardPair3의 10번 인덱스부터 복사
	for (int i = 0; i < 10; i++) {
		cardPair3[i + 10] = cardPair2[i];
	}

	//카드3를 한번 더 섞자 
	for (int i = 0; i < 100; i++) {
		// 0부터 19까지의 랜덤 인덱스 N1, N2 생성
		N1 = rand() % 20;
		N2 = rand() % 20;

		// 스왑
		temp = cardPair3[N1];
		cardPair3[N1] = cardPair3[N2];
		cardPair3[N2] = temp;
	}

	//정답지 
	cout << "정답지 \n";
	for (int i = 0; i < 20; i++) {
		cout << cardPair3[i] << ' ';
		//10개 출력후 줄바꿈
		if (i == 9) {
			cout << endl;
		}
	}

	cout << endl << endl;

	cout << "*이 찍히는지 확인 \n";
	//2. 10* 2로 출력 * 출력 
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 10; j++){
			cout << '*' << ' ';
		}
		cout << endl;
	}
	
	// 3. 사용자는 인덱스 2개를 입력해서, 값이 같으면 해당 부분은 숫자로 출력
	// 10개의 페어가 맞추면 게임은 종료
	// -1을 입력하면 게임 끝 
	cout << endl;
	
	int total = 0, correctCount = 0, notCorrect = 0; 
	cout << "게임을 시작 합니다! \n";
	cout << endl;

	while (1) {
		// 사용자가 인덱스를 입력할 숫자 입력 
		int  inputNum1, inputNum2; 
		cout << "카드를 입력하세요 인덱스 번호 0 ~ 19 ,(종료 -1) : ";
		cin >> inputNum1 >> inputNum2;
		
		// -1을 입력하면 게임을 종료 
		if (inputNum1 == -1 || inputNum2 == -1) {
			cout << "게임을 종료합니다 \n";
			return 0;
		}  

		// 같은 인덱스 입력 방지
		if (inputNum1 == inputNum2) {
			cout << "\033[1;31m같은 인덱스(위치)는 선택할 수 없습니다. 다시 선택해주세요.\033[0m \n";
			cout << endl;
			continue; 
		}
		
		// 정답으로 맞춘 카드라면 선택 불가?
		//if () {
		//	cout << "\033[1;31m이미 선택한 카드입니다  다시 선택해주세요.\033[0m \n";
		//	cout << endl;
		//	continue;
		//}

		if (cardPair3[inputNum1] == cardPair3[inputNum2]) {

				cout << "\033[1;34m값이 같습니다 \033[0m \n";
				cout << "카드1의 [" << inputNum1 << "]의 값 = " << cardPair3[inputNum1];
				cout << ", 카드2의 [" << inputNum2  << "]의 값 = " << cardPair3[inputNum2] << endl;
				correctCount++;
				cout << "맞은 개수 : " << correctCount << endl << endl;
				total++;

				//10개의 페어를 다 맞춘 경우 
				if (correctCount == 10) {
					cout << "\033[1;32m카드를 모두 맞췄습니다 !! \033[0m \n";
					break;
				}

				continue; 

		}
		else {
			cout << "\033[1;31m아닙니다 다시 선택 해주세요 \033[0m \n";
			cout << "카드1의 [" << inputNum1 << "]의 값 = " << cardPair3[inputNum1];
			cout << ", 카드2의 [" << inputNum2 << "]의 값 = " << cardPair3[inputNum2] << endl << endl ;
			notCorrect++; 
			total++;
			continue;
		
		}
		
	}

	cout << "시도한 횟수 : " << total << " 틀린 횟수 : " << notCorrect << endl;
	cout << "게임을 종료 합니다 \n";
	return 0;


}


/*----------------------------------------------------

 오후 실습 로또 프로그램 만들기
 로또 번호 1~45 사이의 번호 출력
 로또 1 등번호 6개 출력하고, 보너스 번호 1개를 출력 


	int nansuNum[7] = {}; //난수 번호 저장
	srand((unsigned int)time(0));

	cout << "로또 번호 추첨 시작 \n";

	// 1. 로또 난수 생성 6자리는 1등 번호고 마지막(7번째) 자리는 보너스 번호
	for (int i = 0; i < 7; i++) {
		nansuNum[i] = (rand() % 45) + 1;
		//중복 체크
		for (int j = 0; j < i ; j++) {
			if (nansuNum[i] == nansuNum[j]) {
				i--;
				break;
			}
		}
	}

	// 로또 출력
	cout << "로또 1등 당첨 번호 : ";
	for (int i = 0; i < 6; i++) {
		cout << "\033[1;36m" << nansuNum[i] << "\033[0m ";
	}
	cout << endl;
	cout << "보너스(마지막) 번호 : \033[1;31m" << nansuNum[6] << "\033[0m \n";



	int nansuNum[45] = {};
	int lottoNum[7] = {}; //셔플한 숫자를 받아올 로또번호
	srand((unsigned int)time(0));

	cout << "로또 번호 추첨 시작 \n";
	//이번에는 셔플해서 출력
	for (int i = 0; i < 45; i++) {
		nansuNum[i] = i + 1;
	}

	//숫자를 셔플하고 스왑해서 난수를 생성
	int nNumber1 = 0, nNumber2 = 0, nTemp = 0;
	for (int i = 0; i < 100; i++) {
		nNumber1 = rand() % 45;
		nNumber2 = rand() % 45;
		// 스왑
		nTemp = nansuNum[nNumber1];
		nansuNum[nNumber1] = nansuNum[nNumber2];
		nansuNum[nNumber2] = nTemp;
	}

	//셔플한 로또 번호를 받아온다.
	for (int i = 0; i < 7; i++) {
		lottoNum[i] = nansuNum[i];
	}

	// 로또 출력
	cout << "로또 1등 당첨 번호 : ";
	for (int i = 0; i < 6; i++) {
		cout << "\033[1;36m" << lottoNum[i] << "\033[0m ";
	}
	cout << endl;
	cout << "보너스(마지막) 번호 : \033[1;31m" << lottoNum[6] << "\033[0m \n";


	---------------------------------------------------
	방법 2
		int nansuNum[45] = {};
	int lottoNum[7] = {}; //셔플한 숫자를 받아올 로또번호
	srand((unsigned int)time(0));

	cout << "로또 번호 추첨 시작 \n";
	//이번에는 셔플해서 출력
	for (int i = 0; i < 45; i++) {
		nansuNum[i] = i + 1;
	}

	//숫자를 셔플하고 스왑해서 난수를 생성
	int nNumber1 = 0, nNumber2 = 0, nTemp = 0;
	for (int i = 0; i < 100; i++) {
		nNumber1 = rand() % 45;
		nNumber2 = rand() % 45;
		// 스왑
		nTemp = nansuNum[nNumber1];
		nansuNum[nNumber1] = nansuNum[nNumber2];
		nansuNum[nNumber2] = nTemp;
	}

	//셔플한 로또 번호를 받아온다.
	for (int i = 0; i < 7; i++) {
		lottoNum[i] = nansuNum[i];
	}

	// 로또 출력
	cout << "로또 1등 당첨 번호 : ";
	for (int i = 0; i < 6; i++) {
		cout << "\033[1;36m" << lottoNum[i] << "\033[0m ";
	}
	cout << endl;
	cout << "보너스(마지막) 번호 : \033[1;31m" << lottoNum[6] << "\033[0m \n";

*/
