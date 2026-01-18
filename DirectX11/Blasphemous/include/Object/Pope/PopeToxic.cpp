#include "PopeToxic.h"
#include "../SpriteEffect.h"
#include "../../Component/StaticMeshComponent.h"
#include "../../Component/MovementComponent.h"
#include "../../Component/ColliderAABB2D.h"
#include "../../Component/ColliderOBB2D.h"
#include "../../Component/ColliderSphere2D.h"
#include "../../Share/Log.h"
#include "../../Component/SpriteComponent.h"
#include "../../Scene/Scene.h"


CPopeToxic::CPopeToxic()
{
}

CPopeToxic::CPopeToxic(const CPopeToxic& Obj) : CBulletObject(Obj) 
{
}

CPopeToxic::CPopeToxic(CPopeToxic&& Obj) : CBulletObject(Obj)
{
}

CPopeToxic::~CPopeToxic()
{
}

bool CPopeToxic::Init()
{
	CBulletObject::Init();
	if (!CBulletObject::Init()) return false;

	mToxicBody = CreateComponent<CColliderSphere2D>();

	if (mAnimation)
	mAnimation->ChangeAnimation("pope_toxicOrb"); 

	if (mMovement)
		mMovement->SetMoveSpeed(GetBulletSpeed());

	if (mToxicBody) {
		mRoot->AddChild(mToxicBody);
		mToxicBody->SetRadius(50.0f);
		mToxicBody->SetEnable(true);
		mToxicBody->SetCollisionProfile("MonsterAttack");
		mToxicBody->SetCollisionBeginFunc<CPopeToxic>(this, &CPopeToxic::CollisionBullet);
	}
	return true;
}

void CPopeToxic::Update(float DeltaTime)
{
	CBulletObject::Update(DeltaTime);
}



void CPopeToxic::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{	
	
	Dest->GetOwner()->Damage(9.0f, this);

	CSpriteEffect* TEffect = mScene->CreateObj<CSpriteEffect>("ToxicEffect");
	TEffect->SetAnimation("Pope_toxicCloud");
	TEffect->SetWorldPos(HitPoint);
	TEffect->SetWorldScale(101.f, 105.f);
	Destroy();
}
