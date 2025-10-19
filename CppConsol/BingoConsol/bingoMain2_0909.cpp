//빙고를 수정해라
// 배열 포인터, 함수화 할것 
#include <iostream>
#include <ctime>
#include <random>
#include <Windows.h>

using namespace std;

// 전역 변수 선언
int plyerBigoCount = 0;
int pcBigoCount = 0;
bool Player_check[5][5] = {};
bool pc_check[5][5]{};

// 함수 선언
void gamePlay_Logic(int player_bingo[][5], int Pc_bingo[][5]);
void bingoCheck();
void gameResult(int player_bingo[][5], int Pc_bingo[][5]);
void vicory_condition();

// Main Func
int main(void) {
    srand(unsigned int(time(0)));
    // 빙고판 변수
    int playerBingoFan[5][5] = {};
    int pcBingoFan[5][5] = {};

    // 빙고판 값을 받아 인덱스에 넣기
    int tempN1[25]{}, tempN2[25]{};
    int temp = 0;
    int inputIndex1 = 0, inputIndex2 = 0;
    int suffleNum1 = 0, suffleNum2 = 0;

    for (int i = 0; i < 25; i++) {
        tempN1[i] = i + 1;
        tempN2[i] = i + 1;
    }

    // 유저용 빙고판 셔플
    for (int i = 0; i < 100; i++) {
        suffleNum1 = rand() % 25;
        suffleNum2 = rand() % 25;

        temp = tempN1[suffleNum1];
        tempN1[suffleNum1] = tempN1[suffleNum2];
        tempN1[suffleNum2] = temp;
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            playerBingoFan[i][j] = tempN1[inputIndex1++];
        }
    }

    // 컴퓨터 빙고판 셔플
    for (int i = 0; i < 100; i++) {
        suffleNum1 = rand() % 25;
        suffleNum2 = rand() % 25;

        temp = tempN2[suffleNum1];
        tempN2[suffleNum1] = tempN2[suffleNum2];
        tempN2[suffleNum2] = temp;
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            pcBingoFan[i][j] = tempN2[inputIndex2++];
        }
    }

    gamePlay_Logic(playerBingoFan, pcBingoFan);

    return 0;
}

// 게임 로직을 진행
void gamePlay_Logic(int player_bingo[][5], int Pc_bingo[][5]) {
    while(1) {
        system("cls");

        // 빙고판 출력
        cout << "플레이어 빙고판\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (Player_check[i][j] == true) {
                    cout << "\033[1;33mX\033[0m\t";
                }
                else {
                    cout << player_bingo[i][j] << "\t";
                }
            }
            cout << endl;
        }

        cout << "------------------" << endl;

        cout << "컴퓨터용 빙고판\n";
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (pc_check[i][j] == true) {
                    cout << "\033[1;35mX\033[0m \t";
                }
                else {
                    cout << Pc_bingo[i][j] << "\t";
                }
            }
            cout << endl;
        }
        cout << "------------------" << endl;

        // 빙고 개수
        bingoCheck();
       //vicory_condition();

        // 승리 조건 충족 시 게임 종료
        if (plyerBigoCount >= 3 || pcBigoCount >= 3) {
            gameResult(player_bingo, Pc_bingo);
            break;
        }

        cout << endl;

        // 플레이어 턴
        int playerSelect = 0;
        bool plyerKeyFound = false;

        while (true) {
            cout << "플레이어의 차례, 입력하실 숫자를 선택 하세요 : ";
            cin >> playerSelect;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (player_bingo[i][j] == playerSelect && !Player_check[i][j]) {
                        plyerKeyFound = true;
                        break;
                    }
                }
                if (plyerKeyFound) break;
            }

            if (plyerKeyFound) {
                cout << "플레이어가 " << playerSelect << "을(를) 선택했습니다." << endl;
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (player_bingo[i][j] == playerSelect) {
                            Player_check[i][j] = true;
                        }
                        if (Pc_bingo[i][j] == playerSelect) {
                            pc_check[i][j] = true;
                        }
                    }
                }
                break;
            }
            else {
                cout << "\033[1;31m잘못된 입력이거나 이미 선택된 숫자입니다. 다시 입력하세요.\033[0m" << endl;
                system("pause");
                system("cls");
                continue;
            }
        }

        // 컴퓨터 턴
        int pcSelect = 0;
        bool pcKeyFound = false;

        while (true) {
            cout << "컴퓨터가 선택 중 입니다..... \n";
            pcSelect = (rand() % 25) + 1;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    if (player_bingo[i][j] == pcSelect && !Player_check[i][j]) {
                        pcKeyFound = true;
                        break;
                    }
                }
                if (pcKeyFound) break;
            }

            if (pcKeyFound) {
                cout << "컴퓨터가 " << pcSelect << "을(를) 선택했습니다. \n";
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (player_bingo[i][j] == pcSelect) {
                            Player_check[i][j] = true;
                        }
                        if (Pc_bingo[i][j] == pcSelect) {
                            pc_check[i][j] = true;
                        }
                    }
                }
                break;
            }
        }
        system("pause");
    }
}

