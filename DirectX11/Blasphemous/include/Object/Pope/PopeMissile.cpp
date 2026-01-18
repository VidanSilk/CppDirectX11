#include "PopeMissile.h"
#include "../SpriteEffect.h"
#include "../../Component/StaticMeshComponent.h"
#include "../../Component/MovementComponent.h"
#include "../../Component/ColliderAABB2D.h"
#include "../../Component/ColliderOBB2D.h"
#include "../../Component/ColliderSphere2D.h"
#include "../../Share/Log.h"
#include "../../Component/SpriteComponent.h"
#include "../../Scene/Scene.h"

CPopeMissile::CPopeMissile()
{
}

CPopeMissile::CPopeMissile(const CPopeMissile& Obj) : CBulletObject(Obj)
{
}

CPopeMissile::CPopeMissile(CPopeMissile&& Obj) : CBulletObject(Obj)
{
}

CPopeMissile::~CPopeMissile()
{
}

bool CPopeMissile::Init()
{
	if (!CBulletObject::Init()) return false;

	//mOBody = CreateComponent<CColliderAABB2D>();
    mOBody = CreateComponent<CColliderOBB2D>();
	SetBulletSpeed(120.f);
	
	if(mAnimation)	
	mAnimation->ChangeAnimation("pope_magicMissile"); 

	if (mMovement)
		mMovement->SetMoveSpeed(GetBulletSpeed());

	if (mOBody) {
		//충돌 결국 필요함  피격시 
		mRoot->AddChild(mOBody);
		mOBody->SetBoxSize(120.f, 30.f);
		mOBody->SetEnable(true);
		mOBody->SetCollisionProfile("MonsterAttack");
		mOBody->SetCollisionBeginFunc<CPopeMissile>(this, &CPopeMissile::CollisionBullet);
	}

	if (mMovement) {
		mMovement->SetUpdateComponent(mRoot);
		mMovement->SetMoveAxis(EAxis::X);
		mMovement->SetMoveSpeed(300.f);
	}

	return true;

}

void CPopeMissile::Update(float DeltaTime)
{
	CBulletObject::Update(DeltaTime);
}

void CPopeMissile::SetFireDir(bool bLeft)
{    // 1) 시각적 반전
    if (mRoot)
        mRoot->SetFlip(bLeft);

    // 2) 실제 이동 방향은 "속도 부호"로 결정 (가장 안전)
    if (mMovement)
    {
        float spd = GetBulletSpeed();
        if (spd < 0.f) spd = -spd;
        mMovement->SetMoveSpeed(bLeft ? -spd : spd);
    }

}

void CPopeMissile::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{
    if (!Dest) return;

    CSceneObject* owner = Dest->GetOwner();
    if (!owner) return;

    FCollisionProfile* prof = Dest->GetProfile();
    if (prof && prof->Name == "PlayerParry")
    {
        // ✅ 패링 성공 처리(너의 Combat 쪽 함수에 맞춰 호출)
        CPlayerObject* player = dynamic_cast<CPlayerObject*>(owner);
        if (player)
        {
            // 예: player->OnParrySuccess(this); 또는 player->GetCombat()->SetParrySuccess();
        }

        Destroy();
        return;
    }

    // 일반 피격
    owner->Damage(13.f, this);
    Destroy();
}