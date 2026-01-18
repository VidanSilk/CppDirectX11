#include "BackFloorThree.h"
#include "../Component/SpriteComponent.h"

CBackFloorThree::CBackFloorThree()
{
}

CBackFloorThree::CBackFloorThree(const CBackFloorThree& Obj)
{
}

CBackFloorThree::CBackFloorThree(CBackFloorThree&& Obj)
{
}

CBackFloorThree::~CBackFloorThree()
{
}

bool CBackFloorThree::Init()
{
	mFloor3 = CreateComponent<CSpriteComponent>(); // 바닥용 시트3

	mFloor3->SetTexture("pontiffFloor3Balck", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_3.png"));
	mFloor3->SetTint(1.f, 1.f, 1.f);
	mFloor3->SetPivot(0.5f, 0.5f);
	mFloor3->SetOpacity(1.f);
	mFloor3->SetUseTime(false);
	//mFloor2->AddChild(mFloor3);
	SetRootComponent(mFloor3);


	return true;
}
