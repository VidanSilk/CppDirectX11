#pragma once
#include "SceneObject.h"
#include "../Share/SharedPtr.h"

class CPlayerObject;

class CAshFloor : public CSceneObject
{
	friend class CScene;

public:
	CAshFloor();
	CAshFloor(const CAshFloor& Obj);
	CAshFloor(CAshFloor&& Obj);
	virtual ~CAshFloor();

protected:

	CSharedPtr<class CSpriteComponent> mAshFloor; //바닥용 시트2
	CSharedPtr<class CColliderAABB2D> mAshFloorCollider; // 페이즈1 바닥용 콜라이더 
	CSharedPtr<class CGravityComponent> mGravity;

private:

	CColliderAABB2D* GetFloorCollider()  const {
		return mAshFloorCollider.Get();
	}

public:
	virtual bool Init();
	void CheckFloorCollider(CPlayerObject* Obj);

private:

};

