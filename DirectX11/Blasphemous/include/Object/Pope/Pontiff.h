#pragma once
#include "../MonsterObject.h"
#include "../../UI/UserWidget/PontiffDieWidget.h"
// 여기는 얼굴 (투구 x) 임 
// PontiffHead위에 올릴 예정이고, 
// 얼굴 뚜껑이 닫혀도 스킬은 시전 되어야함. 

class CPontiffHead;
class CPopeSymbol;

enum class EPontiffState {

	None,
	HeadOpen,
	OpeningIDLE,
	HeadClosing,
	Death

};

enum class EPontiffSkill
{
	None,
	PontiffFireBall,
	PontiffToxic,
	PontiffMissileP2,
	PontiffBeam
};

class CPontiffDieWidget;

class CPontiff : public CMonsterObject
{
	friend class CScene;

protected:
	CPontiff();
	CPontiff(const CPontiff& Obj);
	CPontiff(CPontiff&& Obj);
	virtual ~CPontiff();
	class CAnimation2D* mAnimation = nullptr;
	//	CSharedPtr<class CColliderSphere2D> mHeadBody;
	CSharedPtr<class CWidgetComponent> mWidgetCoponent;

private:
	CPontiffHead* mHead = nullptr;
	FVector3D      mAttachOffset = FVector3D(0.f, 100.f, 1.f);

	FVector2D mClosedScale = FVector2D(130.f, 130.f); // (필요시) 닫힘 상태 스케일
	FVector2D mOpenScale = FVector2D(130.f, 130.f); // (필요시) 열림 상태 스케일
	bool      mOpenedVisual = false;

	EPontiffState mState = EPontiffState::None;
	EPontiffSkill mPendingSkill = EPontiffSkill::None;

	bool  mIsCasting = false;
	bool  mCastTriggered = false;          // Notify 1회 발사 보호
	bool  mForceOpenForCast = false;

	// === Cooldown / Timing ===
	float mSkillAcc = 0.f;
	float mSkillInterval = 2.0f;

	float mOpenIdleAcc = 0.f;
	float mOpenIdleDuration = 7.0f;

	// 스탯
	float mPontiffHP = 100.f;
	float mPontiffATK = 12.0f;

	//캐스팅
	CSharedPtr<class CSceneComponent> mCastPoint;
	FVector3D mCastOffset = FVector3D(220.f, 40.f, 0.f);

	// === One-shot animation flags 
	bool mPlayedClosedIdle = false;
	bool mPlayedOpening = false;
	bool mPlayedOpenIdle = false;
	bool mPlayedCast = false;
	bool mPlayedClosing = false;
	bool mPlayedDeath = false;

	float mBeamDmg = 12.f;              // 빔 데미지
	bool  mBeamCenterPending = false;
	float mBeamCenterAcc = 0.f;
	float mBeamCenterDelay = 5.0f;
	// 빔 x좌표 
	float mBeamXLeft1 = -450.f;
	float mBeamXLeft2 = -300.f;
	float mBeamXRight1 = 250.f;
	float mBeamXRight2 = 400.f;
	//빔 바닥 
	float mBeamGroundY = 100.f;

	float mClosedIdleAcc = 0.f;
	float mClosedIdleDuration = 3.0f;   // 닫힌 채로 유지할 시간(원하는 값)

	// 스킬 관련 변수들 
	EPontiffSkill mNextSkillCycle = EPontiffSkill::PontiffFireBall;
	float mCastWindup = 0.2f;   // StartCast 후 몇 초 뒤 실제 발사
	float mCastAcc = 0.f;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual float Damage(float Attack, CSceneObject* Obj) override;

public:

	void SetHead(CPontiffHead* Head) { mHead = Head; }
	void SetAttachOffset(const FVector3D& Off) { mAttachOffset = Off; }

	bool IsDead() const { return mState == EPontiffState::Death; }

private:
	void OnPontiffHitBegin(const FVector3D& HitPoint, CColliderBase* Dest);
	void OnPontiffHitEnd(CColliderBase* Dest);


private:
	// === Core flow ===
	void ResetAnimFlags();

	EPontiffSkill DecideNextSkill();      // 다음 스킬 선택

	void StartCast(EPontiffSkill Skill, bool NeedOpenVisual); // 스킬 요청(닫혀도 가능)
	void CastNotify();                    // 애니 Notify 프레임에서 실제 발사(1회)


	// === State handlers ===
	void ClosedIdle(float DeltaTime);
	void HeadOpening();
	void OpenIdle(float DeltaTime);
	void HeadClosing();
	void Die();

	// === Animation callbacks ===
	void OnHeadOpenEnd();
	void OnHeadClosingEnd();

	// Skills 
	void CastFireBall();

	void CastToxic();
	void CastMissileP2();

	void CastBeam();
	void UpdateBeamDelay(float DeltaTime);
	void SpawnBeamAt(float x, float y, float z);
	
	CPontiffDieWidget* mDieWidget = nullptr;
	bool  mDeathStarted = false;
	bool mDieUIPlayed = false;
	bool  mDieUIWaiting = false;
	float mDieUIAcc = 0.f;
	float mDieUIDelay = 0.3f;

	float mDeathAnimAcc = 0.f;
	float mDeathAnimMinTime = 2.8f;   // ★ DEATH 애니가 3.0초면 2.8~3.0 추천
	bool  mDeathAnimEnded = false;

	void BeginDeath();
	void ShowDieWidget();
	void OnDeathAnimEnd();
	void UpdateDeathUIDelay(float DeltaTime);


};

