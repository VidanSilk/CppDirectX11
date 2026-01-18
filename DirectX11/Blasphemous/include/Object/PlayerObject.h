#pragma once
#include "SceneObject.h"

//반드시 필요한 기능은 클래스로 나누고
// 여기서 처리가능한 기능은 멤버변수로 처리하기 
// 그리고 이동 무브먼트는 이동처리를 담당해야하니, 플레이어 무브를 나누고
// 회복 죽음은 멤버변수로 피격 모드도 추가

class CBackFloorTwo;
class CAshFloor;
class CAshPlatform;
class CColliderBase;

enum class  PlayerState {
	Idle = 1,
	Move,	// 뛰는게 기본 모션  bool 값 추가해서 참인지 거짓인지 따라 바꾸기 
	Jump,	// 제자리 점프, 앞으로 뛰면서 점프, 하단 점프로 나뉨 그리고 PlayerMove에서 구현 
	ATK,	// 콤보 공격 존재
	UpATK,	// 위로 공격 (A)
	Parry,	// 막았을 때 성공하고 밀어나기 + 실패시 
	HPRecovery, // 회복 모션
	Dodge,	//회피 모션 ? 
	PlayerSkill, // 스킬 에너지파 
	FallingDown, // 피격 -> 넉다운
	KnockBack, // (패링 성공 등) 넉백
	GettingUp,
	PlayerHitMotion, // (보류) 단순 피격 모션 
	Death
};

class CPlayerObject : public CSceneObject {

private:
	// 선언 당한 쪽에서 선언한 쪽에 접근할 수 있게 해준다. 
	friend class CScene;
	friend class CPlayerFallingDown;

protected:

	CPlayerObject();
	CPlayerObject(const CPlayerObject& Obj);
	CPlayerObject(CPlayerObject&& Obj);
	virtual ~CPlayerObject();

protected:
	//충돌 및 애니메이션 등록 
	//기본 스프라이트 
	CSharedPtr<class CSpriteComponent> mRoot; //몸통 
	CSharedPtr<class CColliderAABB2D> mBody; // 히트박스  콜라이더
	
	//공격 콜라이더 
	CSharedPtr<class CColliderAABB2D> mATKCollider; 
	CSharedPtr<class CColliderAABB2D> mUPATKCollider;
	CSharedPtr<class CColliderAABB2D> mParryCollider;

	//MovementComponent 이동 관련 
	CSharedPtr<class CMovementComponent> mMovement; 
	CSharedPtr<class CColliderAABB2D> mMoveCollider;
	CSharedPtr<class CGravityComponent> mGravity;

	//애니메이션
	// 기본 
	class CAnimation2D* mAnimation = nullptr; // 본체 
	
	// 회복관련 애니메이션 
	CSharedPtr<CSpriteComponent> mHealFXSprite;
	class CAnimation2D* mHealFXAnim = nullptr;

	// 스킬 관련  애니메이션 
//	CSharedPtr<CSpriteComponent> mSkillMotion;
	//class CAnimation2D* mSkillMotionAnim = nullptr;
	CSharedPtr<CSpriteComponent> mSkillBeamSprite;  
	class CAnimation2D* mSkillBeamAnim = nullptr;        
	CSharedPtr<class CColliderAABB2D> mSkillCollider;

	//바닥 충돌관련 
	class CBackFloorTwo* mBackFloorTwo = nullptr;
	class CAshFloor* mAshFloor = nullptr;
	std::vector<CAshPlatform*> mAshPlatforms;

	// 기본 멤버 변수 
private:
	//기본 상태 
	bool mAutoBasePose = true;
	PlayerState mDefault = PlayerState::Idle;
	
	// 공격 데미지
	float mPlayerDMG = 100.f;

	//점프 
	int  mJumpDir = 0;           // -1: left, 1: right, 0: vertical
	bool  mWasGrounded = true; //중력 체크 
	int  mLastMoveDir = 0;     // -1: left, 1: right (MoveLeft/Right에서 갱신)
	bool mLanding = false;     // JumpLand 애니 재생 중인지

