#include "AshPlatform.h"

#include "../Component/SpriteComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Animation/Animation2D.h"
#include "../Scene/Scene.h"

// 플레이어 타입 캐스팅이 필요하면 include
#include "../Object/PlayerObject.h"   // 경로는 네 프로젝트에 맞게 조정
#include "../Share/Log.h"
#include "../Component/GravityComponent.h"

CAshPlatform::CAshPlatform() {}
CAshPlatform::CAshPlatform(const CAshPlatform& Obj) : CSceneObject(Obj) {}
CAshPlatform::CAshPlatform(CAshPlatform&& Obj) : CSceneObject(Obj) {}
CAshPlatform::~CAshPlatform() {}

void CAshPlatform::ResetAnimFlags()
{
    mPlayedSpawn = false;
    mPlayedActive = false;
    mPlayedDespawn = false;
}

void CAshPlatform::SetVisibleAndCollidable(bool Enable)
{
    if (mPlat)             mPlat->SetEnable(Enable);
    if (mPlatformCollider) mPlatformCollider->SetEnable(Enable);
}

bool CAshPlatform::Init()
{
    if (!CSceneObject::Init())
        return false;

    // 스프라이트
    mPlat = CreateComponent<CSpriteComponent>();
    SetRootComponent(mPlat);

    mPlat->SetPivot(0.5f, 0.5f);
    mPlat->SetOpacity(1.f);
    mPlat->SetTint(1.f, 1.f, 1.f);
   // mPlat->SetUseTime(false);
    //크기 조절
    mPlat->SetWorldScale(120.f, 60.f);

    // 콜라이더
    mPlatformCollider = CreateComponent<CColliderAABB2D>();
    mPlat->AddChild(mPlatformCollider);

    mPlatformCollider->SetBoxSize(115.f, 15.f);          // 발판 두께(취향)
    mPlatformCollider->SetRelativePos(0.f, 20.f, 0.f); // 발판이 스프라이트 아래쪽이면 조정
    mPlatformCollider->SetCollisionProfile("Floor");    // 일단 기본값으로 세팅 
    mPlatformCollider->SetCollisionBeginFunc<CAshPlatform>(this, &CAshPlatform::CollisionBegin);

    // 애니
    mAnimation = mPlat->CreateAnimation2D<CAnimation2D>();
    mAnimation->AddSequence("AshplatformO", 2.0f, 1.2f, false, false);        // 등장
    mAnimation->AddSequence("ashplatform_64x64_anim", 7.0f, 1.0f, true, false); // 유지
    mAnimation->AddSequence("AshplatformX", 2.0f, 1.2f, false, false);        // 사라짐

    // End 콜백은 loop=false에만
    mAnimation->SetEndFunction("AshplatformO", this, &CAshPlatform::OnSpawnEnd);
    mAnimation->SetEndFunction("AshplatformX", this, &CAshPlatform::OnDespawnEnd);

    // 시작 상태: 바로 등장
    mState = EAshPlatformState::Spawn;
    ResetAnimFlags();
    SetVisibleAndCollidable(true);

    return true;
}

void CAshPlatform::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    switch (mState)
    {
    case EAshPlatformState::Hidden:
        // 안 보이고 충돌도 없음
        mRespawnAcc += DeltaTime;
        if (mRespawnAcc >= mRespawnDelay)
        {
            mRespawnAcc = 0.f;
            mState = EAshPlatformState::Spawn;
            ResetAnimFlags();
            SetVisibleAndCollidable(true);
        }
        break;

    case EAshPlatformState::Spawn:
        if (!mAnimation) break;

        if (!mPlayedSpawn)
        {
            mPlayedSpawn = true;
            // 등장 중에는 보이되, 밟게 할지 말지는 선택
            // 보통 등장 애니 중엔 밟히면 이상해서 콜라이더 OFF 추천
            if (mPlatformCollider) mPlatformCollider->SetEnable(false);

            mAnimation->ChangeAnimation("AshplatformO");
        }
        break;

    case EAshPlatformState::Active:
        if (!mAnimation) break;

        if (!mPlayedActive)
        {
            mPlayedActive = true;

            // 유지 구간에서 발판 활성
            if (mPlatformCollider) mPlatformCollider->SetEnable(true);

            mAnimation->ChangeAnimation("ashplatform_64x64_anim");
            mActiveAcc = 0.f;
        }

        mActiveAcc += DeltaTime;
        if (mActiveAcc >= mActiveDuration)
        {
            mActiveAcc = 0.f;
            mState = EAshPlatformState::Despawn;
            mPlayedDespawn = false;
         //   CLog::PrintLog("Platform: Active -> Despawn");
        }
        break;

    case EAshPlatformState::Despawn:
        if (!mAnimation) break;

        if (!mPlayedDespawn)
        {
            mPlayedDespawn = true;

            // 사라지는 동안 밟히면 안 되니까 OFF
            if (mPlatformCollider) mPlatformCollider->SetEnable(false);

            mAnimation->ChangeAnimation("AshplatformX");
        }
        break;
    }
}

