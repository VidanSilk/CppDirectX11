#include "AshFloor.h"
#include "PlayerObject.h"
#include "../Scene/Scene.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/GravityComponent.h"
#include "../Vector3D.h"
#include "../Share/Log.h"

CAshFloor::CAshFloor()
{
}

CAshFloor::CAshFloor(const CAshFloor& Obj)
{
}

CAshFloor::CAshFloor(CAshFloor&& Obj)
{
}

CAshFloor::~CAshFloor()
{
}

bool CAshFloor::Init() {
    mAshFloor = CreateComponent<CSpriteComponent>();
    mAshFloorCollider = CreateComponent<CColliderAABB2D>();
    mAshFloor->SetTexture("AshFloor", TEXT("Texture\\RealAsset\\Map\\4\\ash-mountain-spritesheet_11.png"));
    mAshFloor->SetTint(1.f, 1.f, 1.f);
    mAshFloor->SetPivot(0.5f, 0.2f);
    mAshFloor->SetOpacity(1.0f);
    mAshFloor->SetUseTime(false);
    mAshFloor->SetWorldScale(1280.f, 60.f);
    SetRootComponent(mAshFloor);
    
    //바닥 콜라이더
    mAshFloor->AddChild(mAshFloorCollider);
    mAshFloorCollider->SetCollisionProfile("Floor");
    
    mAshFloorCollider->SetBoxSize(1280.f, 30.f);  
    mAshFloorCollider->SetRelativePos(0.f, 0.f, 0.f);
  
    mAshFloorCollider->SetEnable(true);
	return true;
}

void CAshFloor::CheckFloorCollider(CPlayerObject* Obj)
{
    if (!Obj) return;
    if (!mAshFloorCollider) return;

    CColliderAABB2D* playerCollider = Obj->GetPlayerMoveCollider();
    CColliderAABB2D* floorCollider = mAshFloorCollider.Get();
    if (!playerCollider || !floorCollider) return;

    CGravityComponent* gravity = Obj->GetGravity();
    if (!gravity) return;

    const bool wasGrounded = gravity->IsGrounded();

    FVector3D hit;
    const bool bHit = playerCollider->Collision(hit, floorCollider);
    if (!bHit)
    {
        gravity->SetGrounded(false);
        return;
    }

    // 상승 중이면 절대 착지 처리하지 않음
    const float velY = gravity->GetVelocityY();
    if (velY > 0.f)
    {
        gravity->SetGrounded(false);
        return;
    }

    const float playerMinY = playerCollider->GetMin().y;
    const float floorMaxY = floorCollider->GetMax().y;

    const float penetration = floorMaxY - playerMinY;

    // penetration이 아주 작거나 0이면 이미 거의 맞닿아 있는 상태일 수 있으니 tolerance 적용
    if (penetration > -0.5f) // (-0.5~0)도 접촉으로 인정 (엔진에 맞게 값 조절)
    {
        if (penetration > 0.f)
        {
            FVector3D pos = Obj->GetWorldPosition();
            pos.y += penetration;        // +0.1 같은 epsilon은 일단 빼자(떨림 원인)
            Obj->SetWorldPos(pos);
        }

        gravity->SetGrounded(true);

        // 진짜 착지 순간만 로그
       // if (!wasGrounded)
            //CLog::PrintLog("Landed!");
    }
    else
    {
        // 옆면/이상 케이스면 공중 처리
        gravity->SetGrounded(false);
    }

}
