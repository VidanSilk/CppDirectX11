#pragma once
#include "SceneObject.h"
class CBackFloor :
	public CSceneObject
{
	friend class CScene;

protected:
	CBackFloor();
	CBackFloor(const CBackFloor& Obj);
	CBackFloor(CBackFloor&& Obj);
	virtual ~CBackFloor();

protected:

	CSharedPtr<class CSpriteComponent> mFloor1; //바닥용 시트1


public:
	virtual bool Init();

private:

};

