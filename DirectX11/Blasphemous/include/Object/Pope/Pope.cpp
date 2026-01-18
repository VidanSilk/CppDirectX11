#include "Pope.h"
#include "PopeFireBall.h"
#include "PopeToxic.h"
#include "PopeMissile.h"
#include "PopeSymbol.h"
#include "PopeSpellCasting.h"

#include "../BulletObject.h"
#include "../PlayerObject.h"

#include "../../Scene/Scene.h"
#include "../../Scene/Input.h"
#include "../../Scene/SceneMain2.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Component/StaticMeshComponent.h"
#include "../../Component/SpriteComponent.h"
#include "../../Vector3D.h"

#include "../../UI/UserWidget/PopeUIInfo.h"
#include "../../Component/WidgetComponent.h"

//교황 패턴 입혀주기 
static float RadToDeg(float r) { return r * 180.f / 3.141f; }

CPope::CPope()
{
	mSymbol = new CPopeSymbol;
	mSpellCast = new CPopeSpellCasting;
}

CPope::CPope(const CPope& Obj) : CMonsterObject(Obj)
{
}

CPope::CPope(CPope&& Obj) : CMonsterObject(Obj)
{
}

CPope::~CPope() 
{
	SAFE_DELETE(mSymbol);
	SAFE_DELETE(mSpellCast);
}

bool CPope::Init()
{
	if (!CMonsterObject::Init())
	{
		return false;
	}
	
	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("pope_idle", 1.0f, 1.0f, true, false);
	mAnimation->AddSequence("pope_appear", 1.0f, 1.0f, false, false);
	mAnimation->AddSequence("pope_vanishing", 1.0f, 1.0f, false, false);
	mAnimation->AddSequence("pope_hitReaction", 1.0f, 1.0f, false, false);
	mAnimation->AddSequence("pope_spellCast", 2.0f, 1.0f, false, false);
	mAnimation->AddSequence("pope_spellCast_FXS", 3.0f, 1.0f, false, false);
	mAnimation->AddSequence("pope_death", 3.5f, 1.0f, false, false);
	mAnimation->AddSequence("pope_twistedOne_symbol", 3.0f, 1.0f, false, false);

	mRoot->SetWorldScale(200.f, 250.f);
	mRoot->SetTexture("Pope");

	mPopeDefault = EPopeState::PopeAppear; //첫등장은 appper로 등장해야함
	if (mAnimation) {
		//mAnimation->SetEndFunction("pope_appear", this, &CPope::PopeIDLE);
        mAnimation->SetEndFunction("pope_spellCast", this,& CPope::OnSpellCastEnd);
		mAnimation->SetEndFunction("pope_appear", this, &CPope::OnAppearEnd);
		mAnimation->SetEndFunction("pope_vanishing", this, &CPope::OnVanishingEnd);
	}

	SetTarget(mScene->FindObjectFromType<CPlayerObject>());
	
	//순간이동 
	DecideTeleportThreshold();
	mSkillUseCount = 0;
	mFirstAppear = true;

	//첫 등장 장소
	mRoot->SetWorldPos(mTeleportLX, mTeleportY);

	// 스킬 스폰 위치들
	// 스킬 심볼 mSymbolFXAni , mSymBolSprite

	mSymBolSprite = CreateComponent<CSpriteComponent>();
	mSymbolFXAni = mSymBolSprite->CreateAnimation2D<CAnimation2D>();
	mRoot->AddChild(mSymBolSprite);
	
	//테스트용인데 아마 캐스팅맞다 색상 바꿔줘야할 꺼임 
	mSymBolSprite->SetPivot(-0.6f, 0.f);
	mSymBolSprite->SetRelativePos(0.f, 30.f);
	mSymBolSprite->SetRelativeScale(0.5f, 0.5f);
	mSymBolSprite->SetEnable(false);
	mSymBolSprite->SetOpacity(1.0f);
	mSymBolSprite->SetTint(1.f, 1.f,1.f);
	mSymbol->Bind(mSymBolSprite, mSymbolFXAni);
	mSymbol->Setup();

	//스킬 쉴드? fxs - mSpellCast
	//2. 쉴드 mSpellCast, mSpellAnim, mSpellSprite;
	// 티트 값은 스킬에 맞게 변경해줄것 
	mSpellSprite = CreateComponent<CSpriteComponent>();
	mSpellAnim = mSpellSprite->CreateAnimation2D<CAnimation2D>();
	mRoot->AddChild(mSpellSprite);
	mSpellSprite->SetPivot(0.5f, 0.375f);
	mSpellSprite->SetRelativePos(0.f, 0.f,0.4f);
	mSpellSprite->SetRelativeScale(1.2f, 1.4f);
	mSpellSprite->SetEnable(false);
	mSpellSprite->SetOpacity(1.0f);
	mSpellSprite->SetTint(1.f, 1.f, 1.f);
	mSpellCast->Bind(mSpellSprite, mSpellAnim);
	mSpellCast->Setup();

	mDetectDistance = 400.f;

	CPopeUIInfo* Widget = mScene->GetUIManager()->CreateWidget<CPopeUIInfo>("CPopeUIInfo");
	mWidgetCoponent = CreateComponent<CWidgetComponent>();
//	mScene->GetUIManager()->AddToViewport(Widget);
	mWidgetCoponent->SetWidget(Widget);
	mWidgetCoponent->SetWorldScale(1200.f, 200.f, 0.1f);
	mWidgetCoponent->SetWorldPos(0.f, -330.f);
	mRoot->AddChild(mWidgetCoponent);



    return true;
}

