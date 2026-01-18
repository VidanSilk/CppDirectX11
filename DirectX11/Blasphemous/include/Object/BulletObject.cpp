#include "BulletObject.h"

#include "SpriteEffect.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Share/Log.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Animation/Animation2D.h"

CBulletObject::CBulletObject()
	:CSceneObject()
{
}

CBulletObject::CBulletObject(const CBulletObject& Obj)
	:CSceneObject(Obj)
{
}

CBulletObject::CBulletObject(CBulletObject&& Obj)
	:CSceneObject(Obj)
{
}

CBulletObject::~CBulletObject()
{
}

void CBulletObject::SetBulletCollisionProfile(const std::string& Name)
{
	
//	mBody->SetCollisionProfile(Name);
}


bool CBulletObject::Init()
{
	CSceneObject::Init();

	mRoot = CreateComponent<CSpriteComponent>();
	//mBody = CreateComponent<CColliderAABB2D>();
	//mBody = CreateComponent<CColliderOBB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();
	mMovement = CreateComponent<CMovementComponent>();
	
	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	
	mAnimation->AddSequence("FireBall", 2.0f, 1.0f, true, false);
	mAnimation->AddSequence("Explosion", 1.25f, 1.0f, true, false);
	mAnimation->AddSequence("FireEffect", 1.0f, 1.0f, false, false);
	mAnimation->AddSequence("pope_toxicOrb", 1.0f, 0.7f, true, false);
	mAnimation->AddSequence("Pope_toxicCloud", 1.0f, 1.2f, true, false);
	
	mAnimation->AddSequence("pope_magicMissile", 1.0f, 1.0f, true, true);
	mAnimation->AddSequence("pope_magicMissileFXS", 1.0f, 1.0f, true, true);

	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetWorldScale(0.5f, 0.5f, 1.f);
	
	SetRootComponent(mRoot);

	// 자식들에서 철 ㅣ
	//mRoot->AddChild(mBody);
	//mBody->SetBoxSize(50.f, 50.f);
	//mBody->SetRadius(75.0f);
	//mBody->SetEnable(true);
	//mBody->SetCollisionProfile("MosterAttack");
	//mBody->SetCollisionBeginFunc<CBulletObject>(this, &CBulletObject::CollisionBullet);

	//Movement 셋팅 기본값으로 
	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::Y); 
	mMovement->SetMoveSpeed(300.f);


	return true;
}

void CBulletObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//FVector3D Pos = mRoot->GetWorldPosition();
	////이동할 위치의 새로운 위치값 = 내 위치 + 내Y축 * 속도 * DeltaTime 
	//mRoot->SetWorldPos(Pos + mRootComponent->GetAxis(EAxis::Y) * mSpeed * DeltaTime); 

}

void CBulletObject::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{
	//CLog::PrintLog("Bullet Hit Collision", ELogPrintType::All);

	//Dest->GetOwner()->Damage(1.f, this);

	//CSpriteEffect* Effect = mScene->CreateObj<CSpriteEffect>("HitEffect");

	//Effect->SetAnimation("Explosion");
	//Effect->SetWorldPos(HitPoint);
	//Effect->SetWorldScale(300.f, 300.f);

	//여기서도 독뎀일 경우만 이펙트 만들어주면됨 

	//if (mSkillType == EPopeSkillType::ToxicOrb) {
	//	CSpriteEffect* TEffect = mScene->CreateObj<CSpriteEffect>("ToxicEffect");

	//	TEffect->SetAnimation("Pope_toxicCloud");
	//	TEffect->SetWorldPos(HitPoint);
	//	TEffect->SetWorldScale(200.f, 200.f);
	//
	//}
	//Destroy();
}

