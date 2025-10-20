#pragma once
#ifndef GAMEMANGER_H
#define GAMEMANGER_H


/*
	게임을 관리하는 클래스
	-초기화
	-그려주기
	-로직 업데이트
여긴 맵 구현 및 사과를 프린트한다
 맵 30 x 30으로, 사과는 랜덤 난수
	뱀 사과
*/



class CSnake;	// 전방선언
class CApple;

class CGameManger
{
private:
	CSnake* mPSnake;	//전방선언을 사용할거면 포인터타입으로 멤버변수를 사용해야한다. 
	CApple* mPApple;

	bool mIsGameOver = false;

	bool Init();

	void HideCursor();

	void Input();
	void Draw();
	void Update();

public:
	CGameManger();
	~CGameManger();

public:
	void GameRun();



};

#endif
