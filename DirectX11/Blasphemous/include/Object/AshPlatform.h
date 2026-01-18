#pragma once
#include "SceneObject.h"
#include "../Share/SharedPtr.h"

class CPlayerObject;
class CColliderBase;
class CAnimation2D;

enum class EAshPlatformState
{
    Hidden,     // 안 보임 + 충돌 꺼짐 (리스폰 대기)
    Spawn,      // AshplatformO (등장)
    Active,     // ashplatform_64x64_anim (유지/발판 활성)
    Despawn     // AshplatformX (사라짐)
};

class CAshPlatform : public CSceneObject
{
    friend class CScene;

protected:
    CAshPlatform();
    CAshPlatform(const CAshPlatform& Obj);
    CAshPlatform(CAshPlatform&& Obj);
    virtual ~CAshPlatform();

protected:
    CSharedPtr<class CSpriteComponent>   mPlat;
    CSharedPtr<class CColliderAABB2D>    mPlatformCollider;
    class CAnimation2D* mAnimation = nullptr;

    // 타이밍
    EAshPlatformState mState = EAshPlatformState::Spawn;
    float mActiveAcc = 0.f;        // Active 유지 누적
    float mRespawnAcc = 0.f;       // Hidden 대기 누적
    float mActiveDuration = 3.0f;  //  "ashplatform_64x64_anim" 유지 시간
    float mRespawnDelay = 2.0f;    //  사라진 뒤 다시 등장까지 대기 시간

    // 애니 리셋 방지(상태 진입 1회만 ChangeAnimation)
    bool mPlayedSpawn = false;
    bool mPlayedActive = false;
    bool mPlayedDespawn = false;

public:
    virtual bool Init() override;
    virtual void Update(float DeltaTime) override;

    // 씬에서 주기 조절하고 싶으면
    void SetTiming(float ActiveDuration, float RespawnDelay)
    {
        mActiveDuration = ActiveDuration;
        mRespawnDelay = RespawnDelay;
    }

    // 플레이어 바닥 처리(프로젝트 API에 맞게 구현)
    void CheckFloorCollider(CPlayerObject* Obj);

private:
    // 충돌 콜백
    void CollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest);

    // 애니 콜백
    void OnSpawnEnd();     // AshplatformO 끝
    void OnDespawnEnd();   // AshplatformX 끝

    // 유틸
    void SetVisibleAndCollidable(bool Enable);
    void ResetAnimFlags();
};