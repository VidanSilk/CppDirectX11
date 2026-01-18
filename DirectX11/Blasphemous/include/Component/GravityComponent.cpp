#include "GravityComponent.h"
#include "../Object/SceneObject.h"
#include "../Vector3D.h"

CGravityComponent::CGravityComponent() {
}

CGravityComponent::CGravityComponent(const CGravityComponent& Com) : CComponent(Com)
{
}

CGravityComponent::CGravityComponent(CGravityComponent&& Com) : CComponent(Com)
{
}

CGravityComponent::~CGravityComponent()
{
}

bool CGravityComponent::Init()
{
	return true;
}

void CGravityComponent::Update(float DeltaTime)
{
	if (!mOwnerObject) return;

	// 공중이면 중력 적용
	if (!mGrounded)
	{
		mVelocityY += mGravity * DeltaTime;

		// 터미널 속도(낙하 최대 속도) 제한
		if (mVelocityY < mTerminalVelocity)
			mVelocityY = mTerminalVelocity;

		// Y축 이동 (월드 포지션에 직접 적용)
		mOwnerObject->AddWorldPos(0.f, mVelocityY * DeltaTime, 0.f);
	}
	else
	{
		// 착지 상태에서는 아래로 내려가는 속도는 제거
		if (mVelocityY < 0.f)
			mVelocityY = 0.f;
	}
}

void CGravityComponent::SetGrounded(bool Grounded)
{
	mGrounded = Grounded;

	if (mGrounded && mVelocityY < 0.f)
		mVelocityY = 0.f;
}

void CGravityComponent::GravityLand(float SnapWorldY, bool bSnap)
{
	mGrounded = true;
	mVelocityY = 0.f;

	if (bSnap && mOwnerObject)
	{
		const FVector3D& Pos = mOwnerObject->GetWorldPosition();
		mOwnerObject->SetWorldPos(Pos.x, SnapWorldY, Pos.z);
	}
}

void CGravityComponent::GravityJump(float JumpSpeed)
{	//  점프
	if (!mGrounded) return;

	mGrounded = false;
	mVelocityY = JumpSpeed;
}

void CGravityComponent::AddImpulseY(float ImpulseY)
{
	mVelocityY += ImpulseY;

	// 임펄스가 위로 들어오면 공중 처리
	if (mVelocityY > 0.f) mGrounded = false;
}

void CGravityComponent::ResetY(float NewVelY)
{
	mVelocityY = NewVelY;
}
