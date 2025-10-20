/*
	스네이크 게임 만들기
	1. 벽그리기
	2. 랜덤한 좌표에 사과 그리기
	3. 뱀은 머리로  시작해서 사과를 먹으면 1씩 길어짐
	4. 뱀은 벽에 몸이 붙이치면 게임은 종료됨
	
	뱀 몸통은 배열
	게임판은 빙고판이랑 비슷

	기획?(로직)
	1. 뱀은 상하좌우만 이동 가능
	2. 사과는 랜덤 난수 돌려야한다 
	3. 맵의 크기는 30 x 30 
	4. gameover는 벽에 쾅하고 박거나 맵이 자기 자신을 먹는 경우 
	5. 사용할 변수부터 생각하자
	-> 게임판이니 x, y 좌표로 게임 판을 생성하고
	과일도 난수로 넣어 fruitX, fruityY (x,y)좌표에 사과가 나올 수 있게 생성하고 
	bool gameover를 넣어 게임이 끝날수 있는 조건을 넣고
	스네이크 머리와 몸 크기가 증가하는걸 구현 
*/

#pragma once
#ifndef SNAKEINFO_H
#define SNAKEINFO_H

#include "GameInfo.h"
#include <vector>

class CSnake
{
	//friend 키워드를 사용하면 private 접근지정자 라도 보여주는것을 허용한다. 
	friend class CGameManger;

private:
	std::vector<POS> mSnake;
	DIR mDir;
	//머리 몸통
public:
	CSnake();
	~CSnake();

	void Move();
	void LevelUP();

	void SetDir(DIR _dir)
	{
		mDir = _dir;
	}
	DIR GetDir()
	{
		return mDir;
	}

	POS GetHeadPos()
	{
		return mSnake.front(); //배열에 가장 앞 0번 인덱스가 머리다 .
	}


};

#endif