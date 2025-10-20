#include "GameManger.h"
#include "GameInfo.h"
#include "snakeinfo.h";
#include "apple.h"

#include <iostream>
//입력
#include <conio.h>	//이친구를 추가해야 입력을 받을수 있다. 

#include <Windows.h>

//c++ 동적할당은
//
//new 키워드로 생성한다.
//
//해제할때는 delete

CGameManger::CGameManger()
{
}

CGameManger::~CGameManger()
{
	if (mPSnake)
	{
		delete mPSnake;
	}

	if (mPApple)
	{
		delete mPApple;
	}
}




bool CGameManger::Init()
{
	mPSnake = new CSnake;
	if (mPSnake == nullptr)
	{
		return false;
	}

	mPApple = new CApple;
	if (mPApple == nullptr)
	{
		return false;
	}

	HideCursor();

	//int* arr = new int[100];
	//delete arr;

	return true;
}

void CGameManger::HideCursor()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void CGameManger::Input()
{
	//_kbhit();	=> 키보드가 눌렸는지 확인하는 함수 : 눌렸으면 true, 아니면 false 반환한다. 
	//_getch(); => 눌린 키값을 반환 한다. 

	if (_kbhit())
	{
		//std::cout << "키보드가 눌렸습니다. " << std::endl;
		int getkey = _getch();	//아스키코드로 나온다. 
		std::cout << (char)getkey << std::endl;

		switch (getkey)
		{
		case 'w':
			//위
			mPSnake->SetDir(DIR::UP);
			break;
		case 'a':
			//왼쪽
			mPSnake->SetDir(DIR::LEFT);
			break;
		case 's':
			//아래
			mPSnake->SetDir(DIR::DOWN);
			break;
		case 'd':
			//오른쪽
			mPSnake->SetDir(DIR::RIGHT);
			break;
		}
	}


}

void CGameManger::Draw()
{
	//콘솔에 그리기 
	system("cls");

	//데이터 가져오기 
	POS SnakeStartPos = mPSnake->GetHeadPos();
	POS ApplePos = mPApple->GetApplePos();
	//게임판 그리기
	//상단
	for (int i = 0; i < GAME_WIDTH; ++i)
	{
		std::cout << "*";
	}
	std::cout << std::endl;

	//인게임
	for (int i = 0; i < GAME_HEIGHT; ++i)
	{
		for (int j = 0; j < GAME_WIDTH; ++j)
		{
			if (j == 0 || j == GAME_WIDTH - 1)
			{
				std::cout << "*";
			}
			else if (i == SnakeStartPos.PosY && j == SnakeStartPos.PosX)
			{
				std::cout << "W";	//뱀은 위치 정보가 필요하겠네? 위치정보 몰로 만들까? 
			}
			else if (i == ApplePos.PosY && j == ApplePos.PosX)
			{
				std::cout << "@"; // 사과를 그려준다.
			}
			else
			{
				bool isSnake = false;
				// 뱀 꼬리를 그려준다. 
				for (int k = 0; k < mPSnake->mSnake.size(); ++k)
				{
					//뱀머리냐 구분할필요 없다 왜냐 else if 문으로 구분했기 때문이다. 
					//해당 인덱스가 다른 몸통이냐 
					if (i == mPSnake->mSnake[k].PosY && j == mPSnake->mSnake[k].PosX)
					{
						std::cout << "#"; //꼬리모양 그려준다. 
						isSnake = true;
						break;
					}
				}
				if (!isSnake)
				{
					std::cout << " ";
				}

			}
		}
		std::cout << std::endl;
	}
	//하단 
	for (int i = 0; i < GAME_WIDTH; ++i)
	{
		std::cout << "*";
	}

	// 뱀 그리기 


	// 과일 그리기 

}

void CGameManger::Update()
{
	//뱀 이동하기 호출
	mPSnake->Move();

	POS SnakeHeadPos = mPSnake->GetHeadPos();
	POS ApplePos = mPApple->GetApplePos();

	//뱀이 게임 밖으로 나갔는지 확인하고싶다. 
	if (SnakeHeadPos.PosX <= 0 || SnakeHeadPos.PosX >= GAME_WIDTH - 1 || SnakeHeadPos.PosY < 0 || SnakeHeadPos.PosY >= GAME_HEIGHT)
	{
		mIsGameOver = true;
		return;
	}
	//여기서 뱀끼리 충돌 어떻게 계산할까? 


	//과일 어떻게 먹었는지 알까 (뱀이랑 사과가 행과 열이 같으면 과일을 먹은거다.)
	if (SnakeHeadPos.PosX == ApplePos.PosX && SnakeHeadPos.PosY == ApplePos.PosY)
	{
		//이때가 뱀 머리랑 사과랑 같은 위치에 있는거다 
		//그럼 사과를 먹은거다. 
		//뱀 꼬리 만들기 
		mPSnake->LevelUP();
		// 사과 다른 위치로 이동 시키기 
		mPApple->Respawn();
	}

}


void CGameManger::GameRun()
{
	Init();

	//게임실행 
	while (!mIsGameOver)
	{
		Draw();
		Input();
		Update();
		std::cout << "출력" << std::endl;
		Sleep(300);
	}

	std::cout << "게임 오버 입니다. " << std::endl;
	system("pause");
}
