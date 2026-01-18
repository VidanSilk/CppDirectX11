#include "BackWall.h"

#include "../Component/SpriteComponent.h"

CBackWall::CBackWall()
{
}

CBackWall::CBackWall(const CBackWall& Obj)
{
}

CBackWall::CBackWall(CBackWall&& Obj)
{
}

CBackWall::~CBackWall()
{
}

bool CBackWall::Init()
{
	mWall1 = CreateComponent<CSpriteComponent>();  //백그라운드 벽 시트
	//mDeco = CreateComponent<CSpriteComponent>();

	// 벽시트
	mWall1->SetTexture("pontiffWall1", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_6.png"));
	mWall1->SetTint(1.f, 1.f, 1.f);
	mWall1->SetPivot(0.5f, 0.5f);
	mWall1->SetOpacity(1.f);
	mWall1->SetUseTime(false);
	SetRootComponent(mWall1);



	//mDeco->SetTexture("WallDeco", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_11.png"));
	//mDeco->SetTint(1.f, 1.f, 1.f);
	//mDeco->SetPivot(0.5f, 0.5f);
	//mDeco->SetOpacity(1.f);
	//mDeco->SetUseTime(false);
	//SetRootComponent(mDeco);

	return true;
}
