#include "MonsterObject.h"
#include "BulletObject.h"
#include "ObjectSpawnPoint.h"

#include "../Component/StaticMeshComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/SpriteComponent.h"
#include "../Component/WidgetComponent.h"

#include "../Scene/Scene.h"
#include "../Share/Log.h"
#include "../Scene/SceneUIManager.h"

//문자열 
#include <sstream>

#include "../UI/UserWidget/HeadInfo.h"

CMonsterObject::CMonsterObject()
{
	mState = EMonsterState::Idle;
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)
	: CSceneObject(Obj)
{
	mState = EMonsterState::Idle;
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj)
	: CSceneObject(Obj)

{
	mState = EMonsterState::Idle;
}

CMonsterObject::~CMonsterObject()
{
}


void CMonsterObject::CollisionMonster(const FVector3D& HitPont, CColliderBase* Dest)
{
	//CLog::PrintLog("CollisionBegin");

	//Dest->GetProfile()->Channel == ECollisionChannel::PlayerAttack();
}

void CMonsterObject::CollisionMonsterEnd(class CColliderBase* Dest)
{
	//CLog::PrintLog("CollisionEnd");
}

void CMonsterObject::Idle(float DeltaTime)
{
}

void CMonsterObject::Recone(float DeltaTime)
{
}

void CMonsterObject::Research(float DeltaTime)
{
}

void CMonsterObject::Move(float DeltaTime)
{
}
void CMonsterObject::Attack(float DeltaTime)
{
}
float CMonsterObject::Damage(float Attack, CSceneObject* Obj)
{
	float Dmg = CSceneObject::Damage(Attack, Obj);

	mHP -= (int)Dmg;

	if (mHP <= 0)
	{
		if (mSpawnPoint != nullptr)
		{
			mSpawnPoint->ClearObject();
		}

		Destroy();
	}

	return Dmg;
}

bool CMonsterObject::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	//mRoot = CreateComponent<CStaticMeshComponent>();
	mRoot = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();
	//mBody = CreateComponent<CColliderOBB2D>();
	
	//콜라이더 체크용 
	//mMonsterMoveCollider = CreateComponent<CColliderAABB2D>();
	//mMonsterMoveCollider->SetBoxSize(35.f, 3.f);
	//mMonsterMoveCollider->SetRelativePos(0.f, -130.0f, 0.f);
	//mMonsterMoveCollider->SetCollisionProfile("Monster");
	//mRoot->AddChild(mMonsterMoveCollider);
	
//	체력바임 
	//CHeadInfo* Widget = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");
	//mWidgetCoponent = CreateComponent<CWidgetComponent>();
	//mWidgetCoponent->SetWidget(Widget);
	//mWidgetCoponent->SetWorldScale(1200.f, 200.f,0.1f);
	//mWidgetCoponent->SetWorldPos(0.f, -330.f);
	//mRoot->AddChild(mWidgetCoponent);

	//mRoot->SetTexture("Pope"); //수정해야할것같은데? 
	mRoot->SetPivot(0.5f, 0.5f);
//	mRoot->SetWorldScale(150.f, 200.f);
	//mRoot->SetFlip(true); // 반전시키는건 추후 고쳐야할듯 
	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(120.f, 180.f);
//	mBody->SetRadius(120.0f);
	mBody->SetCollisionProfile("Monster");
	mBody->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonster);
	mBody->SetCollisionEndFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonsterEnd);
//	mRoot->SetTexture("Pontiff");

	return true;
}

void CMonsterObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//if (!mTarget->IsActive())
	//{
	//	mTarget = nullptr;
	//	return; 
	//}
	//else if (mTarget->IsEnable())
	//{
	//	return;
	//}
	
	if (!mTarget)
	{
		
	}
	else
	{
		// 타겟이 죽었거나 비활성화면 끊기
		if (!mTarget->IsActive() || !mTarget->IsEnable())
		{
			mTarget = nullptr;
		}
	}
	//FSM
	//유한 상태 기계
	switch (mState)
	{
	case EMonsterState::Idle:
		Idle(DeltaTime);
		break;
	case EMonsterState::Recone:
		Recone(DeltaTime);
		break;
	case EMonsterState::Research:
		Research(DeltaTime);
		break;
	case EMonsterState::Move:
		Move(DeltaTime);
		break;
	case EMonsterState::Attack:
		Attack(DeltaTime);
		break;
	}

}