void CPope::Update(float DeltaTime)
{
	CMonsterObject::Update(DeltaTime);
	mPopeSkillCoolTime += DeltaTime;
	//쿨타임 발동 
	if (!mIsCasting && mPopeSkillCoolTime >= mSkillBallInterval)
	{
		mPopeSkillCoolTime = 0.f;
		mPopeDefault = EPopeState::PopespellCast;
		mIsCasting = true;
	}

	switch (mPopeDefault)
	{
	case EPopeState::PopeIdle:
		mAnimation->ChangeAnimation("pope_idle");
		break;
	case EPopeState::PopeAppear:
		PopeAppear();
		break;
	case EPopeState::PopeVanishing:
		PopeVanishing();
		break;
	case EPopeState::PopeHitReaction:
		PopeHitReaction();
		break;
	case EPopeState::PopespellCast:
		PopespellCast();
		if (mNextSkill == EPopeState::PopeFireBall) UpdateFireBallPattern(DeltaTime);
		if (mNextSkill == EPopeState::PopeMissileP1) MisiileP1(DeltaTime);
		break;
	case EPopeState::PopeDeath:
		PopeDeath();
		break;
	default:
		break;
	}

	// 교황의 시점은 항상 플레이어에게 향하게
	if (mTarget)
	{
		// 죽었거나 비활성/비표시 상태면 타겟 해제
		if (!mTarget->IsActive())
		{
			mTarget = nullptr;
		}
		else if (mTarget->IsEnable())
		{
			const float popeX = GetWorldPosition().x;
			const float targetX = mTarget->GetWorldPosition().x;

			// 타겟이 왼쪽이면 flip = true (반대로 보이면 조건만 뒤집어)
			mRoot->SetFlip(targetX < popeX);
		}
	}

}

float CPope::Damage(float Attack, CSceneObject* Obj)
{
	// 이미 죽는 중이면 추가 피격 무시
	if (mDeathStarted)
		return 0.f;

	// SceneObject의 Damage만 사용 (무적 처리 등)
	float Dmg = CSceneObject::Damage(Attack, Obj);
	if (Dmg <= 0.f)
		return 0.f;

	// CPope 전용 HP로 깎기
	mPopeHp -= Dmg;

	// 혹시 씬/위젯/기존 코드가 mHP를 보고 있을 수도 있으니 동기화(추천)
	mHP = mPopeHp;

	if (mPopeHp <= 0.f)
	{
		mPopeHp = 0.f;
		mHP = 0.f;
		BeginDeath();        // 여기서 pope_death 재생 + 끝나면 Destroy()
		return Dmg;
	}

	// 피격 애니(원하면)
	mPopeDefault = EPopeState::PopeHitReaction;
	if (mAnimation)
		mAnimation->ChangeAnimation("pope_hitReaction");

	return Dmg;
}

