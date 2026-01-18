#include "Pontiff.h"
#include "PontiffBody.h"
#include "PontiffHead.h"
#include "PopeFireBall.h"
#include "PopeToxic.h"
#include "PopeMissile.h"
#include "PopeSymbol.h"
#include "PopeBeam.h"

#include "../MonsterObject.h"
#include "../../Component/ColliderSphere2D.h"
#include "../../Component/ColliderAABB2D.h"

#include "../PlayerObject.h"
#include "../../Scene/Scene.h"
#include "../../Component/SpriteComponent.h"
#include "../../Animation/Animation2D.h"
#include "../../Share/Log.h"

#include "../../Scene/SceneUIManager.h"
#include "../../UI/UserWidget/HeadInfo.h"
#include "../../Component/WidgetComponent.h"

//문자열 
#include <sstream>


static float RadToDeg(float r) { return r * 57.295f; }

CPontiff::CPontiff() : CMonsterObject()
{
}

CPontiff::CPontiff(const CPontiff& Obj) : CMonsterObject(Obj)
{
}

CPontiff::CPontiff(CPontiff&& Obj) : CMonsterObject(Obj)
{
}

CPontiff::~CPontiff()
{
}

bool CPontiff::Init()
{
    if (!CMonsterObject::Init()) return false;


    // 애니 세팅
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
    mAnimation->AddSequence("pontiff_openedIdle_face", 4.f, 0.7f, true, false);
    mAnimation->AddSequence("PontiffOpeningFace", 3.f, 1.0f, false, false);
    mAnimation->AddSequence("PontiffClosingHead", 3.f, 1.0f, false, false);
    mAnimation->AddSequence("pontiff_openedIdle_face_DEATH", 3.f, 1.0f, false, false);

    // 캐스팅(심볼) 애니
    mCastPoint = CreateComponent<CSceneComponent>();
    mRoot->AddChild(mCastPoint);
    mCastPoint->SetRelativePos(mCastOffset);


    // End 콜백
    mAnimation->SetEndFunction("PontiffOpeningFace", this, &CPontiff::OnHeadOpenEnd);
    mAnimation->SetEndFunction("PontiffClosingHead", this, &CPontiff::OnHeadClosingEnd);

    mAnimation->SetEndFunction("pontiff_openedIdle_face_DEATH", this, &CPontiff::OnDeathAnimEnd);
    //프레임 조절용 
    // mAnimation->AddNotify("pope_twistedOne_symbol", 6, this, &CPontiff::CastNotify);


    // 스케일
    mRoot->SetWorldScale(mClosedScale.x, mClosedScale.y);
    mRoot->SetPivot(0.58f, 0.93f);
    mRoot->SetTexture("Pontiff_Face");

    //콜라이더 
    //mHeadBody = CreateComponent<CColliderSphere2D>();
    //mRoot->AddChild(mHeadBody);

    //mHeadBody->SetRadius(60.f);              // <- 원하는 반지름으로 조절
    //mHeadBody->SetCollisionProfile("Monster");
    //mHeadBody->SetCollisionBeginFunc<CPontiff>(this, &CPontiff::OnPontiffHitBegin);
    //mHeadBody->SetCollisionEndFunc<CPontiff>(this, &CPontiff::OnPontiffHitEnd);

    //이걸로 콜라이더 값 맞춰주기. 
    //mHeadBody->SetPivot(1.0f, 0.93f);
 //  mHeadBody->SetRelativePos(-10.f,-75.f);
    // AABB말고 CColliderSphere2D로 설정 
    if (mBody)
    {
        mBody->SetEnable(true);
        mBody->SetCollisionProfile("Monster");
        mBody->SetBoxSize(120.f, 120.f);      // 머리 맞게
        mBody->SetRelativePos(-10.f, -75.f);  // 지금 sphere에 맞춘 값 그대로
        mBody->SetPivot(1.0f, 0.9f);
    }
    // 스탯
    mHP = mPontiffHP;

    // 초기 상태
    mState = EPontiffState::None;
    mPendingSkill = EPontiffSkill::None;

    mIsCasting = false;
    mCastTriggered = false;
    mForceOpenForCast = false;
    mOpenedVisual = false;

    mSkillAcc = 0.f;
    mOpenIdleAcc = 0.f;

    ResetAnimFlags();

    CHeadInfo* Widget = mScene->GetUIManager()->CreateWidget<CHeadInfo>("HeadInfo");
    mWidgetCoponent = CreateComponent<CWidgetComponent>();
    mWidgetCoponent->SetWidget(Widget);
    mWidgetCoponent->SetWorldScale(1200.f, 200.f, 0.1f);
    mWidgetCoponent->SetWorldPos(0.f, -330.f);
    mRoot->AddChild(mWidgetCoponent);

    // 닫힘 상태에서는 얼굴 숨김
  //  mRoot->SetEnable(false);
    mRoot->SetEnable(true);
    mRoot->SetOpacity(0.f);   // 닫힘(얼굴 숨김)
    SetTarget(mScene->FindObjectFromType<CPlayerObject>());

    CMonsterObject::SetState(EMonsterState::End);


    return true;
}

