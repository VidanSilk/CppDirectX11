#include "BackObject.h"

#include "../Component/SpriteComponent.h"


// 여기는 맵스테이즈 1

CBackObject::CBackObject()
{
}

CBackObject::CBackObject(const CBackObject& Obj)
{
}

CBackObject::CBackObject(CBackObject&& Obj)
{
}

CBackObject::~CBackObject()
{
}

bool CBackObject::Init()
{
	CSceneObject::Init();

	mRoot	= CreateComponent<CSpriteComponent>();
	//mStatue = CreateComponent<CSpriteComponent>(); // 백그라운드 석상 배경

	// 크자이공부
	//백그라운드 (동상 뒤)
	//mRoot->SetTexture("BackGround", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_5.png"));
	mRoot->SetTexture("BackGround", TEXT("Texture\\RealAsset\\Map\\4\\Pontif-Boss-LayerBackGround.png"));
	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);
	mRoot->SetUseTime(false);

	SetRootComponent(mRoot);

	//석상 (동상) 
	//mStatue->SetTexture("pontiffStatue", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_1.png"));
	//mStatue->SetTint(1.f, 1.f, 1.f);
	//mStatue->SetPivot(0.5f, 0.5f);
	//mStatue->SetOpacity(1.f);
	//mStatue->SetUseTime(false);
	//mRoot->AddChild(mStatue);

	return true;
}


