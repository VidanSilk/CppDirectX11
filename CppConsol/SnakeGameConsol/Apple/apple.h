#pragma once
#ifndef APPLE_H
#define APPLE_H
#include "GameInfo.h"

class CApple
{
private:
	POS mPos;
public:
	CApple();
	~CApple() = default;

	POS GetApplePos()
	{
		return mPos;
	}

	void Respawn();
};


#endif // !APPLE_H
