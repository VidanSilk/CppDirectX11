#pragma once
#include "SceneObject.h"
class CBackFloorThree :
	public CSceneObject
{
	friend class CScene;

protected:
	CBackFloorThree();
	CBackFloorThree(const CBackFloorThree& Obj);
	CBackFloorThree(CBackFloorThree&& Obj);
	virtual ~CBackFloorThree();

protected:
	CSharedPtr<class CSpriteComponent> mFloor3; // 바닥용 시트3

public:
	virtual bool Init();

private:

};

