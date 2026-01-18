#include "PlayerMove.h"
#include "../../Animation/Animation2D.h"
#include "../PlayerObject.h"

//#include "../../Component/StaticMeshComponent.h"
//#include "../../Component/ColliderAABB2D.h"
//#include "../../Component/MovementComponent.h"
//#include "../../Component/SpriteComponent.h"
//
//#include "../../Scene/Scene.h"
//#include "../../Scene/Input.h"
//
//#include "../../Asset/Animation/Animation2DData.h"
//#include "../../Asset/Texture/Texture.h"

//#include "../../Share/Log.h"

//여기서 점프 중력 구현해야할 수도 있음. 
CPlayerMove::CPlayerMove() { }
CPlayerMove::CPlayerMove(const CPlayerMove& Move) { }
CPlayerMove::CPlayerMove(CPlayerMove&& Move) { }
CPlayerMove::~CPlayerMove() {}

bool CPlayerMove::Init() {



	return true;
} 

void CPlayerMove::Update(float DeltaTime){


}

void CPlayerMove::Move()
{
	//mAnimation->ChangeAnimation("PlayerRunStart");
	mAnimation->ChangeAnimation("PlayerRun");
	//mAnimation->ChangeAnimation("PlayerRunStop");
}

void CPlayerMove::Dodge()
{
	mAnimation->ChangeAnimation("PlayerDodge");
}

//대기
void CPlayerMove::Jump() {
	mAnimation->ChangeAnimation("PlayerJump");
}
void CPlayerMove::JumpOff() {
	mAnimation->ChangeAnimation("PlayerJumpDown");
}
void CPlayerMove::ForwardJump() {
	mAnimation->ChangeAnimation("PlayerForwardJump");
}

void CPlayerMove::JumpLanding()
{
	mAnimation->ChangeAnimation("PlayerJumpLand");
}

