#include "snakeinfo.h"

#include <iostream>


CSnake::CSnake()
{
	//뱀의 시작지점을 게임 중앙으로 한다. 
	mSnake.push_back({ GAME_WIDTH / 2, GAME_HEIGHT / 2 });

	//뱀 진행 방향
	mDir = DIR::PAUSE;

}

CSnake::~CSnake()
{

}

void CSnake::Move()
{
	if (mDir == DIR::PAUSE)
		return;

	//머리가 이동할 위치 미리 계산 
	POS temp = mSnake[0];
	switch (mDir)
	{
	case DIR::LEFT:
		--temp.PosX;
		break;
	case DIR::RIGHT:
		++temp.PosX;
		break;
	case DIR::UP:
		--temp.PosY;
		break;
	case DIR::DOWN:
		++temp.PosY;
		break;
	}

	//몸통을 꼬리에서부터 앞으로 한칸씩 다라가기 
	for (int i = mSnake.size() - 1; i > 0; --i)
	{
		mSnake[i] = mSnake[i - 1];
	}

	mSnake[0] = temp;	// 머리까지 이동 



}

void CSnake::LevelUP()
{
	// end는 문자열에서 마감 널문자 같은 녀석이다. 
	//마지막 요소를 가져오고싶으면 back 사용하면 된다. 
	//mSnake.end();
	mSnake.push_back(mSnake.back());
}

