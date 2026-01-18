#pragma once
#include "SceneObject.h"
#include "../Share/SharedPtr.h"

class CPlayerObject;
class CMonsterObject;

class CBackFloorTwo :
	public CSceneObject
{
	friend class CScene;
	 
public:
	CBackFloorTwo();
	CBackFloorTwo(const CBackFloorTwo& Obj);
	CBackFloorTwo(CBackFloorTwo&& Obj);
	virtual ~CBackFloorTwo();

protected:

 	CSharedPtr<class CSpriteComponent> mFloor2; //바닥용 시트2
	CSharedPtr<class CColliderAABB2D> mFloorCollider; // 페이즈1 바닥용 콜라이더 
	CSharedPtr<class CGravityComponent> mGravity;

private: 

	CColliderAABB2D* GetFloorCollider()  const { 
		return mFloorCollider.Get(); 
	}

public:
	virtual bool Init();
	void CheckFloorCollider(CPlayerObject* Obj);

	void CheckFloorCollider(CMonsterObject* Monster);
private:
};

