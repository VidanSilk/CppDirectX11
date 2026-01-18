#include "PlayerSkill.h"
#include "../PlayerObject.h"
#include "../MonsterObject.h"
#include "../SceneObject.h"

#include "../../Component/ColliderAABB2D.h"
#include "../../Animation/Animation2D.h"
#include "../../Component/SpriteComponent.h"
#include "../../Share/Log.h"

CPlayerSkill::CPlayerSkill() {}
CPlayerSkill::CPlayerSkill(const CPlayerSkill& Skill) {}
CPlayerSkill::CPlayerSkill(CPlayerSkill&& Skill) {}
CPlayerSkill::~CPlayerSkill() {}

bool CPlayerSkill::Init()
{
	return true;
}

bool CPlayerSkill::Setup()
{
	if (mReady) return true;

	if (!mPlayerAnim || !mBeamSprite || !mBeamAnim || !mBeamCollider)
		return false;

	// 빔(겸용) 애니 등록
	mBeamAnim->AddSequence("PlayerDivineSkill", 2.0f, 1.0f, false, false);

	// 초기 OFF
	mBeamSprite->SetEnable(false);
	mBeamCollider->SetEnable(false);

	mReady = true;
	return true;
}

void CPlayerSkill::skillAction(bool bFlip)
{
	if (!Setup()) return;

	mPlayerAnim->ChangeAnimation("PlayerAura");

	mCasting = true;
	mBeamActive = false;
	mBeamTime = 0.f;

	mBeamSprite->SetFlip(bFlip);
	mBeamSprite->SetEnable(true);
	mBeamAnim->ChangeAnimation("PlayerDivineSkill");

	// 위치는 PlayerObject에서 잡아둔 RelativePos 그대로 쓰는 걸 추천
	// mBeamSprite->SetRelativePos(0.f, 0.f, 0.1f);

	mBeamCollider->SetEnable(false);
}

void CPlayerSkill::Fire(bool bFlip)
{
	if (!Setup()) return;

	mCasting = false;
	mBeamActive = true;
	mBeamTime = 0.f;

	mBeamSprite->SetFlip(bFlip);
	mBeamSprite->SetEnable(true);

	// 플레이어 위 고정 연출이면 위치 이동하지 말자
	// if (bFlip) mBeamSprite->SetRelativePos(-mFireOffsetX, mFireOffsetY, 0.f);
	// else       mBeamSprite->SetRelativePos( mFireOffsetX, mFireOffsetY, 0.f);

	mBeamCollider->SetEnable(true);
}

void CPlayerSkill::Update(float DeltaTime)
{
	// 발사체 모드일 때만 이동/수명
	if (!mBeamActive || !mBeamSprite)
		return;

	mBeamTime += DeltaTime;
	if (mBeamTime >= mBeamLife)
	{
		StopBeam();
		return;
	}

	//const float dir = mBeamSprite->GetIsFlip() ? -1.f : 1.f;
	//mBeamSprite->AddRelativePos(mBeamSpeed * DeltaTime * dir, 0.f, 0.f);
}

void CPlayerSkill::SkillEnd()
{
	StopBeam();
}

void CPlayerSkill::StopBeam()
{
	mCasting = false;
	mBeamActive = false;
	mBeamTime = 0.f;

	if (mBeamCollider) mBeamCollider->SetEnable(false);
	if (mBeamSprite)   mBeamSprite->SetEnable(false);
}