void CPontiff::Update(float DeltaTime)
{
    CMonsterObject::Update(DeltaTime);

    if (mHead && mHead->IsActive())
        SetWorldPos(mHead->GetWorldPosition() + mAttachOffset);

    //  스킬 쿨타임 트리거 
    if (mTarget && mTarget->IsActive() && mTarget->IsEnable())
    {
        if (!mIsCasting)
        {
            mSkillAcc += DeltaTime;
            if (mSkillAcc >= mSkillInterval)
            {
                mSkillAcc = 0.f;
                EPontiffSkill next = DecideNextSkill();

                StartCast(next, false);
            }
        }
    }
    else
    {
        mSkillAcc = 0.f;
    }


    if (mIsCasting && !mCastTriggered)
    {
        mCastAcc += DeltaTime;
        if (mCastAcc >= mCastWindup)
        {
            CastNotify();      // 실제 발사 1회
        }
    }

    if (mState == EPontiffState::Death)
    {
        mDeathAnimAcc += DeltaTime;

        // 애니 재생(1회)
        Die();

        // 애니가 끝났다고 판단되는 시점(최소시간) 이후에만 UI 딜레이 시작
        if (!mDeathAnimEnded && mDeathAnimAcc >= mDeathAnimMinTime)
        {
            mDeathAnimEnded = true;
            mDieUIWaiting = true;
            mDieUIAcc = 0.f;
        }
    }

    UpdateBeamDelay(DeltaTime);

    switch (mState)
    {
    case EPontiffState::None:        ClosedIdle(DeltaTime); break;
    case EPontiffState::HeadOpen:    HeadOpening(); break;
    case EPontiffState::OpeningIDLE: OpenIdle(DeltaTime); break;
    case EPontiffState::HeadClosing: HeadClosing(); break;
    case EPontiffState::Death:       Die(); break;
    default: break;
    }
}

float CPontiff::Damage(float Attack, CSceneObject* Obj)
{
    // 이미 죽는 중이면 추가 데미지 무시
    if (mDeathStarted || mState == EPontiffState::Death)
        return 0.f;

    // 닫힌 상태 / 열고닫는 중에는 무적
    if (mState == EPontiffState::None ||
        mState == EPontiffState::HeadOpen ||
        mState == EPontiffState::HeadClosing)
    {
        return 0.f;
    }

    //  Destroy가 없는 경로로 "적용 데미지"만 계산
    float applied = CSceneObject::Damage(Attack, Obj);
    if (applied <= 0.f)
        return 0.f;

    mHP -= applied;
    if (mHP <= 0.f)
    {
        mHP = 0.f;
        BeginDeath();
    }

    return applied;
}

