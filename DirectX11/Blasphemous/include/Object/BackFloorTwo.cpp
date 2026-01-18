#include "BackFloorTwo.h"
#include "PlayerObject.h"
#include "MonsterObject.h"
#include "../Scene/Scene.h"
#include "../Component/SpriteComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/GravityComponent.h"
#include "../Vector3D.h"
#include "../Share/Log.h"

CBackFloorTwo::CBackFloorTwo()
{
}

CBackFloorTwo::CBackFloorTwo(const CBackFloorTwo& Obj)
{
}

CBackFloorTwo::CBackFloorTwo(CBackFloorTwo&& Obj)
{
}

CBackFloorTwo::~CBackFloorTwo()
{
}

bool CBackFloorTwo::Init()
{
	mFloor2 = CreateComponent<CSpriteComponent>(); //바닥용 시트2
	mFloorCollider = CreateComponent<CColliderAABB2D>(); // 페이즈1 바닥용 콜라이더 

	//mFloor2->SetTexture("pontiffFloor2While", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_2.png"));
    mFloor2->SetTexture("pontiffFloor2While", TEXT("Texture\\RealAsset\\Map\\4\\Pontiff-Boss-Floor-Layer.png"));
	mFloor2->SetTint(1.f,1.f,1.f);
	mFloor2->SetPivot(0.5f, 0.3f);
	mFloor2->SetOpacity(0.5f);
	mFloor2->SetUseTime(false);
    mFloor2->SetWorldScale(1280.f,250.f);
	SetRootComponent(mFloor2);
	
	//바닥 콜라이더
	mFloor2->AddChild(mFloorCollider);                 //  mFloor2와 "연결"
	mFloorCollider->SetCollisionProfile("Floor");      //프로파일 추가안함 추후에 해줄 예정 
	mFloorCollider->SetBoxSize(1280.f, 15.f);           //  바닥 폭/두께(두께는 얇게
	mFloorCollider->SetRelativePos(0.f, 0.f, 0.f);     //  mFloor2 기준으로 위치 보정f
	mFloorCollider->SetEnable(true);
	
	return true;
}

void CBackFloorTwo::CheckFloorCollider(CPlayerObject* Obj) 
{
    if (!Obj) return;
    if (!mFloorCollider) return;

    CColliderAABB2D* playerCollider = Obj->GetPlayerMoveCollider();
    CColliderAABB2D* floorCollider = mFloorCollider.Get();
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

        //// 진짜 착지 순간만 로그
        //if (!wasGrounded)
        //    CLog::PrintLog("Landed!");
    }
    else
    {
        // 옆면/이상 케이스면 공중 처리
        gravity->SetGrounded(false);
    }
}

//몬스터용 콜라이더 체크 근데 몬스터는 점프 안하는데 콜라이더 체크를 해줘야하는가? 
// 점프를 안해도 일반 몬스터 대비용으로 두는게 좋을듯 
// 보스패턴 떄문에 점프는 아니여도 콜라이더는 ㄴ추가해야함 
void CBackFloorTwo::CheckFloorCollider(CMonsterObject* Obj)
{

	//if (!mFloorCollider || !Obj) return;

	//CColliderAABB2D* MonsterCollider = Obj->GetMonsterMoveCollider();
	//CColliderAABB2D* floorCollider = mFloorCollider.Get();
	//if (!MonsterCollider || !floorCollider) return;

	//FVector3D hit;
	//if (!floorCollider->Collision(hit, floorCollider)) return;

	//const float MonsterMinY = MonsterCollider->GetMin().y;
	//const float MonsterMaxY = MonsterCollider->GetMax().y;

	//const float floorMinY = floorCollider->GetMin().y;
	//const float floorMaxY = floorCollider->GetMax().y;


	//const float MonsterCenterY = (MonsterMinY + MonsterMaxY) * 0.5f;
	//const float floorCenterY = (floorMinY + floorMaxY) * 0.5f;

	//if (MonsterCenterY >= floorCenterY)
	//{
	//	// 겹친 만큼 위로 올려준다
	//	const float penetration = floorMaxY - MonsterMinY;
	//	if (penetration > 0.f)
	//	{
	//		FVector3D pos = Obj->GetWorldPosition();
	//		pos.y += penetration + 0.1f;
	//		Obj->SetWorldPos(pos);
	//		// 나중에 점프도 추가하기 
	//	}
	//}
}

