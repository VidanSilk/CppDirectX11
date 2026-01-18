#include "PopeFireBall.h"
#include "../SpriteEffect.h"
#include "../../Component/StaticMeshComponent.h"
#include "../../Component/MovementComponent.h"
#include "../../Component/ColliderAABB2D.h"
#include "../../Component/ColliderOBB2D.h"
#include "../../Component/ColliderSphere2D.h"
#include "../../Share/Log.h"
#include "../../Component/SpriteComponent.h"
#include "../../Scene/Scene.h"

//Explosion는 폭발 이펙트가 아니라, 발사할 때 

CPopeFireBall::CPopeFireBall()
{
}

CPopeFireBall::CPopeFireBall(const CPopeFireBall& Obj) : CBulletObject(Obj)
{
}

CPopeFireBall::CPopeFireBall(CPopeFireBall&& Obj) : CBulletObject(Obj)
{
	
}

CPopeFireBall::~CPopeFireBall()
{
}

//void CPopeFireBall::SetBulletCollisionProfile(const std::string& Name)
//{
//
//	mFireBody->SetCollisionProfile(Name);
//}

bool CPopeFireBall::Init()
{
	if (!CBulletObject::Init()) return false;

	mFireBody = CreateComponent<CColliderOBB2D>();
	//mFireBody = CreateComponent<CColliderAABB2D>();
	if (mAnimation)
	{
		mAnimation->ChangeAnimation("FireBall");
		mAnimation->SetEndFunction("FireEffect", this, &CPopeFireBall::OnFireEffectEnd);
	}

	SetBulletSpeed(500.f);

	if (mMovement)
	{
		mMovement->SetUpdateComponent(mRoot);  //  루트 기준으로 이동축 계산
		mMovement->SetMoveAxis(EAxis::X);      //  FireBall “오른쪽이 앞”이므로 X축
		mMovement->SetMoveSpeed(GetBulletSpeed());
	}

	if (mFireBody)
	{
		mRoot->AddChild(mFireBody);
		mFireBody->SetBoxSize(150.f, 40.f);
		mFireBody->SetEnable(true);
		mFireBody->SetCollisionProfile("MonsterAttack");
		mFireBody->SetCollisionBeginFunc<CPopeFireBall>(this, &CPopeFireBall::CollisionBullet);
	}

	return true;

}

void CPopeFireBall::Update(float DeltaTime)
{
	CBulletObject::Update(DeltaTime);
	
	if (mFireBody && mRoot) {
		mFireBody->SetWorldRotationZ(mRoot->GetWorldRotation().z);
	}

}

void CPopeFireBall::FireStartMotion()
{
	// 시작좌표는 x축 중 랜덤 위에서 메테오처럼 떨어짐. 
	//FVector3D startPos = mRoot->GetWorldPosition();
	CSpriteEffect* castEffect = mScene->CreateObj<CSpriteEffect>("FireBallCast");
	if (!castEffect) return;

	//  현재 FireBall 위치에서 이펙트 재생
	castEffect->SetWorldPos(GetWorldPosition());
	castEffect->SetAnimation("Explosion");
	castEffect->SetWorldScale(80.f, 80.f);

}

void CPopeFireBall::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest) {

	if (mExploded) return;          // 중복 충돌 방지
	mExploded = true;

	// 데미지 (원하면)
	if (Dest && Dest->GetOwner())
	{
		Dest->GetOwner()->Damage(10.f, this); // 수치/로직은 너 게임에 맞게
	}

	// 충돌/이동 끊기
	if (mFireBody) {
		mFireBody->SetEnable(false);
	}

	if (mMovement)
	{
	
		mMovement->SetMoveSpeed(0.f);
	}

	// 충돌 지점에 고정시키고(선택)
	SetWorldPos(HitPoint);

	// 폭발 이펙트 애니 재생
	if (mAnimation)
		mAnimation->ChangeAnimation("FireEffect");
	else
		Destroy(); // 애니 없으면 즉시 제거

}
// 파이어볼 움직임 
void CPopeFireBall::FiretoTarget(CPlayerObject* Player)
{
	//파이어볼이 타겟으로 움직임

}

void CPopeFireBall::OnFireEffectEnd()
{
	Destroy();
}