void CAshPlatform::OnSpawnEnd()
{
    // 등장 끝 -> 유지(활성)
    mState = EAshPlatformState::Active;
    mPlayedActive = false;
}

void CAshPlatform::OnDespawnEnd()
{
    // 사라짐 끝 -> 숨김(대기)
    mState = EAshPlatformState::Hidden;
    mRespawnAcc = 0.f;
    SetVisibleAndCollidable(false);
}

void CAshPlatform::CollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
    if (mState != EAshPlatformState::Active) return;
    if (!Dest) return;

    CSceneObject* Owner = Dest->GetOwner();
    if (!Owner) return;

    CPlayerObject* Player = dynamic_cast<CPlayerObject*>(Owner);
    if (!Player) return;

    CheckFloorCollider(Player);
}

void CAshPlatform::CheckFloorCollider(CPlayerObject* Obj)
{
    if (!Obj) return;
    if (mState != EAshPlatformState::Active) return;
    if (!mPlatformCollider || !mPlatformCollider->IsEnable()) return;

    CColliderAABB2D* PlayerCol = Obj->GetPlayerMoveCollider();
    CColliderAABB2D* FloorCol = mPlatformCollider.Get();

    if (!PlayerCol || !FloorCol) return;

    CGravityComponent* Gravity = Obj->GetGravity();
    if (!Gravity) return;

    // 상승 중이면 착지 처리 X
    if (Gravity->GetVelocityY() > 0.f)
        return;

    // AABB 범위
    const FVector3D PlayerMin = PlayerCol->GetMin();
    const FVector3D PlayerMax = PlayerCol->GetMax();
    const FVector3D FloorMin = FloorCol->GetMin();
    const FVector3D FloorMax = FloorCol->GetMax();

    // 발판 위에 있는지(X축 겹침)
    const bool XOverlap = (PlayerMax.x > FloorMin.x) && (PlayerMin.x < FloorMax.x);
    if (!XOverlap) return;

    const float FloorTop = FloorMax.y;   // 발판 윗면
    const float PlayerBottom = PlayerMin.y;  // 플레이어 바닥

    // 1) 겹침(Overlap) 검사
    FVector3D Hit;
    const bool bHit = PlayerCol->Collision(Hit, FloorCol);

    // “접촉”도 착지로 인정할 스킨 거리
    const float Skin = 8.f;

    if (bHit)
    {
        // 파고든 만큼 위로 올려서 스냅
        const float Penetration = FloorTop - PlayerBottom; // > 0 이면 파고듦
        if (Penetration > 0.f)
        {
            FVector3D Pos = Obj->GetWorldPosition();
            Pos.y += Penetration;
            Obj->SetWorldPos(Pos);
        }

        Gravity->SetGrounded(true);
        return;
    }

    // 2) 겹치진 않지만, 바로 위면(gap이 Skin 이하) 착지로 인정 (한 프레임 밟고 떨어짐 방지)
    const float Gap = PlayerBottom - FloorTop; // >0: 발판 위로 떠있음
    if (Gap >= 0.f && Gap <= Skin)
    {
        FVector3D Pos = Obj->GetWorldPosition();
        Pos.y -= Gap;               // 아래로 스냅해서 딱 붙임
        Obj->SetWorldPos(Pos);

        Gravity->SetGrounded(true);
        return;
    }
}