#pragma once
#include "../SceneObject.h"
class CPopeBeam : public CSceneObject
{
	friend class CScene;

private:
	float mBeamDmg = 10.f;
	float mHitCooldown = 0.2f;
	float mHitAcc = 0.f;

protected:
	CPopeBeam();
	CPopeBeam(const CPopeBeam& Obj);
	CPopeBeam(CPopeBeam&& Obj);
	virtual ~CPopeBeam();

	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CColliderAABB2D> mBeamCollider;
	//CSharedPtr<class CColliderSphere2D> mBody;
	class CAnimation2D* mAnimation = nullptr;

public:
	float GetBeamDmg() const
	{
		return mBeamDmg;
	}

	void SetBeamDmg(const float& BeamDmg)
	{
		mBeamDmg = BeamDmg;
	}

	void  SetBeamSkillCollisionProfile(const std::string& Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	virtual void CollisionBeam(const FVector3D& HitPoint, class CColliderBase* Dest);
private:
	void BeamHitOn();
	void BeamHitOff();
	void OnBeamEnd();
};

