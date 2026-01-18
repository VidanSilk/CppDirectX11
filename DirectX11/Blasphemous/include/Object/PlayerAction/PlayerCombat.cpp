#include "PlayerCombat.h"
#include "../PlayerObject.h"
#include "../SceneObject.h"
#include "../../Animation/Animation2D.h"
#include "../../Component/ColliderAABB2D.h"
#include "../../Component/StaticMeshComponent.h"

CPlayerCombat::CPlayerCombat() {}

CPlayerCombat::CPlayerCombat(const CPlayerCombat& Combat) {}

CPlayerCombat::CPlayerCombat(CPlayerCombat&& Combat) {

}

CPlayerCombat::~CPlayerCombat() {

}

bool CPlayerCombat::Init(){



	return true;
}

void CPlayerCombat::Update(float DeltaTime) {
	if (!mOwner) return;

	if (mDodgeAtkDash)
	{
		mDodgeAtkDashAcc += DeltaTime;

		const float dir = mFlipCache ? -1.f : 1.f;
		const float dx = dir * mDodgeAtkDashSpeed * DeltaTime;

		//  가장 확실한 방법: 직접 월드포지션 이동(엔진에 맞게)
		FVector3D p = mOwner->GetWorldPosition();
		p.x += dx;
		mOwner->SetWorldPos(p);

		if (mDodgeAtkDashAcc >= mDodgeAtkDashDuration)
		{
			mDodgeAtkDash = false;
		}
	}
}

void CPlayerCombat::OnComboInput(bool bFlip)
{
	if (!mAnimation) return;

	//  DodgeATK 중이면: 지금은 공격 못 하니까 "끝나면 콤보" 버퍼
	if (mAtkType == EPlayerAtkType::Dodge)
	{
		mComboAfterDodgeBuffered = true;
		return;
	}

	if (mAtkType == EPlayerAtkType::Combo)
	{
		mAtkBuffered = true;
		return;
	}
	if (mAtkType != EPlayerAtkType::None) return;

	mAtkType = EPlayerAtkType::Combo;
	StartCombo(1);
}

void CPlayerCombat::OnUpAtkInput(bool bFlip)
{
	if (!mAnimation) return;
	if (mAtkType != EPlayerAtkType::None) return;

	mAtkType = EPlayerAtkType::Up;
	StartUpAtk();
}

void CPlayerCombat::OnDodgeAtkInput(bool bFlip)
{
	if (!mAnimation) return;
	if (mAtkType != EPlayerAtkType::None) return;

	mFlipCache = bFlip;          
	mAtkType = EPlayerAtkType::Dodge;
	StartDodgeAtk();
}

void CPlayerCombat::OnParryInput(bool bFlip)
{
	if (!mAnimation) return;
	if (mAtkType != EPlayerAtkType::None) return; // 공격 중 패링 금지(원하면 CancelAll 후 허용)

	mParryActive = true;
	mParrySuccess = false;

	mAnimation->ChangeAnimation("PlayerParry");

	if (!mParryCollider) return;

	// 패링 창 위치
	if (bFlip) mParryCollider->SetRelativePos(-40.f, 0.f);
	else       mParryCollider->SetRelativePos(40.f, 0.f);

	mParryCollider->SetEnable(true);
}

void CPlayerCombat::ComboNotify(bool bFlip)
{	// 기본 공격 판정 위치(튜닝)
	EnableAtkCollider(true, bFlip, 70.f, 0.f);
}

void CPlayerCombat::UpAtkNotify(bool bFlip)
{	// 상단 공격 판정(위쪽)
	EnableUpAtkCollider(true, bFlip, 40.f, 70.f);
}

void CPlayerCombat::DodgeAtkNotify(bool bFlip)
{

	EnableAtkCollider(true, bFlip, 90.f, -10.f);
}

bool CPlayerCombat::OnAttackEnd()
{
	if (mATKCollider) mATKCollider->SetEnable(false);
	if (mUpATKCollider) mUpATKCollider->SetEnable(false);

	if (mAtkType == EPlayerAtkType::Dodge)
	{
		mAtkType = EPlayerAtkType::None;

		if (mComboAfterDodgeBuffered)
		{
			mComboAfterDodgeBuffered = false;
			mAtkType = EPlayerAtkType::Combo;
			StartCombo(1);
			return true; // 계속 공격 상태 유지
		}

		mComboIndex = 0;
		ResetHit();
		return false;
	}

	if (mAtkType == EPlayerAtkType::Combo)
	{
	
		const bool chain = (mAtkBuffered && mHitConfirmed && mComboIndex < 4);

		if (chain)
		{
			StartCombo(mComboIndex + 1);
			return true; // 계속 공격 중
		}

		// 실패(히트 없음 or 입력 없음)면 1로 리셋
		mAtkType = EPlayerAtkType::None;
		mComboIndex = 0;
		ResetHit();
		return false;
	}

	// Up/Dodge는 단발
	mAtkType = EPlayerAtkType::None;
	mComboIndex = 0;
	ResetHit();
	return false;

}

