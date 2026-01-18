#include "Scene.h"

#include "Input.h"
#include "CameraManager.h"
#include "SceneCollision.h"
#include "SceneAssetManager.h"
#include "SceneUIManager.h"
#include "../GameManager.h"
#include "../Share/Log.h"
#include <iostream>

CScene::CScene()
{
}

CScene::~CScene()
{
	auto iter = mObjList.begin();
	auto iterEnd = mObjList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Destroy();

	}

	mObjList.clear();
	SAFE_DELETE(mAssetManager);
	SAFE_DELETE(mInput);
	SAFE_DELETE(mCameraManager);
	SAFE_DELETE(mCollision);
	SAFE_DELETE(mUIManager);
}

bool CScene::Init()
{
	mInput = new CInput;
	mInput->mScene = this;

	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
	{
		SAFE_DELETE(mCameraManager);
		return false;
	}

	mCollision = new CSceneCollision;
	mCollision->mScene = this;
	if (!mCollision->Init())
	{
		SAFE_DELETE(mCollision);
		return false;
	}

	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
	{
		SAFE_DELETE(mAssetManager);
		return false;
	}

	mUIManager = new CSceneUIManager;
	mUIManager->mScene = this;
	if (!mUIManager->Init())
	{
		SAFE_DELETE(mUIManager);
		return false;
	}

	//콜라이더 On/off 토글키 
	GetInput()->AddBindKey("ToggleColliderDraw", 'O');
	GetInput()->AddBindFunction("ToggleColliderDraw", EInputType::Down,
		this, &CScene::ToggleColliderDraw);

	//쿼드트리 On/off 토글키 
	GetInput()->AddBindKey("ToggleQuadTreeDraw", 'I');
	GetInput()->AddBindFunction("ToggleQuadTreeDraw", EInputType::Down,
		this, &CScene::ToggleQuadTreeDraw);


	// 마우스 좌클릭으로 좌표 찍기
	// 근데 좌클릭시 2번씩 찍히고 
	// 우클릭이면 우클릭이 안되고 좌클릭으로 2번찍힘 
	if (!mPickBindAdded)
	{
		mPickBindAdded = true;
		GetInput()->AddBindKey("DebugPickPos", VK_RBUTTON);
		GetInput()->AddBindFunction("DebugPickPos", EInputType::Down, this, &CScene::DebugPickMouse);
	}
	return true;
}

bool CScene::Init(const char* FileName)
{
	mInput = new CInput;
	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
	{
		SAFE_DELETE(mCameraManager);
		return false;
	}

	mCollision = new CSceneCollision;

	mCollision->mScene = this;

	if (!mCollision->Init())
	{
		SAFE_DELETE(mCollision);
		return false;
	}

	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
	{
		SAFE_DELETE(mAssetManager);
		return false;
	} 

	mUIManager = new CSceneUIManager;
	mUIManager->mScene = this;
	if (!mUIManager->Init())
	{
		SAFE_DELETE(mUIManager);
		return false;
	}

	return true;
}

void CScene::Input(float DeltaTime)
{
	mInput->Update(DeltaTime);

	DebugPickMouse(DeltaTime);

}

void CScene::PreUpdate(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreUpdate(DeltaTime);
		++iter;
	}
}

void CScene::Update(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}

	mCameraManager->Update(DeltaTime);
	//UI 매니져 업데이트
	mUIManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}
}

void CScene::Collision(float DeltaTime)
{
	// SceneCollsion이 해당 씬의 충돌을 모두 관리하게 한다!! 
	mCollision->Update(DeltaTime, mUIManager, mInput);

	//UI 충돌 호출순서
	//Scene -> SceneCollision -> SceneUIManager -> UserWidget -> Common UI들 충돌검사를 한다. 
}

//void CScene::PreRender()
//{
//	std::list<CSharedPtr<CSceneObject>>::iterator iter;
//	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();
//
//	for (iter = mObjList.begin(); iter != iterEnd;)
//	{
//		if (!(*iter)->IsActive())
//		{
//			iter = mObjList.erase(iter);
//			iterEnd = mObjList.end();
//			continue;
//		}
//		else if (!(*iter)->IsEnable())
//		{
//			++iter;
//			continue;
//		}
//
//		(*iter)->PreRender();
//		++iter;
//	}
//}

void CScene::Render()
{
#ifdef _DEBUG
	if (mDebugQuadTree)
	{
		mCollision->Render();
	}
#endif // _DEBUG
	mCollision->ReturnNodePool();

	//std::list<CSharedPtr<CSceneObject>>::iterator iter;
	//std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	//for (iter = mObjList.begin(); iter != iterEnd;)
	//{
	//	if (!(*iter)->IsActive())
	//	{
	//		iter = mObjList.erase(iter);
	//		iterEnd = mObjList.end();
	//		continue;
	//	}
	//	else if (!(*iter)->IsEnable())
	//	{
	//		++iter;
	//		continue;
	//	}

	//	(*iter)->Render();
	//	++iter;
	//}
}
//
//void CScene::PostRender()
//{
//	std::list<CSharedPtr<CSceneObject>>::iterator iter;
//	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();
//
//	for (iter = mObjList.begin(); iter != iterEnd;)
//	{
//		if (!(*iter)->IsActive())
//		{
//			iter = mObjList.erase(iter);
//			iterEnd = mObjList.end();
//			continue;
//		}
//		else if (!(*iter)->IsEnable())
//		{
//			++iter;
//			continue;
//		}
//
//		(*iter)->PostRender();
//		++iter;
//	}
//}

void CScene::RenderUI()
{
	mUIManager->Render();
}


void CScene::EndFrame()
{
	std::list<CSharedPtr<CSceneObject>>::iterator iter;
	std::list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd; ++iter)
	{
		(*iter)->EndFrame();
	}
}

//콜라이더 on off 
void CScene::ToggleColliderDraw(float DeltaTime)
{
	CGameManager::ToggleColliderDebugDraw();
	CLog::PrintLog(CGameManager::IsColliderDebugDraw() ? "Collider Wire ON" : "Collider Wire OFF");
}

void CScene::ToggleQuadTreeDraw(float DeltaTime)
{
	CGameManager::ToggleDrawQuadTree();
	CLog::PrintLog(CGameManager::IsQuadTreeDebugDraw() ? "QuadTree ON" : "QuadTree Wire OFF");
}

void CScene::DebugPickMouse(float DeltaTime)
{
	if (!mInput->GetMouseDown(EMouseButtonType::LButton))

		return;

	const FVector2D& screen = mInput->GetMousePos();
	const FVector2D& world = mInput->GetMouseWorldPos();

	CLog::PrintLogF(ELogPrintType::Console, "Screen(%.1f, %.1f)  World(%.1f, %.1f)",
		screen.x, screen.y, world.x, world.y);

}
