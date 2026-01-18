#include "SceneMain2.h"
#include "SceneAssetManager.h"
#include "SceneUIManager.h"

#include "../Share/Log.h"

#include "../UI/UserWidget/TwisterWidget.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../UI/UserWidget/PontiffDieWidget.h"
#include "../Scene/Input.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Animation/Animation2D.h"

#include "../Object/Pope/Pontiff.h"
#include "../Object/Pope/PontiffHead.h"
#include "../Object/Pope/PontiffBody.h"
#include "../Object/PlayerObject.h"
#include "../Object/AshPlatform.h"
#include "../Object/AshFloor.h"
#include "../Object/CameraObject.h"

CSceneMain2::CSceneMain2()
{
}

CSceneMain2::~CSceneMain2()
{
}

bool CSceneMain2::Init()
{	
	if (!CScene::Init()) return false;
//	mAssetManager->LoadSound("PontiffBGM", "BGM", true, "Sound\\Carlos Viola - Blasphemous - 26 - Que en Procesión Marchen.mp3");
	CAssetManager::GetInst()->GetSoundManager()->Play("PontiffBGM");

	//이게 백그라운드(배경) 역할을 할것이다. 
	CTwisterWidget* Twister = mUIManager->CreateWidget<CTwisterWidget>("TwisterBG");
	mUIManager->AddToViewport(Twister);
	Twister->SetSpeed(110.f);
	Twister->SetAlpha(0.3f);

	CAshFloor* AshFloor = CreateObj<CAshFloor>("AshFloor");
	if (AshFloor == nullptr) return false;
	//AshFloor->SetWorldScale(1280.f, 250.f);
	AshFloor->SetWorldPos(0.f, -195.f, 0.0f);

	CCameraObject* Cam = CreateObj<CCameraObject>("Main2Cam");
	Cam->SetWorldPos(0.f, 40.f, 0.f);

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");
	if (Player == nullptr) return false;
	Player->SetBackAshFloor(AshFloor);
	
	CPontiffBody* Body = CreateObj<CPontiffBody>("PontiffBody");
	if (!Body) return false;
	Body->SetWorldPos(0.f, 0.f, 0.f);
	Body->SetWorldScale(640.f, 420.f);

	CPontiffHead* Head = CreateObj<CPontiffHead>("PontiffHead");
	if (!Head) return false;
	Head->SetWorldPos(Body->GetWorldPosition());
	Head->SetWorldScale(250.f, 400.f);
	Head->SetBody(Body);
	
	CPontiff* PontiffFace = CreateObj<CPontiff>("PontiffFace");
	if (!PontiffFace) return false;
	PontiffFace->SetWorldPos(Head->GetWorldPosition());
	PontiffFace->SetWorldScale(250.f, 250.f);
	//앤 바디가아니라 얼굴에 이어야함 
	PontiffFace->SetHead(Head);
	PontiffFace->SetTarget(Player);

	CAshPlatform* p1 = CreateObj<CAshPlatform>("AshPlatform1");
	p1->SetWorldPos(140.f, 120.f); 
	p1->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p2 = CreateObj<CAshPlatform>("AshPlatform2");
	p2->SetWorldPos(-140.f, 120.f);
	p2->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p3 = CreateObj<CAshPlatform>("AshPlatform3");
	p3->SetWorldPos(270.f, 30.f);
	p3->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등

	CAshPlatform* p4 = CreateObj<CAshPlatform>("AshPlatform4");
	p4->SetWorldPos(-270.f, 30.f);
	p4->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p5 = CreateObj<CAshPlatform>("AshPlatform5");
	p5->SetWorldPos(-450.f, 50.f);
	p5->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p6 = CreateObj<CAshPlatform>("AshPlatform6");
	p6->SetWorldPos(450.f, 50.f);
	p6->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등

	CAshPlatform* p7 = CreateObj<CAshPlatform>("AshPlatform7");
	p7->SetWorldPos(-30, 15.f);
	p7->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p8 = CreateObj<CAshPlatform>("AshPlatform8");
	p8->SetWorldPos(-200.f, -80.f);
	p8->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등

	CAshPlatform* p9 = CreateObj<CAshPlatform>("AshPlatform9");
	p9->SetWorldPos(200.f, -80.f);
	p9->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p10 = CreateObj<CAshPlatform>("AshPlatform10");
	p10->SetWorldPos(-420.f, -100.f);
	p10->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등

	CAshPlatform* p11 = CreateObj<CAshPlatform>("AshPlatform11");
	p11->SetWorldPos(420.f, -100.f);
	p11->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등장

	CAshPlatform* p12 = CreateObj<CAshPlatform>("AshPlatform12");
	p12->SetWorldPos(20.f, -65.f);
	p12->SetTiming(8.0f, 4.0f); // 2초 유지, 3초 후 재등

	Player->AddBackPlatform(p1);
	Player->AddBackPlatform(p2);
	Player->AddBackPlatform(p3);
	Player->AddBackPlatform(p4);
	Player->AddBackPlatform(p5);
	Player->AddBackPlatform(p6);
	Player->AddBackPlatform(p7);
	Player->AddBackPlatform(p8);
	Player->AddBackPlatform(p9);
	Player->AddBackPlatform(p10);
	Player->AddBackPlatform(p11);
	Player->AddBackPlatform(p12);

	GetInput()->AddBindKey("PontiffDieUI_Play", 'Y');
	GetInput()->AddBindFunction("PontiffDieUI_Play", EInputType::Down, this, &CSceneMain2::PlayPontiffDieUI);

	return true;

}

void CSceneMain2::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);

	if (!mPontiffDieUIPlayed)
	{
		CPontiff* Pontiff = FindObjectFromType<CPontiff>();
		if (Pontiff && Pontiff->IsDead())
		{
			PlayPontiffDieUI(DeltaTime);
		}
	}
}

void CSceneMain2::PlayPontiffDieUI(float DeltaTime)
{
	if (mPontiffDieUIPlayed) return;
	mPontiffDieUIPlayed = true;

	// 이미 만들어졌으면 또 만들지 않기
	if (!mPontiffWidget)
	{
		mPontiffWidget = mUIManager->CreateWidget<CPontiffDieWidget>("PontiffDieUI");
		mUIManager->AddToViewport(mPontiffWidget);
	}

}
 