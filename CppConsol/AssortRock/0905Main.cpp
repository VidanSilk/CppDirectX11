#include <iostream>
#include <ctime>
#include <random>
#include <Windows.h>

using namespace std;


//배열 마지막 실습 
// 빙고, 5 x 5로 빙고
// 빙고 맞춘 갯 수 출력
// 5빙고면 게임 종료
// 가능하면 내가 선택하고 컴퓨터가 하나 선택하는 적 ai 기능 만들기

/*
	로직
	1. 빙고판을 만든다 → 5 * 5로 빙고판 제작  (내용은 1~25까지 숫자만 넣자, 위치는 상관 없음)
	2. 플레이어와 컴퓨터가 서로 번갈아 가면서 숫자를 선택 한다 (게임 플레이)
	3.  가로 세로 대각선 상관없이 빙고가 5개면 게임은 끝난다
	
	비고 
	1. 이미 선택한 숫자는 다시 선택할 수 없다. (중복 불가)

*/

int main(void) {

	//1. 빙고판 생성 2차원 (플레이어용 빙고판) 
	int bingo[5][5] = {};
	bool bingoOpened1[5][5] = {};
	srand((unsigned int)time(0));

	// 컴퓨터용 빙고판
	int bingoPC[5][5] = {};
	bool bingoOpened2[5][5] = {};

	// 1차원 배열에 원소 값을 받는다 
	int tempNum[25] = {};

	for (int i = 0; i < 25; i++) {
		tempNum[i] = i + 1;
	}

	// 임시 빙고판을 셔플하고 스왑한다
	int temp, n1, n2;
	for (int i = 0; i < 100; i++) {
		n1 = rand() % 25;
		n2 = rand() % 25;

		temp = tempNum[n1];
		tempNum[n1] = tempNum[n2];
		tempNum[n2] = temp;
	}

	//셔플한 1차원 배열의 원소 값을 2차원 배열에 할당 )유저용)
	int index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			bingo[i][j] = tempNum[index++];
		}
	}

	// 컴퓨터 빙고판 셔플
	for (int i = 0; i < 100; i++) {
		n1 = rand() % 25;
		n2 = rand() % 25;

		temp = tempNum[n1];
		tempNum[n1] = tempNum[n2];
		tempNum[n2] = temp;
	}

	index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			bingoPC[i][j] = tempNum[index++];
		}
	}

	// 게임 시작 (게임 로직)
	while (1) {
		system("cls");

		//빙고판 플레이어용 생성 
		cout << "플레이어 빙고판\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoOpened1[i][j] == true) {
					cout << "\033[1;33mX\033[0m\t";
				}
				else {
					cout << bingo[i][j] << "\t";
				}
			}
			cout << endl;
		}

		cout << "------------------" << endl;

		cout << "컴퓨터용 빙고판\n";
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoOpened2[i][j] == true) {
					cout << "\033[1;35mX\033[0m \t";
				}
				else {
					cout << bingoPC[i][j] << "\t";
				}
			}
			cout << endl;
		}
		cout << "------------------" << endl;
		cout << endl;
		//	2. 플레이어와 컴퓨터가 서로 번갈아 가면서 숫자를 선택 한다 (게임 플레이)
		// 플레이어는 숫자를 입력하고, 입력한 값이 [인덱스]에 있는 값과 비교해서 
		// 정답이 되면 X로 

		int playerSelect = 0;
		bool plyerKeyFound = false;

		int pcSelect = 0;
		bool pcKeyFound = false;

		// 2-1. 플레이어 
		while (1) {

			cout << "플레이어의 차례, 입력하실 숫자를 선택 하세요 : ";
			cin >> playerSelect;

			// 빙고판에서 숫자 찾기 (공통)
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (bingo[i][j] == playerSelect && !bingoOpened1[i][j]) {
						plyerKeyFound = true;
						break;
					}
				}
				if (plyerKeyFound) break;
			}

			if (plyerKeyFound) {
				cout << "플레이어가 " << playerSelect << "을(를) 선택했습니다." << endl;

				// 선택된 숫자를 양쪽 빙고판에 모두 표시
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						if (bingo[i][j] == playerSelect) {
							bingoOpened1[i][j] = true;
						}
						if (bingoPC[i][j] == playerSelect) {
							bingoOpened2[i][j] = true;
						}
					}
				}
				system("pause");
				break;
			}
			else {
				cout << "\033[1;31m잘못된 입력이거나 이미 선택된 숫자입니다. 다시 입력하세요.\033[0m" << endl;
				system("pause");
				continue;
			}
		}


		// 2-2. 컴퓨터
		while (1) {

			cout << "컴퓨터가 선택 중 입니다..... \n";
			// 컴퓨터는 어떻게 입력해야할까... ?  
			// 로직은 플레이어와 비슷하게 작동하는 것 같음, but 입력은 ? 
			// 1~25를 난수로 돌려서 선택하게 한다 
			pcSelect = (rand() % 25) + 1;

			for (int i = 0; i < 5; i++) {				for (int j = 0; j < 5; j++) {
					if (bingo[i][j] == pcSelect && !bingoOpened1[i][j]) { // 플레이어 판을 기준으로 이미 선택된 숫자인지 확인
						pcKeyFound = true;
						break;
					}
				}
				if (pcKeyFound) break;
			}

			if (pcKeyFound) {
				// 중복된 값이 있으면 다시 선택하는 기능도 포함
				cout << "컴퓨터가 " << pcSelect << "을(를) 선택했습니다. \n";

				// 선택된 숫자를 양쪽 빙고판에 모두 표시
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 5; j++) {
						//플레이어 빙고판
						if (bingo[i][j] == pcSelect) {
							bingoOpened1[i][j] = true;
						}
						// 컴퓨터 빙고판
						if (bingoPC[i][j] == pcSelect) {
							bingoOpened2[i][j] = true;
						}
					}
				}
				system("pause");
				break;
			}
		}

		// 빙고 개수 확인 컴퓨터도 포함하여  
		int plyerBigoCount = 0;
		int pcBigoCount = 0;

		// 가로줄
		for (int i = 0; i < 5; i++) {
			bool isPlyerBingo = true;
			bool isComputerBingo = true;
			for (int j = 0; j < 5; j++) {
				if (!bingoOpened1[i][j]) {
					isPlyerBingo = false;
				}
				if (!bingoOpened2[i][j]) {
					isComputerBingo = false;
				}
			}
			if (isPlyerBingo) {
				plyerBigoCount++;
			}
			if (isComputerBingo) {
				pcBigoCount++;
			}

		}
		// 세로줄
		for (int j = 0; j < 5; j++) {
			bool isPlyerBingo = true;
			bool isComputerBingo = true;
			for (int i = 0; i < 5; i++) {
				if (!bingoOpened1[i][j]) {
					isPlyerBingo = false;
				}
				if (!bingoOpened2[i][j]) {
					isComputerBingo = false;
				}
			}
			if (isPlyerBingo) {
				plyerBigoCount++;
			}
			if (isComputerBingo) {
				pcBigoCount++;
			}

		}
		// 대각선 (왼쪽 위 -> 오른쪽 아래)
		bool isPlayerBingo1 = true;
		bool isPcbingo1 = true;
		for (int i = 0; i < 5; i++) {
			if (!bingoOpened1[i][i]) {
				isPlayerBingo1 = false;
			}
			if (!bingoOpened2[i][i]) {
				isPcbingo1 = false;
			}
		}
		if (isPlayerBingo1) { plyerBigoCount++; }
		if (isPcbingo1) { pcBigoCount++; }

		// 대각선 (오른쪽 위 -> 왼쪽 아래)
		bool isPlayerBingo2 = true;
		bool isPcBingo2 = true;
		for (int i = 0; i < 5; i++) {
			if (!bingoOpened1[i][4 - i]) {
				isPlayerBingo2 = false;
			}
			if (!bingoOpened2[i][4 - i]) {
				isPcBingo2 = false;
			}
		}
		if (isPlayerBingo2) {
			plyerBigoCount++;
		}
		if (isPcBingo2) {
			pcBigoCount++;
		}

		system("cls");

		// 플레이어 빙고판 출력
		cout << "플레이어 빙고판" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoOpened1[i][j]) { 
					cout << "\033[1;33mX\033[0m \t"; 
				}
				else { 
					cout << bingo[i][j] << "\t";
				}
			}
			cout << endl;
		}
		cout << "------------------" << endl;

		// 컴퓨터 빙고판 출력
		cout << "컴퓨터 빙고판" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoOpened2[i][j]) {
					cout << "\033[1;35mX\033[0m \t"; 
				}
				else { 
					cout << bingoPC[i][j] << "\t"; 
				}
			}
			cout << endl;
		}
		cout << "------------------" << endl;
		cout << "현재 플레이어 빙고: " << plyerBigoCount << "개\n";
		cout << "현재 컴퓨터 빙고: " << pcBigoCount << "개 \n";
		//cout << "컴퓨터의 빙고 : << 변수명 << endl;
		if (plyerBigoCount >= 3 && pcBigoCount >= 3) {
			cout << "무승부! \n";
			break;
		}
		else if (plyerBigoCount >= 3) {
			cout << "플레이어가 승리하였습니다 \n";
			break;
		}
		else if (pcBigoCount >= 3) {
			cout << "플레이어가 패배 하였습니다! \n";
			break;

		}

	}

	return 0;
}