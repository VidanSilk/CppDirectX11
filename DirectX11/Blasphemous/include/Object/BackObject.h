#pragma once
#include "SceneObject.h"
class CBackObject :
	public CSceneObject
{
	friend class CScene;

protected:
	CBackObject();
	CBackObject(const CBackObject& Obj);
	CBackObject(CBackObject&& Obj);
	virtual ~CBackObject();

protected:
	//CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CSpriteComponent> mRoot; //백그라운드 배경 
	//CSharedPtr<class CSpriteComponent> mStatue; // 백그라운드 석상 배경

public:
	virtual bool Init();

private: 

};

