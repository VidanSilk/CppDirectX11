#include "apple.h"
#include <iostream>

CApple::CApple()
{
	mPos.PosX = rand() % GAME_WIDTH;
	mPos.PosY = rand() % GAME_HEIGHT;
}

void CApple::Respawn()
{
	//같은 위치 스폰 막아보기 직접 해보고싶으면 해보자!
	mPos.PosX = rand() % GAME_WIDTH;
	mPos.PosY = rand() % GAME_HEIGHT;
}