void CPope::PopeIDLE()
{
	mPopeDefault = EPopeState::PopeIdle;
}

void CPope::PopeAppear()
{
	// 첫 등장 후 
	//맵의 끝과 끝에서 등장함 
	if (!mAnimation) return;
	//첫 등장시에는 좌표 고정, 그후 사라진 이후 랜덤한 좌표에
	mAnimation->ChangeAnimation("pope_appear");

}

void CPope::PopeVanishing()
{
	//사리지고 순간이동을 한다 
	mAnimation->ChangeAnimation("pope_vanishing");

}
//호출용 - 업데이트용 
void CPope::PopeHitReaction()
{
	//델타타임 넣으면 안됨 다른거 넣어야함 임시르 넣어줌 
	//HitReaction(플레이어 부터 받은 데미지를 넣어주면됨.);
	//mAnimation->SetEndFunction("pope_appear", this, &CPope::PopeIDLE);
}

float CPope::HitReaction(float Damage)
{
	mPopeHp -= Damage;

	if (mPopeHp <= 0.f)
	{
		mPopeHp = 0.f;
		BeginDeath();    
		return mPopeHp;
	}

	mAnimation->ChangeAnimation("pope_hitReaction");
	return mPopeHp;
}

void CPope::PopespellCast()
{
	if (!mAnimation) return;
	mAnimation->ChangeAnimation("pope_spellCast");
	
	ApplyCastFxTint();
	
	if (!mSpellCast) return;
	mSpellSprite->SetEnable(true);
	mSpellCast->Play(mRoot->GetIsFlip());
	
	if (!mSpellCast) return;
	mSymBolSprite->SetEnable(true);
	mSymbol->Play(mRoot->GetIsFlip());

	//mAnimation->SetEndFunction("pope_appear", this, &CPope::PopeIDLE);
}

void CPope::PopeDeath()
{
	//if (!mAnimation) return;

	////  이미 죽음 애니 시작했으면 또 바꾸지 않기
	//static bool started = false;
	//if (!started)
	//{
	//	started = true;
	//	mAnimation->ChangeAnimation("pope_death");
	//}

}

void CPope::OnDeathAnimEnd()
{
	
	Destroy();
}

void CPope::DecideTeleportThreshold()
{
	//스킬은 2번 아니면 3번 
	mTeleportThreshold = 2 + (rand() % 2); // 2 or 3
}

void CPope::OnVanishingEnd()
{
	TeleportToEdgeRandom();
	//순간이동후에도 타겟 잡기 
	if (mTarget && mTarget->IsEnable()) {
		mRoot->SetFlip(mTarget->GetWorldPosition().x < GetWorldPosition().x);
	}
	// 이동 후 등장
	mPopeDefault = EPopeState::PopeAppear;

}

void CPope::OnAppearEnd()
{
	mIsCasting = false;
	mPopeSkillCoolTime = 0.f;      // 등장 직후 바로 캐스팅 방지(선택이지만 추천)

	// 텔포 사이클 초기화
	mSkillUseCount = 0;
	DecideTeleportThreshold();

	mFirstAppear = false;
	mPopeDefault = EPopeState::PopeIdle;

}

//텔레포트
void CPope::TeleportToEdgeRandom()
{
	const bool left = (rand() % 2) == 0;
	const float x = left ? mTeleportLX : mTeleportRX;
	mRoot->SetWorldPos(x, mTeleportY);
}

