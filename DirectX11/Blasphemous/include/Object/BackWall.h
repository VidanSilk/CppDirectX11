#pragma once
#include "SceneObject.h"


class CBackWall :
	public CSceneObject
{
	friend class CScene;

protected:
	CBackWall();
	CBackWall(const CBackWall& Obj);
	CBackWall(CBackWall&& Obj);
	virtual ~CBackWall();

protected:

	CSharedPtr<class CSpriteComponent> mWall1; //백그라운드 벽 시트
	//벽장? 철장? 안에 하나더 뭔가 있음... 하 
	//CSharedPtr<class CSpriteComponent> mDeco;
public:
	virtual bool Init();

private:

};

