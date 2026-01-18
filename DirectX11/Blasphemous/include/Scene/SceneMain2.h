#pragma once
#include "Scene.h"
class CPontiffDieWidget;

class CSceneMain2 : public CScene
{
	friend class CSceneManager;
	

protected:
	CSceneMain2();
	virtual ~CSceneMain2();
	
	bool mPontiffDieUIPlayed = false;
	CPontiffDieWidget* mPontiffWidget = nullptr;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void PlayPontiffDieUI(float DeltaTime); // Y키/죽음 공용
};