//casting 색상을 바꿔준다. 
void CPope::ApplyCastFxTint()
{
	float Red = 1.f, Green = 1.f, Blue = 1.f;

	switch (mNextSkill)
	{
	case EPopeState::PopeFireBall:  Red = 1.f;  Green = 1.f; Blue = 1.f; break; // 노랑색
	case EPopeState::PopeToxic:     Red = 0.565f; Green = 1.83f;  Blue = 1.03f; break; // 연두색
	case EPopeState::PopeMissileP1: Red = 2.33f; Green = 0.51f; Blue = 3.11f; break; // 퍼블색0.933, 0.510, 0.933
	default: break;
	}

	if (mSymBolSprite)
	{
		mSymBolSprite->SetTint(Red, Green, Blue);
	}

	if (mSpellSprite) { 
		mSpellSprite->SetTint(Red, Green, Blue); 
	}
}

void CPope::FireBall()
{
	//mPopeSkillCoolTime += DeltaTime;
	//if (mPopeSkillCoolTime >= mSkillBallInterval) {
		CastFireBall();
		//mPopeSkillCoolTime = 0.0f;
	//}
	mPopeDefault = EPopeState::PopeIdle;
}

void CPope::CastFireBall()
{   
	if (!mTarget) return;
	if (!mTarget->IsEnable()) return;

	const FVector3D playerPos = mTarget->GetWorldPosition();

	//  Toxic처럼 "위에서 발사" (상단 y 고정)
	const float y = 300.f;

	//  포프 기준 3발(좌우로 약간 벌려서) — 값은 취향대로 조절
	const float popeX = mRoot->GetWorldPosition().x;
	const float offsets[3] = { -80.f, 0.f, 80.f };

	for (int i = 0; i < 7; ++i)
	{
		CPopeFireBall* Firebullet = mScene->CreateObj<CPopeFireBall>("PopeFireBall");
		if (!Firebullet) continue;

		const float x = popeX + offsets[i];

		Firebullet->SetWorldPos(x, y);
		Firebullet->SetBulletSpeed(350.f);
		Firebullet->SetBulletCollisionProfile("MonsterAttack");
		Firebullet->SetWorldScale(80.f, 50.f);

		// 조준(각 탄의 시작 위치 기준)
		const FVector3D startPos = Firebullet->GetWorldPosition();
		FVector3D dir = playerPos - startPos;

		const float len2 = dir.x * dir.x + dir.y * dir.y;
		if (len2 < 0.001f) continue;

		dir.Normalize();

		// Toxic에서 쓰던 방식 그대로 (MoveAxis = Y 기준)
		float angleDeg = -RadToDeg(atan2f(dir.x, dir.y));
		Firebullet->SetWorldRotationZ(angleDeg);
	
		// 발사 FX (탄 위치 기준으로 나오게 아래에서 수정)
		Firebullet->FireStartMotion();
	}
}

void CPope::StartFireBallPattern()
{
	mFireBallPattern = true;
	mFireBallPosIdx = 0;
	mFireBallShotIdx = 0;
	mFireBallAcc = mFireBallShotInterval;  // 시작하자마자 1발
	mFireBallWaitingNextPos = false;
}

void CPope::UpdateFireBallPattern(float DeltaTime)
{
	if (!mFireBallPattern) return;
	if (!mIsCasting) return;

	mFireBallAcc += DeltaTime;

	// 다음 좌표로 넘어가기 
	if (mFireBallWaitingNextPos)
	{
		if (mFireBallAcc < mFireBallNextPosDelay) return;

		mFireBallAcc = 0.f;
		mFireBallWaitingNextPos = false;
		mFireBallShotIdx = 0;
		mFireBallPosIdx++;

		// 모든 좌표(A,B,C) 끝
		if (mFireBallPosIdx >= 3)
		{
			mFireBallPattern = false;
			//FinishSkillCycle();
		}

		return;
	}

	// 같은 좌표에서 1발씩 3번 발사
	if (mFireBallAcc < mFireBallShotInterval) return;
	mFireBallAcc = 0.f;

	const float x = mFireBallPosX[mFireBallPosIdx];
	const float y = mFireBallY;

	SpawnFireBallAt(x, y);     //  한 발만

	mFireBallShotIdx++;

	// 3발 다 쐈으면 다음 좌표로 넘어가기 대기
	if (mFireBallShotIdx >= 3)
	{
		mFireBallWaitingNextPos = true;
		// 다음 좌표 넘어가기 텀을 재기 시작
		mFireBallAcc = 0.f;
	}
}

