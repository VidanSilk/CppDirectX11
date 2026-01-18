#include "SceneManager.h"

#include "SceneMain.h"
#include "SceneStart.h"

CSceneManager::CSceneManager()
{

}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mCurrentScene);
}

bool CSceneManager::Init()
{
	//mCurrentScene = CreateScene<CSceneMain>();
	mCurrentScene = CreateScene<CSceneStart>();
	
	if (mCurrentScene == nullptr)
	{
		return false;
	}

	return true;

}

void CSceneManager::Input(float DeltaTime)
{
	mCurrentScene->Input(DeltaTime);
}


void CSceneManager::Update(float DeltaTime)
{
	mCurrentScene->PreUpdate(DeltaTime);

	mCurrentScene->Update(DeltaTime);

	mCurrentScene->PostUpdate(DeltaTime);

	//씬을 변경해야한다면
	if (mLoadScene) {
		SAFE_DELETE(mCurrentScene);
		mCurrentScene = mLoadScene;
		mLoadScene = nullptr;
		return;
	}
	return;
}

void CSceneManager::Collision(float DeltaTime)
{
	mCurrentScene->Collision(DeltaTime);
}
void CSceneManager::Render() 
{
	//mCurrentScene->PreRender();

	mCurrentScene->Render();

	//mCurrentScene->PostRender();
}

void CSceneManager::RenderUI()
{
	mCurrentScene->RenderUI();
}

void CSceneManager::EndFrame()
{
	mCurrentScene->EndFrame();
}