void CPontiff::OnPontiffHitBegin(const FVector3D& HitPoint, CColliderBase* Dest)
{
}

void CPontiff::OnPontiffHitEnd(CColliderBase* Dest)
{
}

///////////////////////////////////////////////////////

void CPontiff::ResetAnimFlags()
{
    mPlayedClosedIdle = false;
    mPlayedOpening = false;
    mPlayedOpenIdle = false;
    mPlayedCast = false;
    mPlayedClosing = false;
    mPlayedDeath = false;
}

EPontiffSkill CPontiff::DecideNextSkill()
{
    EPontiffSkill out = mNextSkillCycle;

    switch (mNextSkillCycle)
    {
    case EPontiffSkill::PontiffFireBall:   mNextSkillCycle = EPontiffSkill::PontiffToxic;      break;
    case EPontiffSkill::PontiffToxic:      mNextSkillCycle = EPontiffSkill::PontiffMissileP2;  break;
    case EPontiffSkill::PontiffMissileP2:  mNextSkillCycle = EPontiffSkill::PontiffBeam;       break;
    case EPontiffSkill::PontiffBeam:       mNextSkillCycle = EPontiffSkill::PontiffFireBall;   break;
    default:                               mNextSkillCycle = EPontiffSkill::PontiffFireBall;  out = EPontiffSkill::PontiffFireBall; break;
    }

    return out;
}

void CPontiff::StartCast(EPontiffSkill Skill, bool NeedOpenVisual)
{

    mPendingSkill = Skill;
    mIsCasting = true;
    mCastTriggered = false;

    mCastAcc = 0.f;

    // 스킬은 얼굴 상태와 무관: 여기서 ResetAnimFlags(), mState 변경 금지
    mForceOpenForCast = false;
}

void CPontiff::CastNotify()
{


    if (mCastTriggered) return;
    mCastTriggered = true;

    switch (mPendingSkill)
    {
    case EPontiffSkill::PontiffFireBall:
        CastFireBall();
        break;

    case EPontiffSkill::PontiffToxic:
        CastToxic();
        break;

    case EPontiffSkill::PontiffMissileP2:
        CastMissileP2();
        break;

    case EPontiffSkill::PontiffBeam:
        CastBeam();
        break;

    default:
        break;
    }

    // 단발 스킬은 여기서 캐스팅 종료 + 닫기 연출(너 현재 구조 유지)
    mIsCasting = false;
    mPendingSkill = EPontiffSkill::None;
    mForceOpenForCast = false;
    //mState = EPontiffState::HeadClosing;
    //mPlayedClosing = false;

}

// State handlers

void CPontiff::ClosedIdle(float DeltaTime)
{

    if (!mPlayedClosedIdle)
    {
        mPlayedClosedIdle = true;

        mOpenedVisual = false;
        mRoot->SetEnable(true);
        mRoot->SetOpacity(0.f);
        mRoot->SetWorldScale(mClosedScale.x, mClosedScale.y);

        mClosedIdleAcc = 0.f;
    }

    mClosedIdleAcc += DeltaTime;

    //  닫힘 유지 시간 지나면 다시 열기
    if (mClosedIdleAcc >= mClosedIdleDuration)
    {
        mClosedIdleAcc = 0.f;
        mState = EPontiffState::HeadOpen;
        mPlayedOpening = false;
    }
}

void CPontiff::HeadOpening()
{
    if (!mAnimation) return;
    if (mPlayedOpening) return;

    mPlayedOpening = true;

    // 열림 연출 보여주려면 얼굴 표시
    mRoot->SetEnable(true);
    mRoot->SetOpacity(1.f);
    mRoot->SetWorldScale(mOpenScale.x, mOpenScale.y);
    mAnimation->ChangeAnimation("PontiffOpeningFace");
}

