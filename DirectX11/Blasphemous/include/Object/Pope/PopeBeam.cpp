#include "PopeBeam.h"

#include "../../Component/SpriteComponent.h"
#include "../../Component/ColliderAABB2D.h"
#include "../../Animation/Animation2D.h"
#include "../../Scene/Scene.h"
#include "../../Share/Log.h"

// 플레이어 데미지 주기 위해
#include "../PlayerObject.h"

CPopeBeam::CPopeBeam() : CSceneObject()
{
}

CPopeBeam::CPopeBeam(const CPopeBeam& Obj) : CSceneObject(Obj)
{
}

CPopeBeam::CPopeBeam(CPopeBeam&& Obj) : CSceneObject(Obj)
{
}

CPopeBeam::~CPopeBeam()
{
}

void CPopeBeam::SetBeamSkillCollisionProfile(const std::string& Name)
{
    if (mBeamCollider)
        mBeamCollider->SetCollisionProfile(Name);
}

bool CPopeBeam::Init()
{
    if (!CSceneObject::Init())
        return false;

    // 루트(스프라이트)
    mRoot = CreateComponent<CSpriteComponent>();
    SetRootComponent(mRoot);
    mRoot->SetRenderLayerName("Effect");
    mRoot->SetPivot(0.5f, 0.65f);        // 바닥 기준(아래가 피벗)
    mRoot->SetOpacity(1.f);
    mRoot->SetTint(1.f, 1.f, 1.f);

    // 빔 기본 크기(원하는 대로 조절)
    mRoot->SetWorldScale(250.f, 900.f);

    // 콜라이더
    mBeamCollider = CreateComponent<CColliderAABB2D>();
    mRoot->AddChild(mBeamCollider);

    // 빔이 위로 길게 올라가니까 콜라이더도 위로
    mBeamCollider->SetBoxSize(120.f, 800.f);
    mBeamCollider->SetRelativePos(0.f, 0.f, 0.f); // 피벗이 바닥이니 절반만큼 위로
    mBeamCollider->SetCollisionProfile("MonsterAttack"); // 네 프로젝트 프로파일에 맞게 변경 가능
    mBeamCollider->SetEnable(true);   // false -> true
    // 충돌 콜백(한 번 닿을 때)
    mBeamCollider->SetCollisionBeginFunc<CPopeBeam>(this, &CPopeBeam::CollisionBeam);

    // 애니메이션 (스프라이트에 붙여야 함)
    mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
    mAnimation->AddSequence("threeAnguishBigBeam", 3.0f, 1.0f, false, false);

    // 시작하자마자 재생
    mAnimation->ChangeAnimation("threeAnguishBigBeam");

    // 데미지 쿨 초기화
    mHitAcc = 0.f;
 
   
    // 애니 중 “실제 발사 시작 프레임”에서 ON
   // mAnimation->AddNotify("threeAnguishBigBeam", 8, this, &CPopeBeam::BeamHitOn);
    // “소멸 시작 프레임”에서 OFF (예: 20프레임)
    //mAnimation->AddNotify("threeAnguishBigBeam", 58, this, &CPopeBeam::BeamHitOff);
    mAnimation->SetEndFunction("threeAnguishBigBeam", this, &CPopeBeam::OnBeamEnd);
    return true;
}

void CPopeBeam::Update(float DeltaTime)
{
    CSceneObject::Update(DeltaTime);

    // 간단 쿨타임
    if (mHitAcc > 0.f)
        mHitAcc -= DeltaTime;

    // (선택) 애니 끝나면 콜라이더 끄고 숨기기 같은 처리 필요하면,
    // 엔진에 맞게 EndFunction/Destroy 처리 붙이면 됨.
}

void CPopeBeam::CollisionBeam(const FVector3D& HitPoint, CColliderBase* Dest)
{
    if (!Dest) return;

    // 데미지 연타 방지(원하면 제거 가능)
    if (mHitAcc > 0.f)
        return;

    CSceneObject* Owner = Dest->GetOwner();
    if (!Owner) return;

    CPlayerObject* Player = dynamic_cast<CPlayerObject*>(Owner);
    if (!Player) return;

    // 데미지
    Player->Damage(mBeamDmg, this);

    // 쿨타임 시작
    mHitAcc = mHitCooldown;
}

void CPopeBeam::BeamHitOn()
{
    if (mBeamCollider) mBeamCollider->SetEnable(true);
}

void CPopeBeam::BeamHitOff()
{
   if (mBeamCollider) mBeamCollider->SetEnable(false);
}

void CPopeBeam::OnBeamEnd()
{
   
    Destroy(); 
 
}