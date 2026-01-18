#pragma once
#include "../MonsterObject.h"

//움직임 없어도됨 대신 순간이동 이 있음  
// appear vanishing을 이용한 이용 
// 캐스팅할 때 rgb 값으로 색상 입혀주면 될듯?

enum class EPopeState {
	PopeIdle,
	PopeAppear,
	PopeVanishing,
	PopeHitReaction,
	PopespellCast,
	PopeDeath,
	PopeFireBall,
	PopeToxic,
	PopeMissileP1,

};

class CPope : public CMonsterObject
{
	friend class CScene;

protected:
	CPope();
	CPope(const CPope& Obj);
	CPope(CPope&& Obj);
	virtual ~CPope();
	class CAnimation2D* mAnimation = nullptr;
	//CSharedPtr<class CColliderSphere2D> mPopeBody;
	CSharedPtr<class CWidgetComponent> mWidgetCoponent;
private:

	//캐스팅용 이펙트. 
	// 1. 심볼 
	class CPopeSymbol* mSymbol = nullptr;
	class CAnimation2D* mSymbolFXAni = nullptr;
	CSharedPtr<CSpriteComponent> mSymBolSprite;

	//2. 쉴드
	class CPopeSpellCasting* mSpellCast = nullptr;
	class CAnimation2D* mSpellAnim = nullptr;
	CSharedPtr<CSpriteComponent> mSpellSprite;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	
	bool IsDeathStarted() const { return mDeathStarted; }  
	virtual float Damage(float Attack, CSceneObject* Obj) override;

private:
	//교황의 움직임 
	void PopeIDLE();
	void PopeAppear();
	void PopeVanishing();
	void PopeHitReaction();
	float HitReaction(float Damage);
	void PopespellCast();
	void PopeDeath();
	void OnDeathAnimEnd();

	//텔레포트 
	void DecideTeleportThreshold();
	void OnVanishingEnd();
	void OnAppearEnd();
	void TeleportToEdgeRandom();

	//교황 스킬들
	void ApplyCastFxTint(); //캐스팅하는동안 색상 입히기 

	void FireBall();
	void CastFireBall();

	void StartFireBallPattern();
	void UpdateFireBallPattern(float DeltaTime);
	void SpawnFireBallAt(float x, float y);
	//void FinishSkillCycle();

	//독탄
	void Toxic();
	void CastToxic();

	//미사일 
	//좌표
	void MisiileP1(float DeltaTime);
	void CastMissile();
	void StartMissilePattern();              // 캐스팅 끝나고 호출
	void UpdateMissilePattern(float DeltaTime);
	void SpawnMissile(const FVector3D& pos); // 기존 SpawnMissile를 함수로 빼두면 편함

	//스킬 캐스팅하는동안 발동 
	void ActiveSkill();
	void OnSpellCastEnd();

	bool mGoScene2OnDeath = false;

public:
	void DebugDieAndGoScene2(float DeltaTime);   // U키 바인딩용 (시그니처는 Input에 맞춰 float)
	void BeginDeath();
	//void GoScene2();                              // 씬 전환 실제 호출부


//교황 기본상태와 관련된 멤버 변수
private:
	//교황 1페이즈용 스텟 
	// 교황 체력 
	float mPopeHp = 30.0f;
	// 발사체 투여 시간 (파이어볼, 독성)
	//스킬 데미지는 ATK x 1.2배로 
	float mPopeATK = 5.0f;
	EPopeState mPopeDefault = EPopeState::PopeIdle; //기본 상태값 
	//죽음 체크용
	bool mDeathStarted = false;
	
	// 스킬 관련 변수들 
	float mSkillBallInterval = 3.0f;   
	float mPopeSkillCoolTime = 0.0f;   // 쿨타임 
	//스킬 타이밍
	EPopeState mNextSkill = EPopeState::PopeMissileP1;
	bool mIsCasting = false;
	bool mSpellAnimStarted = false; 

//여긴 텔포관련 멤버 변수들 
private:
	// 스킬 2~3번 후 텔포
	int  mSkillUseCount = 0;
	int  mTeleportThreshold = 2;   // 2 또는 3
	bool mFirstAppear = true;

	// 위치  	
	float mTeleportLX = -480.f;
	float mTeleportRX = 500.f;
	float mTeleportY = -175.f; //Y축 좌표는 고정

	//파이어볼 관련 멤버 변수들 
private: 
	bool  mFireBallPattern = false;

	int   mFireBallPosIdx = 0;      // 0:A, 1:B, 2:C
	int   mFireBallShotIdx = 0;     // 0~2 (같은 좌표에서 3발)

	float mFireBallAcc = 0.f;
	float mFireBallShotInterval = 0.6f;  // 같은 좌표에서 발사 간격(원하는 값)
	float mFireBallNextPosDelay = 0.35f;  // 좌표 바꾸기 전 텀(원하는 값)
	bool  mFireBallWaitingNextPos = false;

	float mFireBallY = 300.f;
	float mFireBallPosX[3] = { 300.f, 150.f, -100.f };
//	float mFireBallPosX[5] = { -300.f, 150.f, 0.f, 150.f, 300.f }; // x축 좌표 지정 


//Toxic관련 멤버변수들 
private:

	// Toxic 6연사(0.5초 간격, y 고정, x만 변경)
	bool  mToxicBurst = false;
	int   mToxicShotIndex = 0;
	int   mToxicTotalShots = 6;
	float mToxicAcc = 0.f;
	float mToxicInterval = 0.5f;

	float mToxicY = 300.f;
	float mToxicStartX = -250.f;
	float mToxicSpacing = 100.f;

//미사일 관련 멤버 변수들
private:

	// 미사일 패턴(위->아래 1초 간격)
	bool  mMissilePattern = false;
	float mMissileAcc = 0.f;
	float mMissileInterval = 1.f;   // pos1 후 1초 뒤 pos2
	int   mMissileStep = 0;         // 0: pos1, 1: pos2
	bool  mMissileLeft = false;     // 캐스팅 시작 시점의 포프 방향(왼쪽인지)
	FVector3D mMissilePos1;
	FVector3D mMissilePos2;


};