void CPontiff::OpenIdle(float DeltaTime)
{

    if (!mAnimation) return;

    if (!mPlayedOpenIdle)
    {
        mPlayedOpenIdle = true;
        mOpenedVisual = true;

        mRoot->SetEnable(true);
        mRoot->SetOpacity(1.f);
        mRoot->SetWorldScale(mOpenScale.x, mOpenScale.y);
        mAnimation->ChangeAnimation("pontiff_openedIdle_face");

        mOpenIdleAcc = 0.f;
    }

    mOpenIdleAcc += DeltaTime;

    if (mOpenIdleAcc >= mOpenIdleDuration)
    {
        mOpenIdleAcc = 0.f;
        mState = EPontiffState::HeadClosing;
        mPlayedClosing = false;
    }
}

void CPontiff::HeadClosing()
{
    if (!mAnimation) return;
    if (mPlayedClosing) return;

    mPlayedClosing = true;

    mRoot->SetEnable(true);
    mRoot->SetOpacity(1.f);
    mRoot->SetWorldScale(mOpenScale.x, mOpenScale.y);
    mAnimation->ChangeAnimation("PontiffClosingHead");
}

void CPontiff::Die()
{
    if (!mAnimation) return;
    if (mPlayedDeath) return;

    mPlayedDeath = true;

    mRoot->SetEnable(true);
    mRoot->SetOpacity(1.f);
    mRoot->SetWorldScale(mOpenScale.x, mOpenScale.y);

    // 죽음 애니 재생
    mAnimation->ChangeAnimation("pontiff_openedIdle_face_DEATH");

}

void CPontiff::OnHeadOpenEnd()
{
    if (mDeathStarted) return;
    // 열림 끝 → OpenIdle로
    mState = EPontiffState::OpeningIDLE;
    mPlayedOpenIdle = false;
    mOpenIdleAcc = 0.f;
}


void CPontiff::OnHeadClosingEnd()
{
    if (mDeathStarted) return;
    mOpenedVisual = false;

    mRoot->SetEnable(true);
    mRoot->SetOpacity(0.f);
    mRoot->SetWorldScale(mClosedScale.x, mClosedScale.y);

    mState = EPontiffState::None;

    // 다음 ClosedIdle에서 다시 루프 돌 수 있게 플래그 리셋
    mPlayedClosedIdle = false;
    mPlayedOpening = false;
    mPlayedOpenIdle = false;
    mPlayedClosing = false;

}

void CPontiff::CastFireBall()
{
    if (!mTarget || !mTarget->IsEnable()) return;

    const FVector3D playerPos = mTarget->GetWorldPosition();

    // 스폰 기준: CastPoint 있으면 거기서, 없으면 Pontiff 위치
    FVector3D base = mRoot->GetWorldPosition();
    if (mCastPoint)
        base = mCastPoint->GetWorldPosition();

    // Pope처럼 3발 좌우 벌리기
    const float offsets[10] = { -800.f, -720.f, -640.f, -560.f, -480.f,
                                100.f, 160.f, 220.f, 280.f, 350.f
    };

    for (int i = 0; i < 10; ++i)
    {
        CPopeFireBall* b = mScene->CreateObj<CPopeFireBall>("Pontiff_FireBall");
        if (!b) continue;

        // 스폰 위치(원하면 Y쪽도 살짝 벌려도 됨)
        const FVector3D spawnPos = base + FVector3D(offsets[i], 0.f, 0.f);

        b->SetWorldPos(spawnPos);
        b->SetBulletSpeed(200.f);
        b->SetBulletCollisionProfile("MonsterAttack");
        b->SetWorldScale(120.f, 80.f);

        // 조준
        FVector3D dir = playerPos - spawnPos;
        const float len2 = dir.x * dir.x + dir.y * dir.y;
        if (len2 < 0.001f) continue;
        dir.Normalize();

        //  Pope FireBall에서 쓰던 공식 그대로
        float angleDeg = -RadToDeg(atan2f(dir.x, dir.y)) + 90.f;
        b->SetWorldRotationZ(angleDeg);

        // 시작 모션(이게 내부적으로 “발사 시작”을 담당하면 꼭 호출)
        b->FireStartMotion();
    }
}



