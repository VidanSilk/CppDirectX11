#include "AshBright.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MovementComponent.h"
#include "../Animation/Animation2D.h"
#include "../Asset/Texture/Texture.h"
#include <chrono>

CAshBright::CAshBright()
{
	auto seed = (unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count();
	mRng.seed(seed);
}

CAshBright::CAshBright(const CAshBright& Obj) : CSceneObject(Obj)
{
}

CAshBright::CAshBright(CAshBright&& Obj) : CSceneObject(Obj)
{
}

CAshBright::~CAshBright()
{
}

bool CAshBright::Init()
{
	CSceneObject::Init();
	//랜덤으로 뿌릴꺼아님? 
	mAshRoot = CreateComponent<CSpriteComponent>("AshBright");
	mAshAnim = mAshRoot->CreateAnimation2D<CAnimation2D>();

	SetRootComponent(mAshRoot);
	if (!mAshAnim) return false;
	mAshAnim->AddSequence("AshBright", 2.0f, 1.5f, true, false);
	mAshAnim->ChangeAnimation("AshBright");
	randomAsh();
	return true;
}

void CAshBright::Update(float DeltaTime)
{
	// (1) 먼저 이동 처리 (바람 + 낙하)
	if (mAshRoot)
	{
		FVector3D pos = mAshRoot->GetWorldPosition();
		pos.x += mVelX * DeltaTime;
		pos.y += mVelY * DeltaTime;
		mAshRoot->SetWorldPos(pos);

		// 아래로 떨어지면 리셋
		if (pos.y < mKillY)
			randomAsh();
	}
	CSceneObject::Update(DeltaTime);

}


void CAshBright::randomAsh()
{
	// 분포 (멤버 범위 사용)
	std::uniform_real_distribution<float> distX(mMinX, mMaxX);
	std::uniform_real_distribution<float> distY(mSpawnYMin, mSpawnYMax);
	std::uniform_real_distribution<float> distScale(20.f, 50.f);
	std::uniform_real_distribution<float> distRot(0.f, 360.f);

	// 바람/낙하 속도
	std::uniform_real_distribution<float> distVelX(-60.f, 60.f);
	std::uniform_real_distribution<float> distVelY(-320.f, -160.f); // 아래가 -Y 기준

	const float x = distX(mRng);
	const float y = distY(mRng);

	mAshRoot->SetWorldPos(x, y, 0.03f);

	const float s = distScale(mRng);
	mAshRoot->SetWorldScale(s, s);

	mAshRoot->SetRelativeRotationZ(distRot(mRng));

	// 속도 갱신
	mVelX = distVelX(mRng);
	mVelY = distVelY(mRng);

}
