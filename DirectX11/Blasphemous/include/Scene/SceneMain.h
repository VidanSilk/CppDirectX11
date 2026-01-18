#pragma once
#include "Scene.h"

class CCloudWidget;

class CSceneMain : public CScene
{
	friend class CSceneManager;

protected:
	CSceneMain();
	virtual ~CSceneMain();

private:
	CCloudWidget* mCloud = nullptr;
	bool mTransitionStarted = false;
	bool mPopeSpawnedOnce = false;   // 스폰되기 전 nullptr을 죽음으로 오판 방지


	void StartStageTransition(float DeltaTime);
	void DebugKillPope(float DeltaTime);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	
};

