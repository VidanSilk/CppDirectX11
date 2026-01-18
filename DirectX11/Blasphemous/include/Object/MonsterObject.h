#pragma once
#include "SceneObject.h"

// 몬스터 오브젝트는 모든걸 관리함 
// 그럼 여기서 피격, 체력 관리, 콜라이더로 인식 필요
class CBackFloorTwo;

enum class EMonsterState
{
	Idle,
	Recone,
	Research,
	Move,
	Attack,
	End
};

class CMonsterObject : public CSceneObject
{
	friend class CScene;

protected:
	CMonsterObject();
	CMonsterObject(const CMonsterObject& Obj);
	CMonsterObject(CMonsterObject&& Obj);
	virtual ~CMonsterObject();

protected:
	//CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CSpriteComponent> mRoot;
	CSharedPtr<class CColliderAABB2D> mBody; //피격 몸통 콜라이더 
	//CSharedPtr<class CColliderSphere2D> mBody;
	//CSharedPtr<class CColliderOBB2D> mBody;
	CSharedPtr<class CColliderAABB2D> mBoundary; // 몬스터 경계 인식을 위한 콜라이더 
	CSharedPtr<CSceneObject> mTarget;
	//CSharedPtr<class CMovementComponent> mMovement; //몬스터 이동 범위

	//CSharedPtr<class CColliderAABB2D> mMonsterMoveCollider;
	class CBackFloorTwo* mBackFloorTwo = nullptr;

	//Widget Component -> 체력바 
	CSharedPtr<class CWidgetComponent> mWidgetCoponent;

	float mDetectDistance = 0.0f;

	//몬스터 체력 
	float mHP = 100.0f;

	//몬스터의 기본 공격력 
	float mMonsterATK = 10.0f; 

	EMonsterState mState;


private:
	void CollisionMonster(const FVector3D& HitPont, class CColliderBase* Dest);
	void CollisionMonsterEnd(class CColliderBase* Dest);

protected:
	//이건 일반 몬스터용으로 빼주면 좋을 것같음, 보스몹은 따로 
	virtual void Idle(float DeltaTime);
	virtual void Recone(float DeltaTime);
	virtual void Research(float DeltaTime);
	virtual void Move(float DeltaTime);
	virtual void Attack(float DeltaTime);

public:
	EMonsterState GetState() const
	{
		return mState;
	}

	void SetState(EMonsterState State)
	{
		mState = State;
	}

	void SetTarget(CSceneObject* Target)
	{
		mTarget = Target;
	}

	//CColliderAABB2D* GetMonsterMoveCollider() const {
	//	return mMonsterMoveCollider.Get();
	//}

	void SetBackFloorTwo(class CBackFloorTwo* Floor) {
		mBackFloorTwo = Floor;
	}

	virtual float Damage(float Attack, CSceneObject* Obj);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
};