void CPope::SpawnFireBallAt(float x, float y)
{
	if (!mTarget) return;
	if (!mTarget->IsEnable()) return;

	CPopeFireBall* b = mScene->CreateObj<CPopeFireBall>("PopeFireBall");
	if (!b) return;

	b->SetWorldPos(x, y);
	b->SetBulletSpeed(350.f);
	b->SetBulletCollisionProfile("MonsterAttack");
	b->SetWorldScale(200.f,120.f);

	// 조준
	const FVector3D playerPos = mTarget->GetWorldPosition();
	const FVector3D startPos = b->GetWorldPosition();
	FVector3D dir = playerPos - startPos;

	const float len2 = dir.x * dir.x + dir.y * dir.y;
	if (len2 < 0.001f) return;

	dir.Normalize();

	//  FireBall 시트: 오른쪽(+X)이 공(앞부분)
	float angleDeg = -RadToDeg(atan2f(dir.x, dir.y)) + 90.f;
	b->SetWorldRotationZ(angleDeg);

	b->FireStartMotion();
}


//독탄 
void CPope::Toxic( )
{
	CastToxic();
	mPopeDefault = EPopeState::PopeIdle;

}

void CPope::CastToxic()
{
	
	if (!mTarget) return;  
	if (!mTarget->IsEnable()) return;

	const FVector3D playerPos = mTarget->GetWorldPosition();

	const float y = 350.f;            // y
	const float startX = -450.f;      // 첫 탄 x
	const float spacing = 150.f;      // 탄 간격

	for (int i = 0; i < 6; ++i)
	{
		CPopeToxic* ToxicOrb = mScene->CreateObj<CPopeToxic>("pope_toxicOrb");
		if (!ToxicOrb) continue;

		const float x = startX + spacing * i;

		ToxicOrb->SetWorldPos(x, y);
		ToxicOrb->SetBulletSpeed(500.f);
		ToxicOrb->SetBulletCollisionProfile("MonsterAttack");
		ToxicOrb->SetWorldScale(85.f, 85.f);

		// 조준(각 탄의 시작 위치 기준으로 플레이어 방향 계산)
		const FVector3D startPos = ToxicOrb->GetWorldPosition();
		FVector3D dir = playerPos - startPos;

		const float len2 = dir.x * dir.x + dir.y * dir.y;
		if (len2 < 0.001f) continue;

		dir.Normalize();

		// MoveAxis = Y 기준 조준 각도(너가 쓰던 방식 유지)
		float angleDeg = -RadToDeg(atan2f(dir.x, dir.y));
		ToxicOrb->SetWorldRotationZ(angleDeg);

		// 만약 반대로 나가면 아래 중 하나만 적용:
		// angleDeg += 180.f;
		// 또는 angleDeg 부호 반전
	}
}

//매직미사일
void CPope::MisiileP1(float DeltaTime)
{	
	if (!mIsCasting) return;
	// 패턴체크 
	if (!mMissilePattern) StartMissilePattern();
	UpdateMissilePattern(DeltaTime);
}

void CPope::CastMissile()
{
	const FVector3D popePos = mRoot->GetWorldPosition();

	bool faceLeft = false;
	if (mTarget && mTarget->IsEnable()) {
		faceLeft = (mTarget->GetWorldPosition().x < popePos.x);
	}
	else
	{
		faceLeft = mRoot->GetIsFlip(); // fallback
	}

	mMissileLeft = faceLeft;

	const float side = faceLeft ? -1.f : 1.f;

	const float forwardX = 35.f;
	const float kneeY = -60.f;

	FVector3D pos = (mMissileStep == 0) ? (popePos + FVector3D(forwardX * side, 0.f, 0.f))       // 위(명치)
										: (popePos + FVector3D(forwardX * side, kneeY, 0.f));    // 아래(무릎)

	SpawnMissile(pos);

	mMissileStep = 1 - mMissileStep;
}

