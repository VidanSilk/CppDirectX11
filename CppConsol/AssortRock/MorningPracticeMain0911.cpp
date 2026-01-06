#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;
/*
오전 실습
Goblin, orc, Drango, Skeleton, zombi, troll, vampire, ghost, hydra, slime
해당 문자열을 분리하여 (strtok)
배열에 넣고
cin 입력시 해당 몬스터문자열이 있는지 여부 출력 strcmp
*/
#define MOSTER_LIST_COUNT 10
int main(void) {
	//배열 공간 
	char MonstList[] = { "Goblin,Orc,Drango,Skeleton,Zombie,Troll,Vampire,Ghost,Hydra,Slime" };

	char* context = nullptr;
	char* token = strtok_s(MonstList, ", ", &context);
	char monsterList[MOSTER_LIST_COUNT][100]{};
	char inputList[100];
	bool checkList = false; 
	
	//리스트에 카피해서 값을 들어감 + 문자열 나누기 
	while (token != nullptr) {
		for (int i = 0; i < 10; i++) {
			strcpy_s(monsterList[i], token);
			token = strtok_s(nullptr, ",", &context); //자료를 넣었다는 뜻

		}
	}
	//제대로 들어갔는지 확인하는 작업
	cout << "몬스터 리스트 확인 : \n";
	for (int i = 0; i < 10; i++) {
		cout << monsterList[i] << endl;
	}

	cout << "몬스터 이름을 입력 하세요 : ";
	cin >> inputList;
	for (int i = 0; i < MOSTER_LIST_COUNT; i++) {
		if (strcmp(monsterList[i], inputList) == 0) {
			checkList = true;
			break;
		}
	}

	if (checkList) {
		cout << inputList << "는 리스트에 있습니다 \n";
	}
	else {
		cout << inputList << "는 리스트에 없습니다 \n";
	}
	

	return 0;
}