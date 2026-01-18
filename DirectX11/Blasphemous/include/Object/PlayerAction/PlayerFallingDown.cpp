#include "PlayerFallingDown.h"
#include "../PlayerObject.h"
#include "../../Animation/Animation2D.h"

CPlayerFallingDown::CPlayerFallingDown() {}
CPlayerFallingDown::CPlayerFallingDown(const CPlayerFallingDown& Obj) {}
CPlayerFallingDown::CPlayerFallingDown(CPlayerFallingDown&& Obj) {}
CPlayerFallingDown::~CPlayerFallingDown() {}

bool CPlayerFallingDown::Init()
{
	return true;
}

void CPlayerFallingDown::StartKnockDown()
{
	if (!mOwner || !mAnimation)
		return;

	// 한 번만 바인딩(중복 호출 방지)
	if (!mReady)
	{

		mAnimation->AddSequence("FallingOver", 1.0f, 1.0f, false, false);
		mAnimation->AddSequence("GettingUp", 1.0f, 1.0f, false, false);

		mAnimation->SetEndFunction("FallingOver", this, &CPlayerFallingDown::OnFallDownEnd);
		mAnimation->SetEndFunction("GettingUp", this, &CPlayerFallingDown::OnGetUpEnd);
		mReady = true;
	}

	mGettingUp = false;
	mDownTime = 0.f;
	FallDownAction();
}

void CPlayerFallingDown::Update(float DeltaTime)
{
	if (!mOwner || !mAnimation)
		return;

	// 넘어짐 애니 끝나고 바로 일어나기 싫으면 딜레이를 준다.
	if (!mGettingUp && mDownDelay > 0.f)
	{
		mDownTime += DeltaTime;
		if (mDownTime >= mDownDelay)
		{
			// 넘어짐 애니가 이미 끝났다면 GetUp로 전환
			// (애니 종료 콜백이 안 불리는 환경이면 여기서도 보정 가능)
		}
	}
}

void CPlayerFallingDown::FallDownAction()
{
	if (!mAnimation)
		return;

	// PlayerObject의 상태는 Damage에서 KnockDown으로 세팅한다.
	mAnimation->ChangeAnimation("FallingOver");
}

void CPlayerFallingDown::GetUpAction()
{
	if (!mAnimation)
		return;

	mGettingUp = true;
	mAnimation->ChangeAnimation("GettingUp");
}

void CPlayerFallingDown::OnFallDownEnd()
{
	// 넘어짐 애니 끝 -> 딜레이 후 일어나기
	if (mDownDelay <= 0.f)
	{
		GetUpAction();
		return;
	}

	// 딜레이는 Update에서 관리
	if (!mGettingUp)
		GetUpAction();
}

void CPlayerFallingDown::OnGetUpEnd()
{
	if (!mOwner)
		return;

	// 원복
	mOwner->mAutoBasePose = true;
	mOwner->mDefault = PlayerState::Idle;
}