void CPontiff::CastToxic()
{
    if (!mTarget || !mTarget->IsEnable()) return;

    const FVector3D playerPos = mTarget->GetWorldPosition();

    // 6발 라인
    const int count = 6;
    const float spacing = 150.f;

    //  플레이어 X 기준으로 중앙 정렬
    const float startX = playerPos.x - spacing * (count - 1) * 0.5f;

    // Y는 “위에서” or “중간 라인” 등 원하는 값
    const float y = 350.f;

    for (int i = 0; i < count; ++i)
    {
        CPopeToxic* t = mScene->CreateObj<CPopeToxic>("Pontiff_Toxic");
        if (!t) continue;

        const float x = startX + spacing * i;
        t->SetWorldPos(x, y);
        t->SetBulletSpeed(500.f);
        t->SetBulletCollisionProfile("MonsterAttack");
        t->SetWorldScale(85.f, 85.f);

        // 조준
        const FVector3D startPos = t->GetWorldPosition();
        FVector3D dir = playerPos - startPos;

        const float len2 = dir.x * dir.x + dir.y * dir.y;
        if (len2 < 0.001f) continue;

        dir.Normalize();

        //  Pope Toxic에서 쓰던 공식 그대로
        float angleDeg = -RadToDeg(atan2f(dir.x, dir.y));
        t->SetWorldRotationZ(angleDeg);
    }
}

void CPontiff::CastMissileP2()
{
    if (!mScene) return;

    // 기준 좌표: CastPoint 있으면 그 기준, 없으면 Pontiff 기준
    FVector3D base = GetWorldPosition();
    if (mCastPoint)
        base = mCastPoint->GetWorldPosition();

    // 좌/우 200 오프셋
    FVector3D leftPos = base + FVector3D(-600.f, -50.f, 0.f);
    FVector3D rightPos = base + FVector3D(250.f, -50.f, 0.f);

    // 미사일 생성 헬퍼(각도 1개씩 하드코딩 호출용)
    auto SpawnOne = [&](const FVector3D& pos, float angleDeg)
        {
            CPopeMissile* m = mScene->CreateObj<CPopeMissile>("Pontiff_Missile");
            if (!m) return;

            m->SetWorldPos(pos);
            m->SetWorldScale(110.f, 24.f);

            // 속도: CPopeMissile::Init()에서 MoveSpeed를 300으로 박아놨기 때문에
            // 여기서 BulletSpeed를 바꾸고 SetFireDir(false) 한번 호출해서
            // MoveSpeed를 +BulletSpeed로 덮어씌우는 방식으로 맞춤.
            m->SetBulletSpeed(150.f);
            m->SetFireDir(false);          // ✅ MoveSpeed = +420 으로 강제 세팅

            // 방향: 회전값으로 8방향 만들기 (0=오른쪽, 90=위, -90=아래, 180=왼쪽)
            m->SetWorldRotationZ(angleDeg);
        };

    // 왼쪽 스폰
    SpawnOne(leftPos, 0.f);
    SpawnOne(leftPos, 45.f);
    SpawnOne(leftPos, 90.f);
    SpawnOne(leftPos, 135.f);
    SpawnOne(leftPos, 180.f);
    SpawnOne(leftPos, -135.f);
    SpawnOne(leftPos, -90.f);
    SpawnOne(leftPos, -45.f);

    // 오른쪽 스폰
    SpawnOne(rightPos, 0.f);
    SpawnOne(rightPos, 45.f);
    SpawnOne(rightPos, 90.f);
    SpawnOne(rightPos, 135.f);
    SpawnOne(rightPos, 180.f);
    SpawnOne(rightPos, -135.f);
    SpawnOne(rightPos, -90.f);
    SpawnOne(rightPos, -45.f);
}

