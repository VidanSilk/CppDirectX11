#pragma once
#include "SceneObject.h"
#include "PlayerObject.h"
// fireball는 좌표 고정 3발 쏘고, 다음 위치로 가서 발사 
// toxic도 좌표 고정 1 ~ 2발 쏘고 다음 위치로 발사 
// MissileP1 좌표는 포프에서 생성됨, 근데 반전 필요할수도 있음. 
// Missilep2 좌표 고정, 반전 필요 고정된 위치에서 6방향으로 발사 


class CBulletObject : public CSceneObject
{
	friend class CScene;

private:
	float mSpeed = 200.f;
	bool mFlip = false; // 반전 여부 
	
protected:
	CBulletObject();
	CBulletObject(const CBulletObject& Obj);
	CBulletObject(CBulletObject&& Obj);
	virtual ~CBulletObject();

	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CMovementComponent> mMovement;
	// 충돌체는 서브클래스에서 구체적으로, 이유 : 파이어볼, 독탄은 Sphere인데, 미사일은 Obb라서 
	//CSharedPtr<class CColliderOBB2D> mOBody;
	//CSharedPtr<class CColliderSphere2D> mBody;
	class CAnimation2D* mAnimation = nullptr;

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}

	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}

	void  SetBulletCollisionProfile(const std::string& Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);



};

