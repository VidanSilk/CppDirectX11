#pragma once
struct sPosition
{
	int PosX = 0;
	int PosY = 0;
};
using POS = sPosition;

enum class eDirection
{
	PAUSE = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
using DIR = eDirection;


#define GAME_WIDTH 20
#define GAME_HEIGHT 20