void CPontiff::CastBeam()
{

    SpawnBeamAt(mBeamXLeft1, mBeamGroundY, 0.1f);
    SpawnBeamAt(mBeamXRight2, mBeamGroundY, 0.1f);

    //  중앙 빔은 5초 뒤 스폰 예약
    // 이미 예약 중이면 "마지막 빔 기준으로 5초"로 리셋
    mBeamCenterPending = true;
    mBeamCenterAcc = 0.f;
}

void CPontiff::UpdateBeamDelay(float DeltaTime)
{
    if (!mBeamCenterPending) return;

    mBeamCenterAcc += DeltaTime;
    if (mBeamCenterAcc >= mBeamCenterDelay)
    {
        mBeamCenterPending = false;
        mBeamCenterAcc = 0.f;
        SpawnBeamAt(mBeamXLeft2, mBeamGroundY, 0.8f);
        SpawnBeamAt(mBeamXRight1, mBeamGroundY, 0.8f);
    }
}

void CPontiff::SpawnBeamAt(float x, float y, float z)
{
    if (!mScene) return;

    CPopeBeam* beam = mScene->CreateObj<CPopeBeam>("Pontiff_Beam");
    if (!beam) return;

    beam->SetWorldPos(x, y, 0.8f);
    beam->SetBeamDmg(mPontiffATK);
    beam->SetBeamSkillCollisionProfile("MonsterAttack");
}

void CPontiff::ShowDieWidget()
{
    if (mDieUIPlayed) return;
    mDieUIPlayed = true;

    if (!mScene) return;
    auto* UIManager = mScene->GetUIManager();
    if (!UIManager) return;

    if (!mDieWidget)
    {
        mDieWidget = UIManager->CreateWidget<CPontiffDieWidget>("PontiffDieUI");
        UIManager->AddToViewport(mDieWidget);
    }
}

void CPontiff::OnDeathAnimEnd()
{
    if (!mDeathStarted) return;
    if (mDeathAnimAcc < mDeathAnimMinTime) return;

    if (mDieUIPlayed) return;

    mDeathAnimEnded = true;
    mDieUIWaiting = true;
    mDieUIAcc = 0.f;
}

void CPontiff::UpdateDeathUIDelay(float DeltaTime)
{
    if (!mDieUIWaiting) return;
    if (mDieUIPlayed) return;

    mDieUIAcc += DeltaTime;
    if (mDieUIAcc >= mDieUIDelay)
    {
        mDieUIWaiting = false;
        ShowDieWidget();        // 여기서 띄움
    }
}

void CPontiff::BeginDeath()
{
    if (mDeathStarted) return;
    mDeathStarted = true;

    mState = EPontiffState::Death;

    // 공격/스킬 중단
    mIsCasting = false;
    mPendingSkill = EPontiffSkill::None;
    mCastTriggered = true;

    // 충돌 끄기(추가 타격 방지)
    if (mBody) mBody->SetEnable(false);

    // 죽음 UI/애니 플래그 확실히 초기화
    mDieUIWaiting = false;
    mDieUIPlayed = false;
    mDieUIAcc = 0.f;

    mDeathAnimAcc = 0.f;
    mDeathAnimEnded = false;

    // 죽음 비주얼 강제 오픈
    mRoot->SetEnable(true);
    mRoot->SetOpacity(1.f);
    mRoot->SetWorldScale(mOpenScale.x, mOpenScale.y);

    // Die()가 1회만 재생하도록 플래그 리셋
    mPlayedDeath = false;

    // 여기서 바로 죽음 애니 시작(업데이트에서 Die()가 부르긴 하지만 확실하게)
    if (mAnimation)
        mAnimation->ChangeAnimation("pontiff_openedIdle_face_DEATH");

}
