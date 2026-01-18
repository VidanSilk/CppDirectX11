#include "BackFloor.h"
#include "../Component/SpriteComponent.h"

CBackFloor::CBackFloor()
{
}

CBackFloor::CBackFloor(const CBackFloor& Obj)
{
}

CBackFloor::CBackFloor(CBackFloor&& Obj)
{
}

CBackFloor::~CBackFloor()
{
}

bool CBackFloor::Init()
{
	mFloor1 = CreateComponent<CSpriteComponent>(); //바닥용 시트1


	// 바닥용 시트
	mFloor1->SetTexture("pontiffFloor1Gray", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_0.png"));
	mFloor1->SetTint(0.f, 0.f, 0.f);
	mFloor1->SetPivot(0.5f, 0.5f);
	mFloor1->SetOpacity(0.5f);
	mFloor1->SetUseTime(false);

	SetRootComponent(mFloor1);

	//mFloor2->SetTexture("pontiffFloor2While", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_2.png"));
	//mFloor2->SetTint(1.f, 1.f, 1.f);
	//mFloor2->SetPivot(0.5f, 0.5f);
	//mFloor2->SetOpacity(0.7f);
	//mFloor2->SetUseTime(false);
	//mFloor1->AddChild(mFloor2);
	////SetRootComponent(mFloor2);

	//mFloor3->SetTexture("pontiffFloor3Balck", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_3.png"));
	//mFloor3->SetTint(1.f, 1.f, 1.f);
	//mFloor3->SetPivot(0.5f, 0.5f);
	//mFloor3->SetOpacity(1.f);
	//mFloor3->SetUseTime(false);
	//mFloor2->AddChild(mFloor3);
	////SetRootComponent(mFloor3);


	return true;
}