void CPope::StartMissilePattern()
{
	mMissilePattern = true;
	mMissileAcc = mMissileInterval;   // 시작하자마자 1발 나가게
	mMissileStep = 0;                 // 첫 발은 pos1
//	mMissileLeft = mRoot->GetIsFlip(); // 캐스팅 시작 시 방향 

}

void CPope::UpdateMissilePattern(float DeltaTime)
{

	if (!mMissilePattern) return;
	if (!mIsCasting) return;

	mMissileAcc += DeltaTime;
	if (mMissileAcc < mMissileInterval) return;

	mMissileAcc -= mMissileInterval;   

	CastMissile(); //  1발만(위/아래 번갈아)
}

void CPope::SpawnMissile(const FVector3D& pos)
{
	CPopeMissile* Missile = mScene->CreateObj<CPopeMissile>("pope_magicMissile");
	if (!Missile) return;

	Missile->SetWorldPos(pos);
	Missile->SetBulletSpeed(500.f);
	Missile->SetFireDir(mMissileLeft);   
	Missile->SetBulletCollisionProfile("MonsterAttack");
	Missile->SetWorldScale(100.0f, 20.0f);

}

void CPope::ActiveSkill()
{
	switch (mNextSkill)
	{
	case EPopeState::PopeMissileP1: 
		mNextSkill = EPopeState::PopeToxic;    
		break;
	case EPopeState::PopeToxic:     
		mNextSkill = EPopeState::PopeFireBall; 
		break;
	case EPopeState::PopeFireBall:  
		mNextSkill = EPopeState::PopeMissileP1; 
		break;
	default:                        
		mNextSkill = EPopeState::PopeIdle; 
		break;
	}
}

void CPope::OnSpellCastEnd()
{
	if (mSymbol)    mSymbol->Stop();
	if (mSpellCast) mSpellCast->Stop();
	
	switch (mNextSkill)
	{
	case EPopeState::PopeMissileP1:
		//CastMissile(); 
		mMissilePattern = false;
		mMissileAcc = 0.f;
		break;
	case EPopeState::PopeToxic:     
		CastToxic();  
		break;
	case EPopeState::PopeFireBall:  
		//CastFireBall(); 
		StartFireBallPattern();
		//mPopeDefault = EPopeState::PopespellCast;
		break;
	default:                        
		break;
	}
	ActiveSkill();

	//  스킬 사용 카운트 증가
	++mSkillUseCount;

	//  2~3회 채우면 사라짐/등장
	if (mSkillUseCount >= mTeleportThreshold)
	{
		mPopeDefault = EPopeState::PopeVanishing;
		mIsCasting = true;          // 텔포 중에는 캐스팅 트리거 막기
		return;
	}
	// 3) 상태 복귀
	mIsCasting = false;
	mPopeDefault = EPopeState::PopeIdle;
}

void CPope::DebugDieAndGoScene2(float DeltaTime)
{
	BeginDeath();

}

void CPope::BeginDeath()
{
	    if (mDeathStarted) return;
    mDeathStarted = true;

    mPopeDefault = EPopeState::PopeDeath;
    mIsCasting = true;
    mPopeSkillCoolTime = 0.f;

    if (mSymbol)    mSymbol->Stop();
    if (mSpellCast) mSpellCast->Stop();
    if (mSymBolSprite) mSymBolSprite->SetEnable(false);
    if (mSpellSprite)  mSpellSprite->SetEnable(false);

    if (mAnimation)
    {
        mAnimation->ChangeAnimation("pope_death");
        mAnimation->SetEndFunction("pope_death", this, &CPope::OnDeathAnimEnd);
    }
}