	// 회피 
	int   mDodgeDir = 0;          // -1 / 1
	float mDodgeTime = 0.f;
	float mDodgeDuration = 0.3f;
	float mBaseMoveSpeed = 300.f;
	float mDodgeSpeedMul = 3.5f; //배수로
	float   mDodgeDistance = 300.f;     
	float   mDodgeStartX = 0.f;
	float   mDodgeTargetX = 0.f;

	// 넉백
	float mKnockBackDistance = 130.f;   // 100~150
	float mKnockBackDuration = 0.10f;   // 짧게 (순간이동 느낌)
	float mKnockBackTime = 0.f;
	float mKnockBackStartX = 0.f;
	float mKnockBackTargetX = 0.f;
	bool  mKnockBacking = false;

	// HP 관련 변수
	float mMaxHp = 100.0f; //플레이어 최대 체력
	float mNowHp = 100.0f; //플레리어의 현재 체력 
	float mHpRecovery = 25.0f; //회복량
	
	// has-a 관계 친구들 
	// 여기는 플레이어와 관련된 것들을 담아 줄 것이다. 
	// 하지만 꼭 나눠야할건 나눌것이다. 
	class CPlayerMove* mMove = nullptr;
	class CPlayerCombat* mCombat = nullptr;
	class CPlayerSkill* mSkill = nullptr;
	class CPlayerHealEffect* mHeal = nullptr;
	class CPlayerFallingDown* mFallingDown = nullptr;

	//프로세스 추가 
	class CProgressBar* mHPBar = nullptr;

	bool mDieUIShown = false;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual float Damage(float Attack, CSceneObject* Obj) override;
	void Damage(float Damage); 

	CColliderAABB2D* GetPlayerMoveCollider() const {
		return mMoveCollider.Get();
	}

	void SetBackFloorTwo(class CBackFloorTwo* Floor) { 
		mBackFloorTwo = Floor; 
	}
	
	void SetBackAshFloor(class CAshFloor* Floor) {
		mAshFloor = Floor;
	}

	void AddBackPlatform(CAshPlatform* Plat)
	{
		if (Plat) mAshPlatforms.push_back(Plat);
	}

	class CGravityComponent* GetGravity() const { 
		return mGravity.Get(); 
	}

private:
	//이동 관련로직 PlayerMove
	 void MoveLeft(float DeltaTime);
	 void MoveRight(float DeltaTime);
	void StartDodge(int dir);
	void DodgeLeft(float DeltaTime);
	void DodgeRight(float DeltaTime);
	void UpdateDodge(float DeltaTime);
	void DodgeEnd();

	//점프 관련 함수 PlayerJump
	void Jump(float DeltaTime); // 기본 점프 
	void JumpForward(float DeltaTime); //앞으로 점프
	void JumpDown(float DeltaTime); // 밑으로 점프 
	void JumpLandEnd();

	//전투 로직 일반 공격 PlayerCombat
	void Attack(float DeltaTime);
	void AttackEnd();
	void AttackNotify();
	void OnAttackHit(CSceneObject* Other);
	void UpATK(float DeltaTime); //윗 공격 
	void UpATKNotify();
	
	void DodgeATK(float DeltaTime); //대쉬 공격 
	void DodgeATKNotify();

	void ParryCounter(float DeltaTime);
	void ParryBack(float DeltaTime); //패링 빽 
	void ParryEnd();
	void ParryBackEnd();
	void StartKnockBack(int dir, float dist);
	void UpdateKnockBack(float DeltaTime);
	// 스킬 로직 -> PlayerSkill

	void BeamSkill(float DeltaTime);
	void BeamSkillNotify();
	void BeamSkillEnd();

	//회복 관련 로직 -> 완성  PlayerHeal
	void HPrecovery(float DeltaTime);
	void HPEffectNotify();
	void HPRecoveryEnd();

	// 죽는거 완성 -> 피봇 맞추면 됨 
	void PlayerDeath(float DeltaTime);

	// 공격 콜백 
	void OnPlayerAttackColliderHit(const FVector3D& HitPoint, CColliderBase* Dest);
	void OnPlayerSkillColliderHit(const FVector3D& HitPoint, CColliderBase* Dest);
	//패링 콜백 
	void OnPlayerParryColliderHit(const FVector3D& HitPoint, CColliderBase* Dest);
	void FallingOverEnd();
	void GettingUpEnd();
};