// 빙고판 값을 체크한다.
void bingoCheck() {
    // 매 턴마다 빙고 개수를 0으로 초기화
    plyerBigoCount = 0;
    pcBigoCount = 0;

    // 가로줄
    for (int i = 0; i < 5; i++) {
        bool isPlyerBingo = true;
        bool isComputerBingo = true;
        for (int j = 0; j < 5; j++) {
            if (!Player_check[i][j]) {
                isPlyerBingo = false;
            }
            if (!pc_check[i][j]) {
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
            if (!Player_check[i][j]) {
                isPlyerBingo = false;
            }
            if (!pc_check[i][j]) {
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
        if (!Player_check[i][i]) {
            isPlayerBingo1 = false;
        }
        if (!pc_check[i][i]) {
            isPcbingo1 = false;
        }
    }
    if (isPlayerBingo1) { plyerBigoCount++; }
    if (isPcbingo1) { pcBigoCount++; }

    // 대각선 (오른쪽 위 -> 왼쪽 아래)
    bool isPlayerBingo2 = true;
    bool isPcBingo2 = true;
    for (int i = 0; i < 5; i++) {
        if (!Player_check[i][4 - i]) {
            isPlayerBingo2 = false;
        }
        if (!pc_check[i][4 - i]) {
            isPcBingo2 = false;
        }
    }
    if (isPlayerBingo2) {
        plyerBigoCount++;
    }
    if (isPcBingo2) {
        pcBigoCount++;
    }
}

// 게임 결과를 출력
void gameResult(int player_bingo[][5], int Pc_bingo[][5]) {
    system("cls");
    // 플레이어 빙고판 출력
    cout << "플레이어 빙고판" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (Player_check[i][j]) {
                cout << "\033[1;33mX\033[0m \t";
            }
            else {
                cout << player_bingo[i][j] << "\t";
            }
        }
        cout << endl;
    }
    cout << "------------------" << endl;

    // 컴퓨터 빙고판 출력
    cout << "컴퓨터 빙고판" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (pc_check[i][j]) {
                cout << "\033[1;35mX\033[0m \t";
            }
            else {
                cout << Pc_bingo[i][j] << "\t";
            }
        }
        cout << endl;
    }

    vicory_condition();
}

// 게임 승리 조건
void vicory_condition() {
    cout << "------------------" << endl;
    cout << "최종 플레이어 빙고: " << plyerBigoCount << "개\n";
    cout << "최종 컴퓨터 빙고: " << pcBigoCount << "개 \n";

    if (plyerBigoCount >= 3 && pcBigoCount >= 3) {
        cout << "무승부! \n";
    }
    else if (plyerBigoCount >= 3) {
        cout << "플레이어가 승리하였습니다 \n";
    }
    else if (pcBigoCount >= 3) {
        cout << "플레이어가 패배 하였습니다! \n";
    }

    system("pause");
}