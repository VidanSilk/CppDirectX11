#pragma once
#include "../BulletObject.h"

// 마사일은 페이즈 1일때는 직선으로 
// 페이즈2일 때는 6방향 + 특정 좌표에서 쏘게 만들어야 한다. 
// 반전 여부는 다 있어야할듯 
// aabb나 obb로 바꿔주야할듯? 

class CPopeMissile : public CBulletObject
{
	friend class CScene;

private:
	float mMissileDamage = 12.0f;
	float mMissileTime = 1.f;
	bool mFireLeft = false;
public:
	float GetFireBallDamage() const {
		return mMissileDamage;
	}

	void SetFireBall(const float& MissileDMG) {
		mMissileDamage = MissileDMG;
	}

protected:
	CPopeMissile();
	CPopeMissile(const CPopeMissile& Obj);
	CPopeMissile(CPopeMissile&& Obj);
	virtual ~CPopeMissile();
	CSharedPtr<class CColliderOBB2D> mOBody;
	//CSharedPtr<class CColliderAABB2D> mOBody;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void SetFireDir(bool bLeft);
private:
	virtual void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);

};