bool CPlayerCombat::OnParryEnd()
{
	if (mParryCollider) mParryCollider->SetEnable(false);

	mLastParrySuccess = mParrySuccess;

	// 상태 리셋
	mParryActive = false;
	mParrySuccess = false;

	return true;
}


void CPlayerCombat::SetupColliders()
{  // 기본 공격
	if (mATKCollider)
	{
		mATKCollider->SetBoxSize(60.f, 40.f);
		mATKCollider->SetCollisionProfile("PlayerAttack");
		mATKCollider->SetEnable(false);
	//	mATKCollider->SetCollisionBeginFunc<CPlayerCombat>(this, &CPlayerCombat::OnAtkHitBegin);
	}

	// 위 공격
	if (mUpATKCollider)
	{
		mUpATKCollider->SetBoxSize(50.f, 90.f);
		mUpATKCollider->SetCollisionProfile("PlayerAttack");
		mUpATKCollider->SetEnable(false);
	//	mUpATKCollider->SetCollisionBeginFunc<CPlayerCombat>(this, &CPlayerCombat::OnAtkHitBegin);
	}

	// 패링
	if (mParryCollider)
	{
		mParryCollider->SetBoxSize(50.f, 50.f);
		mParryCollider->SetCollisionProfile("PlayerParry");
		mParryCollider->SetEnable(false);
	}
}

void CPlayerCombat::CancelAll()
{
	if (mATKCollider)    mATKCollider->SetEnable(false);
	if (mUpATKCollider)  mUpATKCollider->SetEnable(false);
	if (mParryCollider)  mParryCollider->SetEnable(false);

	mAtkType = EPlayerAtkType::None;
	mComboIndex = 0;
	mAtkBuffered = false;
	mHitConfirmed = false;

	mParryActive = false;
	mParrySuccess = false;
}

void CPlayerCombat::ConfirmParrySuccess()
{
	if (!mParryActive) return;
	mParrySuccess = true;
	if (mParryCollider) mParryCollider->SetEnable(false); // 성공 즉시 창 닫기(선택)
}

void CPlayerCombat::StartCombo(int idx)
{
	ResetHit();
	mComboIndex = idx;

	// ★ 콤보는 시퀀스를 3개로 나누는 걸 추천
	if (idx == 1) { 
		mAnimation->ChangeAnimation("PlayerAttack1"); 
	}
	else if (idx == 2) {
		mAnimation->ChangeAnimation("PlayerAttack2");
	}
	else {
		mAnimation->ChangeAnimation("PlayerAttack3");
	}

	if (mATKCollider) mATKCollider->SetEnable(false);
	if (mUpATKCollider) mUpATKCollider->SetEnable(false);
}

void CPlayerCombat::StartUpAtk()
{
	ResetHit();
	mAnimation->ChangeAnimation("PlayerUpATK");
	if (mATKCollider) mATKCollider->SetEnable(false);
	if (mUpATKCollider) mUpATKCollider->SetEnable(false);
}

void CPlayerCombat::StartDodgeAtk()
{
	ResetHit();
	mAnimation->ChangeAnimation("PlayerDodgeATK");

	mDodgeAtkDash = true;
	mDodgeAtkDashAcc = 0.f;

	if (mATKCollider) mATKCollider->SetEnable(false);
	if (mUpATKCollider) mUpATKCollider->SetEnable(false);
}

void CPlayerCombat::EnableAtkCollider(bool on, bool bFlip, float x, float y)
{
	if (!mATKCollider) return;
	if (!on) { 
		mATKCollider->SetEnable(false); return; 
	}

	if (bFlip) { 
		mATKCollider->SetRelativePos(-x, y); 
	}
	else {
		mATKCollider->SetRelativePos(x, y);
	}
	mATKCollider->SetEnable(true);
}

void CPlayerCombat::EnableUpAtkCollider(bool on, bool bFlip, float x, float y)
{
	CColliderAABB2D* col = mUpATKCollider ? mUpATKCollider : mATKCollider;
	if (!col) return;
	if (!on) { col->SetEnable(false); return; }

	if (bFlip) { 
		col->SetRelativePos(-x, y); 
	}
	else {
		col->SetRelativePos(x, y);
	}

	col->SetEnable(true);
}

void CPlayerCombat::ResetHit()
{
	mHitConfirmed = false;
	mAtkBuffered = false;
}

//void CPlayerCombat::OnAtkHitBegin(const FVector3D& HitPoint, CColliderBase* Dest)
//{
//	mHitConfirmed = true;
//}

