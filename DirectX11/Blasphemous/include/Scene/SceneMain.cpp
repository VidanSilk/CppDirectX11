#include "SceneMain.h"
#include "SceneAssetManager.h"
#include "SceneUIManager.h"
#include "Input.h"
#include "SceneMain2.h"
#include "SceneManager.h" 

#include "../Asset/AssetManager.h"
#include "../Asset/Material/Material.h"
#include "../Asset/Sound/SoundManager.h"

#include "../Object/TileMapObj.h"
#include "../Object/PlayerObject.h"
#include "../Object/ObjectSpawnPoint.h"
#include "../Object/BackObject.h"
#include "../Object/BackWall.h"
#include "../Object/BackFloor.h"
#include "../Object/BackFloorTwo.h"
#include "../Object/BackFloorThree.h"
#include "../Object/CameraObject.h"
#include "../Object/Pope/Pope.h"
#include "../Share/Log.h"
#include "../UI/UserWidget/MainWidget.h"
#include "../UI/UserWidget/CloudWidget.h"
#include "../UI/UserWidget/TwisterWidget.h"
#include "../Object/AshBright.h"

// 인풋 키 'p'를 누르거나 교황이 죽을시 안개가 소환되면서 씬전환 
CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
	//CAssetManager::GetInst()->GetSoundManager()->Stop("PopeBGM");
}

void CSceneMain::StartStageTransition(float DeltaTime)
{
	if (mTransitionStarted) return;
	mTransitionStarted = true;

	// Cloud 위젯 생성/등록 
	if (!mCloud)
	{
		mCloud = mUIManager->CreateWidget<CCloudWidget>("CloudTransition"); // 혹은 Cloud_Back
		mUIManager->AddToViewport(mCloud);
	}

	// 안개 덮이는 순간에 씬 전환
	mCloud->StartTransition([this]() {
		//  여기에서 Stage2로 씬 전환 호출
		// 음악도끄기 
		//CAssetManager::GetInst()->GetSoundManager()->Stop("PopeBGM");
		CSceneManager::GetInst()->CreateLoadScene<CSceneMain2>();
		CLog::PrintLog("SceneMain2 True");
		}, [this]() { },
			2.5f,   // CloseTime (덮기 시간) 
			3.0f,  // HoldTime  (덮인 상태 유지)
			2.0f    // OpenTime  (열기 시간)
	);
}

bool CSceneMain::Init()
{
	if (!CScene::Init())
	{
		return false;
	}

	///////////// 사용할 머티리얼 미리 만든다!!
	//mAssetManager->CreateMaterial("Monster1");

	///////////// 사용할 사운드도 미리 추가한다.
	mAssetManager->LoadSound("PopeBGM", "BGM", true, "Sound\\BossSound\\Pontiff.wav");
	CAssetManager::GetInst()->GetSoundManager()->Play("PopeBGM"); 

	CCameraObject* Camera = CreateObj<CCameraObject>("Camera");
	if (!Camera) return false;
	Camera->GetWorldPosition();

	//백그라운드 오브젝트  1280, 720
	CBackObject* BackGorundObject1 = CreateObj<CBackObject>("BackGround");
	BackGorundObject1->SetWorldScale(1280.f, 720.f);
	BackGorundObject1->SetWorldPos(0.f, 0.f, 0.0f);

	CBackFloorTwo* BackGorundObject7 = CreateObj<CBackFloorTwo>("pontiffFloor2While");
	if (BackGorundObject7 == nullptr) return false;
//	BackGorundObject7->SetWorldScale(1280.0f, 250.f);
	BackGorundObject7->SetWorldPos(0.f, -275.f, 0.01f);

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");
	if (Player == nullptr) return false;
	Player->SetBackFloorTwo(BackGorundObject7);
	Player->SetWorldPos(-400.f, -170.f);

	CObjectSpawnPoint* PopePoint = CreateObj<CObjectSpawnPoint>("Pope");
	if (!PopePoint) return false;
	PopePoint->SetSpawnType(EObjectSpawnType::Pope);
	PopePoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
	PopePoint->SetWorldPos(400.f, -150.f);
//	PopePoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	//PopePoint->SetDestroySpawnCount(100);

	//for (int i = 0; i < 40; ++i)
	//{
	//	CAshBright* ash = CreateObj<CAshBright>("Ash_" + std::to_string(i));
	//	ash->SetArea(-100.f, 1380.f, 720.f, 900.f, -700.f);
	//	ash->randomAsh(); 
	//}
	//

////	UI 생성
//	CMainWidget* Widget = mUIManager->CreateWidget<CMainWidget>("main");
//	mUIManager->AddToViewport(Widget);
//	

	GetInput()->AddBindKey("StageChange", 'P');
	GetInput()->AddBindFunction("StageChange", EInputType::Down, this, &CSceneMain::StartStageTransition);

	GetInput()->AddBindKey("KillPope", 'U');
	GetInput()->AddBindFunction("KillPope", EInputType::Down, this, &CSceneMain::DebugKillPope);
	return true;
}

void CSceneMain::Update(float DeltaTime)
{
	CScene::Update(DeltaTime);
	
	// 교황 찾기 
	CPope* Pope = FindObjectFromType<CPope>();

	if (Pope)
		mPopeSpawnedOnce = true;

	// 교황이 한 번이라도 생성되었다면
	if (!mTransitionStarted && mPopeSpawnedOnce)
	{
		// 포프가 죽음 애니 시작하는 순간 -> 즉시 전환
		if (Pope && Pope->IsDeathStarted())
		{
			StartStageTransition(DeltaTime);
			return;
		}

		// 2) 기존 로직(포프가 사라졌을 때도 전환)
		if (!Pope || !Pope->IsActive())
		{
			StartStageTransition(DeltaTime);
		}
	}
}


void CSceneMain::DebugKillPope(float DeltaTime)
{
	CPope* Pope = FindObjectFromType<CPope>();
	if (Pope)
	{
		Pope->BeginDeath(); // 아래에서 Pope 쪽 함수로 정리
		StartStageTransition(0.f); // 바로 안개 트리거도 가능(원하면)
	}
}