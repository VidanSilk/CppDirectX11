#include "PlayerObject.h"
#include "SpriteEffect.h"
#include "MonsterObject.h"
#include "SceneObject.h"
	
#include "PlayerAction/PlayerMove.h"
#include "PlayerAction/PlayerCombat.h"
#include "PlayerAction/PlayerSkill.h"
#include "PlayerAction/PlayerHealEffect.h"
#include "PlayerAction/PlayerFallingDown.h"
#include "BackFloorTwo.h"
#include "AshFloor.h"
#include "AshPlatform.h"

#include "../Vector3D.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/MovementComponent.h"
#include "../Component/RotationComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/ColliderAABB2D.h"
#include "../Component/ColliderSphere2D.h"
#include "../Component/ColliderOBB2D.h"
#include "../Component/ColliderLine2D.h"
#include "../Component/SpriteComponent.h"
#include "../Component/GravityComponent.h"
#include "../Component/ColliderBase.h"
#include "../Animation/Animation2D.h"

#include "../Scene/Scene.h"
#include "../Scene/Input.h"
#include "../Scene/SceneUIManager.h"

#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Texture/Texture.h"

#include "../Share/Log.h"

#include "../UI/UserWidget/MainWidget.h"
#include "../UI/Common/ProgressBar.h"
#include "../UI/UserWidget/PlayerDieWidget.h"
#include "../UI/UserWidget/StartWidget.h"


CPlayerObject::CPlayerObject()
	: CSceneObject()
{
	mMove = new CPlayerMove;
	mCombat = new CPlayerCombat;
	mSkill = new CPlayerSkill;
	mHeal = new CPlayerHealEffect;
	mFallingDown = new CPlayerFallingDown;
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj)
	: CSceneObject(Obj)
{
	
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj)
	: CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
	SAFE_DELETE(mMove);
	SAFE_DELETE(mCombat);
	SAFE_DELETE(mSkill);
	SAFE_DELETE(mHeal);
	SAFE_DELETE(mFallingDown);
}

bool CPlayerObject::Init()
{
	// 게임 매니져 -> 씬매니져를 통해 -> 현재 씬을 실행시키고
	// 씬에서는 씬에 포함된 오브젝트들을 전부 순회하면서 시점 함수들을 호출해준다. 
	// 오브젝트들은 본인의 루트 컴포넌트를 호출해주면 
	// 루트 컴포넌트는 자식 컴포넌트들을 호출해준다. 


	// 로직 정리
	// 1. 컴포넌트 생성 및 사이즈 세팅 
	//mRoot = CreateComponent<CStaticMeshComponent>();
	mRoot = CreateComponent<CSpriteComponent>();
	mBody = CreateComponent<CColliderAABB2D>();

	mATKCollider = CreateComponent<CColliderAABB2D>();
	mUPATKCollider = CreateComponent<CColliderAABB2D>();
	mParryCollider = CreateComponent<CColliderAABB2D>();
	mSkillCollider = CreateComponent<CColliderAABB2D>();

	// 바닥용 콜라이더
	mMovement = CreateComponent<CMovementComponent>();
	mMoveCollider = CreateComponent<CColliderAABB2D>();
	
	mRoot->AddChild(mMoveCollider);
	mMoveCollider->SetBoxSize(35.f, 5.f); //바닥용 사이즈
	mMoveCollider->SetRelativePos(0.f, -75.0f, 0.f);
	mMoveCollider->SetCollisionProfile("PlayerMove");
	//mMoveCollider->SetEnable(false);

	mRoot->SetTint(1.f, 1.f, 1.f);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetOpacity(1.f);

	//mRoot->SetWorldPos(-400.f, -100.f, 0.f); //스폰 위치 
	mRoot->SetWorldScale(125.f, 135.f);
	SetRootComponent(mRoot);
	
	// 2. UI 위젯바 (체력바 나중에 수정할 예정)
	class CMainWidget* MainWidget = mScene->GetUIManager()->CreateWidget<CMainWidget>("Main");
	mScene->GetUIManager()->AddToViewport(MainWidget);
	mHPBar = MainWidget->HPBar;


	// 3. 애니메이션
	//애니메이션 추가 
	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	mAnimation->AddSequence("PlayerIdle", 1.0f, 1.0f, true, false);
	//움직임 나누줌 
	mAnimation->AddSequence("PlayerRunStart", 1.0f, 1.0f, false, false);
	mAnimation->AddSequence("PlayerRun", 2.0f, 1.2f, true, false);
	mAnimation->AddSequence("PlayerRunStop", 1.0f, 1.0f, false, false);
	// 움직임이 끝나면 바로 IDLE로
	mAnimation->AddSequence("PlayerDodge", 2.5f, 3.0f, false, false);
	mAnimation->SetEndFunction("PlayerDodge", this, &CPlayerObject::DodgeEnd);
	
	mAnimation->AddSequence("PlayerJump", 2.0f, 1.0f, false, false);
	mAnimation->AddSequence("PlayerForwardJump", 2.0f, 1.0f, false, false);
	mAnimation->AddSequence("PlayerJumpLand", 2.0f, 1.0f, false, false);
	mAnimation->SetEndFunction("PlayerJumpLand", this, &CPlayerObject::JumpLandEnd);

	//공격과 패링애니 
	mAnimation->AddSequence("PlayerAttack1", 1.f, 1.5f, false, false);
	mAnimation->AddNotify("PlayerAttack1", 1, this, &CPlayerObject::AttackNotify);
	mAnimation->SetEndFunction("PlayerAttack1", this, &CPlayerObject::AttackEnd);

	mAnimation->AddSequence("PlayerAttack2", 1.f, 1.5f, false, false);
	mAnimation->AddNotify("PlayerAttack2", 1, this, &CPlayerObject::AttackNotify);
	mAnimation->SetEndFunction("PlayerAttack2", this, &CPlayerObject::AttackEnd);

	mAnimation->AddSequence("PlayerAttack3", 1.f, 1.5f, false, false);
	mAnimation->AddNotify("PlayerAttack3", 1, this, &CPlayerObject::AttackNotify);
	mAnimation->SetEndFunction("PlayerAttack3", this, &CPlayerObject::AttackEnd);

	mAnimation->AddSequence("PlayerParry", 1.f, 1.2f, false, false);
	mAnimation->SetEndFunction("PlayerParry", this, &CPlayerObject::ParryEnd);
	
	// --- 업공 / 대쉬공 ---
	mAnimation->AddSequence("PlayerUpATK", 1.f, 1.5f, false, false);
	mAnimation->AddNotify("PlayerUpATK", 1, this, &CPlayerObject::UpATKNotify);
	mAnimation->SetEndFunction("PlayerUpATK", this, &CPlayerObject::AttackEnd);

	mAnimation->AddSequence("PlayerDodgeATK", 2.f, 1.5f, false, false);
	mAnimation->AddNotify("PlayerDodgeATK", 1, this, &CPlayerObject::DodgeATKNotify);
	mAnimation->SetEndFunction("PlayerDodgeATK", this, &CPlayerObject::AttackEnd);

	// --- 패링 성공 후 넉백 애니(= PlayerBack) ---
	mAnimation->AddSequence("PlayerBack", 1.f, 1.f, false, false);
	mAnimation->SetEndFunction("PlayerBack", this, &CPlayerObject::ParryBackEnd);

	// 스킬 시작 모션 중간 프레임에서 발사 (프레임 인덱스는 네 리소스에 맞게 조절)
	mAnimation->AddSequence("PlayerAura", 2.0f, 1.0f, false, false);
	mAnimation->AddNotify("PlayerAura", 30, this, &CPlayerObject::BeamSkillNotify);
	mAnimation->SetEndFunction("PlayerAura", this, &CPlayerObject::BeamSkillEnd);

	// 회복 이펙트 
	// 회복도 클래스로 나눌까? 
	mAnimation->AddSequence("HPRecovery", 2.5f, 1.0f,false, false);
	mAnimation->AddNotify("HPRecovery", 13, this, &CPlayerObject::HPEffectNotify);
	mAnimation->SetEndFunction("HPRecovery", this, &CPlayerObject::HPRecoveryEnd);

	//죽음 
	mAnimation->AddSequence("PlayerDeath", 2.5f, 1.0f, false, false);

	//4. 콜라이더 세팅 
	mRoot->SetFlip(false); // 반전 여부 체크 
	mRoot->AddChild(mBody);
	mBody->SetBoxSize(50.0f, 100.0f);
	mBody->SetCollisionProfile("Player");

	//5. 초기화 설정 
	// 공격 콜라이더 생성하기 
	// 추후에 콜라이더 값 더 수정해주기 
	mCombat->mOwner = this;
	mCombat->mAnimation = mAnimation;
	mCombat->mATKCollider = mATKCollider.Get();  // CSharedPtr면 Get()
	mCombat->mParryCollider = mParryCollider.Get(); // 
	mRoot->AddChild(mATKCollider);
	mATKCollider->SetBoxSize(60.0f, 40.f);          //  공격 콜라이더 세팅 임시값
	mATKCollider->SetRelativePos(50.f, 0.f, 0.f);  // 플레이어 앞쪽에 세팅할 것이다.
	mATKCollider->SetCollisionProfile("PlayerAttack"); // 프로파일은 아마 PlayerAttack로 등록함. 
	mATKCollider->SetEnable(false);

	mRoot->AddChild(mUPATKCollider);
	mUPATKCollider->SetBoxSize(50.f, 90.f);
	mUPATKCollider->SetCollisionProfile("PlayerAttack");
	mUPATKCollider->SetEnable(false);

	mRoot->AddChild(mParryCollider);
	mParryCollider->SetBoxSize(50.f, 50.f);                 // 패링 사이즈
	mParryCollider->SetRelativePos(50.f, 0.f, 0.f);         // 기본은 오른쪽 기준
	mParryCollider->SetCollisionProfile("PlayerParry");     // 패링 프로파일이지만 임시적으로 공격용 프로파일로 등록  
	mParryCollider->SetEnable(false);
															//추후에, 프로파일 매니저 및 게임인포에서 패링용 충돌 채널 등록해주기 or 저걸로 재활용 하기
	mParryCollider->SetEnable(false);
	
	mCombat->Bind(this, mAnimation, mATKCollider.Get(), mUPATKCollider.Get(), mParryCollider.Get());

	mCombat->SetupColliders();

	mATKCollider->SetCollisionBeginFunc(this, &CPlayerObject::OnPlayerAttackColliderHit);
	mUPATKCollider->SetCollisionBeginFunc(this, &CPlayerObject::OnPlayerAttackColliderHit);
	mSkillCollider->SetCollisionBeginFunc(this, &CPlayerObject::OnPlayerSkillColliderHit);
//	mParryCollider->SetCollisionBeginFunc(this, &CPlayerObject::OnPlayerParryColliderHit);

	// 스킬 추가예정 
	// === 스킬 컴포넌트 생성 ===
	//mSkillMotion = CreateComponent<CSpriteComponent>();
	mSkillBeamSprite = CreateComponent<CSpriteComponent>();

	mRoot->AddChild(mSkillBeamSprite);

	// 레이어/기본 세팅

	mSkillBeamSprite->SetPivot(0.5f, 0.1f);
	mSkillBeamSprite->SetRelativePos(0.f, 0.f, 1.f);
	mSkillBeamSprite->SetWorldScale(350.f, 920.f);
	mSkillBeamSprite->SetEnable(false);


	// 애니메이션은 각각의 Sprite에서
	mSkillBeamAnim = mSkillBeamSprite->CreateAnimation2D<CAnimation2D>();

	// 스킬  콜라이더 셋팅 
	mSkillBeamSprite->AddChild(mSkillCollider);
	mSkillCollider->SetBoxSize(350.f, 1000.f);
	mSkillCollider->SetRelativePos(0.f, 0.f, 0.f);
	mSkillCollider->SetCollisionProfile("PlayerAttack");	
	mSkillCollider->SetEnable(false);
	mSkill->SkillBind(this, mAnimation, mSkillBeamSprite, mSkillBeamAnim, mSkillCollider.Get());
	mSkill->Setup();

	//회복 -> 보류 
	mHealFXSprite = CreateComponent<CSpriteComponent>();
	mHealFXAnim = mHealFXSprite->CreateAnimation2D<CAnimation2D>();
	mRoot->AddChild(mHealFXSprite);

	mHealFXSprite->SetPivot(0.275f, 0.375f);
	mHealFXSprite->SetRelativePos(0.f, 0.f); //스킬 크기 
	mHealFXSprite->SetRelativeScale(1.25f, 1.25f);
	mHealFXSprite->SetEnable(false);
	mHealFXSprite->SetOpacity(1.f);
	mHealFXSprite->SetTint(1.f, 1.f, 1.f);

	mHeal->Bind(mHealFXSprite, mHealFXAnim);
	mHeal->Setup();

	// 무브
	mMove->mOwner = this;
	mMove->mMovement = mMovement;
	mMove->mAnimation = mAnimation;

	//6. 무브먼트 컴포넌트 세팅
	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveSpeed(300.f);
	mBaseMoveSpeed = 300.f;
	//중력 컴포넌트 세팅 
	mGravity = CreateComponent<CGravityComponent>();
	mGravity->SetGravity(-3000.f);
	mGravity->SetTerminalVelocity(-1000.f);
	mGravity->SetGrounded(true); // 시작을 바닥이라고 가정하면 true
	//Rotation->SetUpdateComponent(mRoot);
	//7. 카메라 셋팅 
	//mCamera->SetProjectionType(ECameraProjectionType::Ortho);
	//mRoot->AddChild(mCamera);

	
	//8. 플레이어 기본 상태 값 세팅 
	mDefault = PlayerState::Idle;
	mAutoBasePose = true;
	mPlayerDMG = 100.f;

	//9. 입력 키 세팅  
	// 좌우 이동 
	mScene->GetInput()->AddBindKey("MoveLeft", VK_LEFT);
	mScene->GetInput()->AddBindFunction("MoveLeft", EInputType::Hold, this, &CPlayerObject::MoveLeft);
	mScene->GetInput()->AddBindKey("MoveRight", VK_RIGHT);
	mScene->GetInput()->AddBindFunction("MoveRight", EInputType::Hold, this, &CPlayerObject::MoveRight);

	mScene->GetInput()->AddBindKey("DodgeLeft", 'W');
	mScene->GetInput()->AddBindFunction("DodgeLeft", EInputType::Down, this, &CPlayerObject::DodgeLeft);

	mScene->GetInput()->AddBindKey("DodgeRight",'E');
	mScene->GetInput()->AddBindFunction("DodgeRight", EInputType::Down, this, &CPlayerObject::DodgeRight);
	//점프 스페이스바 스페이스바도 혹시 바인드키로 셋팅해야하는가? 
	
	// 인풋갑 수정할거 
	mScene->GetInput()->AddBindKey("Jump", 'C');
	mScene->GetInput()->AddBindFunction("Jump", EInputType::Down, this, &CPlayerObject::Jump);

	// 기본 공격		
	mScene->GetInput()->AddBindKey("Attack", 'Z');
	mScene->GetInput()->AddBindFunction("Attack", EInputType::Hold, this, &CPlayerObject::Attack);

	mScene->GetInput()->AddBindKey("UpATK", 'A');
	mScene->GetInput()->AddBindFunction("UpATK", EInputType::Down, this, &CPlayerObject::UpATK);

	// 대쉬공격 S
	mScene->GetInput()->AddBindKey("DodgeATK", 'S');
	mScene->GetInput()->AddBindFunction("DodgeATK", EInputType::Down, this, &CPlayerObject::DodgeATK);

	//패링 
	mScene->GetInput()->AddBindKey("ParryCounter", 'X');
	mScene->GetInput()->AddBindFunction("ParryCounter", EInputType::Down, this, &CPlayerObject::ParryCounter);
	mParryCollider->SetCollisionBeginFunc(this, &CPlayerObject::OnPlayerParryColliderHit);

	mAnimation->AddSequence("PlayerFallingOver", 1.f, 1.f, false, false);
	mAnimation->SetEndFunction("PlayerFallingOver", this, &CPlayerObject::FallingOverEnd);

	mAnimation->AddSequence("PlayerGettingUp", 1.f, 1.f, false, false);
	mAnimation->SetEndFunction("PlayerGettingUp", this, &CPlayerObject::GettingUpEnd);

	// 스킬 Q
	mScene->GetInput()->AddBindKey("BeamSkill", 'Q');
	mScene->GetInput()->AddBindFunction("BeamSkill", EInputType::Down, this, &CPlayerObject::BeamSkill);

	//회복 키 F
	mScene->GetInput()->AddBindKey("HPRecovery", 'F');
	mScene->GetInput()->AddBindFunction("HPRecovery", EInputType::Down, this, &CPlayerObject::HPrecovery);

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//행동이 끝나면 기본 IDLE로 돌아가는건 업데이트쪽이 베스티인듯?
	//아니면 함수 호출 때마다 하는건? 
	PlayerState prevState = mDefault;

	switch (mDefault)
	{
	case PlayerState::Idle:
		if (mMovement->GetVelocityLength() == 0.0f && mAutoBasePose)
		{
			mAnimation->ChangeAnimation("PlayerIdle");

		}
		break;
	case PlayerState::Move:
		if (mAutoBasePose == false)
			mMove->Move();

		if (mMovement->GetVelocityLength() <= 0.0f)
		{
			mAutoBasePose = true;
			mDefault = PlayerState::Idle;
			if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
		}
		break;
	case PlayerState::Jump:
		// 공중에서 방향 점프면 x 이동만 주고, 착지 애니(mLanding)면 아무것도 안 함
		if (!mLanding && mJumpDir != 0)
		{
			mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * (float)mJumpDir);
		}
		break;
	case PlayerState::ATK:
		//Attack(DeltaTime);
		mCombat->Update(DeltaTime); 
		break;
	case PlayerState::Parry:
		//ParryCounter(DeltaTime);
		break;
	case PlayerState::HPRecovery:
		//HPrecovery(DeltaTime);
		break;
	case PlayerState::Dodge:
		UpdateDodge(DeltaTime);
		break;
	case PlayerState::PlayerSkill:
		break;
	case PlayerState::FallingDown:
		break;
	case PlayerState::KnockBack:
		UpdateKnockBack(DeltaTime);
		break;
	case PlayerState::GettingUp:
		break;
	case PlayerState::PlayerHitMotion:
		break;
	case PlayerState::Death:
		PlayerDeath(DeltaTime);
		break;
	default:
		break;
	}

	if (prevState == PlayerState::PlayerSkill && mDefault != PlayerState::PlayerSkill)
	{
		if (mSkill) mSkill->SkillEnd();
	}
	
	if (mGravity) mGravity->SetGrounded(false);

	bool grounded = false;

	// 플랫폼 먼저
	for (size_t i = 0; i < mAshPlatforms.size(); ++i)
	{
		CAshPlatform* p = mAshPlatforms[i];
		if (!p) continue;

		p->CheckFloorCollider(this);
		if (mGravity && mGravity->IsGrounded())
		{
			grounded = true;
			break;
		}
	}

	// 플랫폼 아니면 바닥
	if (!grounded && mAshFloor)
	{
		mAshFloor->CheckFloorCollider(this);
		grounded = (mGravity && mGravity->IsGrounded());
	}

	if (!grounded && mBackFloorTwo)
	{
		mBackFloorTwo->CheckFloorCollider(this);
	}

	// 바닥 체크 끝난 뒤
	bool nowGrounded = (mGravity && mGravity->IsGrounded());

	if (!mWasGrounded && nowGrounded)
	{
		if (mDefault == PlayerState::Jump && !mLanding)
		{
			mLanding = true;
			mJumpDir = 0;               // 착지 중엔 앞으로 밀지 않음
			mMove->JumpLanding();       // "PlayerJumpLand" 재생
		}
	}

	mWasGrounded = nowGrounded;

}

float CPlayerObject::Damage(float Attack, CSceneObject* Obj)
{
	if (!mDamageEnable) return 0.f;

	float dmg = CSceneObject::Damage(Attack, Obj);
	mNowHp -= dmg;
	if (mNowHp < 0.f) mNowHp = 0.f;
	if (mHPBar) mHPBar->SetPercent(mNowHp / mMaxHp);

	if (mNowHp <= 0.f)
	{
		mAutoBasePose = false;
		mDefault = PlayerState::Death;
		if (mAnimation) mAnimation->ChangeAnimation("PlayerDeath");
		return dmg;
	}

	//  공격/패링/스킬 끊기
	if (mCombat) mCombat->CancelAll();
	if (mSkill)  mSkill->SkillEnd();

	mAutoBasePose = false;
	mDefault = PlayerState::FallingDown;
	if (mAnimation) mAnimation->ChangeAnimation("PlayerFallingOver");
	return dmg;
}

void CPlayerObject::Damage(float Damage)
{
	//Damage(Damage, nullptr);
	this->Damage(Damage, (CSceneObject*)nullptr);
}

void CPlayerObject::MoveLeft(float DeltaTime)
{
	if (mDefault == PlayerState::Dodge || mDefault == PlayerState::PlayerSkill || mDefault == PlayerState::Death)
		return;

	mLastMoveDir = -1;
	mRoot->SetFlip(true);

	// 점프 중이면 상태를 Move로 바꾸지 말고 공중 이동만
	if (mDefault == PlayerState::Jump)
	{
		mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * (-1));
		return;
	}

	mAutoBasePose = false;
	mDefault = PlayerState::Move;
	mMove->Move();
	mMovement->AddMove(mRootComponent->GetAxis(EAxis::X) * (-1));
}

void CPlayerObject::MoveRight(float DeltaTime)
{
	if (mDefault == PlayerState::Dodge || mDefault == PlayerState::PlayerSkill || mDefault == PlayerState::Death)
		return;

	mLastMoveDir = 1;
	mRoot->SetFlip(false);

	if (mDefault == PlayerState::Jump)
	{
		mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));
		return;
	}

	mAutoBasePose = false;
	mDefault = PlayerState::Move;
	mMove->Move();
	mMovement->AddMove(mRootComponent->GetAxis(EAxis::X));
}

void CPlayerObject::StartDodge(int dir)
{
	mAutoBasePose = false;
	mDefault = PlayerState::Dodge;

	mDodgeDir = dir;
	mDodgeTime = 0.f;

	// 방향/애니는 1회만
	mRoot->SetFlip(dir < 0);
	mMove->Dodge();

	
	FVector3D pos = GetWorldPosition();      // SceneObject에 있는 GetWorldPosition() 사용 중이었지
	mDodgeStartX = pos.x;
	mDodgeTargetX = mDodgeStartX + (mDodgeDistance * (float)dir);

	// (선택) 회피 중 이동컴포넌트 속도 변경은 필요없어짐
	// if (mMovement) mMovement->SetMoveSpeed(mBaseMoveSpeed * mDodgeSpeedMul);
}

//회피
void CPlayerObject::DodgeLeft(float DeltaTime)
{
	if (mDefault == PlayerState::Dodge) return;
	if (mDefault == PlayerState::PlayerSkill || mDefault == PlayerState::Death) return;

	StartDodge(-1);

}

void CPlayerObject::DodgeRight(float DeltaTime)
{
	if (mDefault == PlayerState::Dodge) return;
	if (mDefault == PlayerState::PlayerSkill || mDefault == PlayerState::Death) return;

	StartDodge(1);
}

void CPlayerObject::UpdateDodge(float DeltaTime)
{
	mDodgeTime += DeltaTime;

	// 보간
	float t = mDodgeTime / mDodgeDuration;
	if (t > 1.f) t = 1.f;

	//  X만 강제 이동(점프/중력 Y는 유지)
	FVector3D pos = GetWorldPosition();
	pos.x = mDodgeStartX + (mDodgeTargetX - mDodgeStartX) * t;

	SetWorldPos(pos);

	if (t >= 1.f)
		DodgeEnd();
}

void CPlayerObject::DodgeEnd()
{
	if (mDefault != PlayerState::Dodge) return;

	mDodgeDir = 0;
	mDodgeTime = 0.f;

	mAutoBasePose = true;
	mDefault = PlayerState::Idle;
	if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
}

void CPlayerObject::Jump(float DeltaTime)
{

	if (!mGravity) return;
	if (!mGravity->IsGrounded()) return;
	if (mDefault == PlayerState::Dodge || mDefault == PlayerState::PlayerSkill || mDefault == PlayerState::Death)
		return;

	const bool wantForward = (mLastMoveDir != 0); // 또는 (mMovement->GetVelocityLength() > 0)

	mAutoBasePose = false;
	mDefault = PlayerState::Jump;
	mLanding = false;

	if (wantForward)
	{
		mJumpDir = mLastMoveDir;
		mMove->ForwardJump();
	}
	else
	{
		mJumpDir = 0;
		mMove->Jump();
	}

	mGravity->GravityJump(1000.f);

}

void CPlayerObject::JumpForward(float DeltaTime)
{
}

void CPlayerObject::JumpDown(float DeltaTime)
{
	mAutoBasePose = false;
	mDefault = PlayerState::Jump;
	mMove->JumpOff();
	//mAnimation->ChangeAnimation("PlayerJump");
	mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * (-2));

}

void CPlayerObject::JumpLandEnd()
{
	if (!mLanding) return;

	mLanding = false;
	mAutoBasePose = true;
	mDefault = PlayerState::Idle;
	if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
}

void CPlayerObject::Attack(float DeltaTime)
{
	mAutoBasePose = false;
	mDefault = PlayerState::ATK;
	mCombat->OnComboInput(mRoot->GetIsFlip());

	//히트포인트에 타격시 데미지를 입게 해준다.
	//CPlayerATK* ATK = mScene->CreateObj<CPlayerATK>("ATKAction");
	//ATK->ATKAction(DeltaTime);

}

void CPlayerObject::AttackEnd()
{

	const bool keepAttacking = mCombat->OnAttackEnd();
	if (!keepAttacking)
	{
		mAutoBasePose = true;
		mDefault = PlayerState::Idle;
		if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
	}

	CLog::PrintLog("AttackEnd");

}

void CPlayerObject::AttackNotify()
{
	mCombat->ComboNotify(mRoot->GetIsFlip());
	CLog::PrintLog(mATKCollider && mATKCollider->IsEnable() ? "ATKCollider ON" : "ATKCollider OFF"); //콜라이더 체크용 
}

void CPlayerObject::OnAttackHit(CSceneObject* Other)
{
	CMonsterObject* mon = dynamic_cast<CMonsterObject*>(Other);
	if (!mon) return;

	mon->Damage(mPlayerDMG, this);

	if (mCombat)
		mCombat->ConfirmHit();
}

void CPlayerObject::UpATK(float DeltaTime)
{
	mAutoBasePose = false;
	mDefault = PlayerState::UpATK;
	mCombat->OnUpAtkInput(mRoot->GetIsFlip());
}

void CPlayerObject::UpATKNotify()
{
	mCombat->UpAtkNotify(mRoot->GetIsFlip());
}

void CPlayerObject::DodgeATK(float DeltaTime)
{
	if (mDefault == PlayerState::Death) return;

	mDodgeDistance = 300.f; // 회피공격은 짧게
	StartDodge(mRoot->GetIsFlip() ? -1 : 1);


	mAutoBasePose = false;
	mDefault = PlayerState::ATK;
	mCombat->OnDodgeAtkInput(mRoot->GetIsFlip());
}

void CPlayerObject::DodgeATKNotify()
{
	mCombat->DodgeAtkNotify(mRoot->GetIsFlip());
}

//ATK 방어기능이니 방어쪽으로 옮길 예정 
void CPlayerObject::ParryCounter(float DeltaTime)
{
	 mAutoBasePose = false;
    mDefault = PlayerState::Parry;
    mCombat->OnParryInput(mRoot->GetIsFlip());

	CLog::PrintLog(mParryCollider && mParryCollider->IsEnable() ? "mParryCollider ON" : "mParryCollider OFF"); // 콜라이더 체크용 

}

void CPlayerObject::ParryBack(float DeltaTime)
{
}


void CPlayerObject::ParryEnd()
{
	// 패링 창 닫고, 결과를 mLastParrySuccess에 저장
	mCombat->OnParryEnd();

	if (mCombat->WasParrySuccess())
	{
		// 성공: 넉백/백스텝 애니
		mAutoBasePose = false;
		mDefault = PlayerState::KnockBack;

		if (mAnimation) mAnimation->ChangeAnimation("PlayerBack");

		// 넉백 이동을 실제로 주고 싶으면 여기서 값 세팅해서 Update에서 처리하면 됨
		// mKnockBackDir = mRoot->GetIsFlip() ? 1 : -1;  // 예시(방향은 네 게임 감각대로)
		// mKnockBackTime = 0.f;
	}
	else
	{
		// 실패: 데미지
		Damage(mCombat->GetParryFailDamage());

		// 필요하면 넉다운으로
		// mAutoBasePose = false;
		// mDefault = PlayerState::KnockDown;
		// mAnimation->ChangeAnimation("PlayerKnockDown");
		// 여기선 일단 Idle 복귀로만 처리해도 OK
		mAutoBasePose = true;
		mDefault = PlayerState::Idle;
		if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
	}

	// 결과는 1회성으로 쓰고 지우기
	mCombat->ClearParryResult();
}

void CPlayerObject::ParryBackEnd()
{
	mAutoBasePose = true;
	mDefault = PlayerState::Idle;
	if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
}

void CPlayerObject::StartKnockBack(int dir, float dist)
{
	mKnockBacking = true;
	mKnockBackTime = 0.f;

	FVector3D pos = GetWorldPosition();
	mKnockBackStartX = pos.x;
	mKnockBackTargetX = mKnockBackStartX + dist * (float)dir;
}

void CPlayerObject::UpdateKnockBack(float DeltaTime)
{
	mKnockBackTime += DeltaTime;

	float t = mKnockBackTime / mKnockBackDuration;
	if (t > 1.f) t = 1.f;

	FVector3D pos = GetWorldPosition();
	pos.x = mKnockBackStartX + (mKnockBackTargetX - mKnockBackStartX) * t;
	SetWorldPos(pos);

	if (t >= 1.f)
	{
		// 이동만 끝내고 애니 끝까지 보여주고 싶으면 여기서 Idle로 안 돌려도 됨.
		// “이동 끝나면 바로 Idle” 원하면 아래 호출
		// ParryBackEnd(); 또는 KnockBackEnd() 만들어서 처리

	}

}


void CPlayerObject::BeamSkill(float DeltaTime)
{ 

	if (mDefault == PlayerState::PlayerSkill) return;
	if (mDefault == PlayerState::Dodge || mDefault == PlayerState::Death) return;

	mAutoBasePose = false;
	mDefault = PlayerState::PlayerSkill;

	mSkillBeamSprite->SetEnable(true);
	mSkillCollider->SetEnable(false);

	// 엔진에 따라 ChangeAnimation이 같은 이름이면 무시될 수 있어서 2단계로 강제
	if (mSkillBeamAnim)
	{
		mSkillBeamAnim->ChangeAnimation("None");     // 없는 시퀀스면, 다른 더미 시퀀스라도 OK
		mSkillBeamAnim->ChangeAnimation("SkillBeam"); // 실제 빔 시퀀스
	}

	// 플레이어 시전 모션도 동일하게 "강제 재시작" 해주는 게 안전
	if (mAnimation)
	{
		mAnimation->ChangeAnimation("PlayerIdle");
		mAnimation->ChangeAnimation("PlayerAura");
	}

	mSkill->skillAction(mRoot->GetIsFlip());
}

void CPlayerObject::BeamSkillNotify() {
	if (mDefault != PlayerState::PlayerSkill) return; // 안전장치
	mSkill->Fire(mRoot->GetIsFlip());

}

void CPlayerObject::BeamSkillEnd()
{
	mSkill->SkillEnd();        // 스킬 정리(빔/콜라이더 OFF)

	mAutoBasePose = true;
	mDefault = PlayerState::Idle;

	// 바로 Idle로 보내고 싶으면(선택)
	if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
}


// 회복 
void CPlayerObject::HPrecovery(float DeltaTime)
{
	if (mDefault == PlayerState::HPRecovery) return;
	
	mAutoBasePose = false;
	mDefault = PlayerState::HPRecovery;
	
	mAnimation->ChangeAnimation("HPRecovery");
}

void CPlayerObject::HPEffectNotify()
{
	//체스트용 
	//CSpriteEffect* fx = mScene->CreateObj<CSpriteEffect>("HealFXEffect");
	//fx->SetWorldPos(GetWorldPosition());            // 플레이어 위치
	//fx->SetWorldScale(125.f, 175.f, 1.f);           // 적당히
	//fx->SetAnimation("HealFX", 3.0f, 1.0f, false, false);

	//회복 로직 
	mNowHp += mHpRecovery;
	if (mNowHp >= mMaxHp) {
		mNowHp = mMaxHp;
	}
	
	mHPBar->SetPercent(mNowHp / mMaxHp);
	mHeal->Play(mRoot->GetIsFlip());
	CLog::PrintLog("HPEffect");
}

void CPlayerObject::HPRecoveryEnd()
{

    mAutoBasePose = true;
    mDefault = PlayerState::Idle;
}

//죽음
void CPlayerObject::PlayerDeath(float DeltaTime)
{
	mAutoBasePose = false;
	mDefault = PlayerState::Death;
	if (mMaxHp <= 0.0f) {
		mAnimation->ChangeAnimation("PlayerDeath");
	}
	
	if (!mDieUIShown)
	{
		mDieUIShown = true;
		CPlayerDieWidget* DieUI = mScene->GetUIManager()->CreateWidget<CPlayerDieWidget>("PlayerDieUI");
		mScene->GetUIManager()->AddToViewport(DieUI);    

		//DieUI->SetOnReturnToStart( [this]()
		//	{
		//		/*	CStartWidget* Start = mScene->GetUIManager()->CreateWidget<CStartWidget>("StartWidget");
		//		mScene->GetUIManager()->AddToViewport(Start); 
		//		일단 넘어가기
		//		*/
		//	}
		//  );

	}
}


void CPlayerObject::OnPlayerAttackColliderHit(const FVector3D& HitPoint, CColliderBase* Dest)
{
	if (!Dest) return;

	CSceneObject* other = Dest->GetOwner();
	if (!other) return;

	// 몬스터만 처리
	CMonsterObject* mon = dynamic_cast<CMonsterObject*>(other);
	if (!mon) return;

	// 데미지
	mon->Damage(mPlayerDMG, this);

	// 콤보/히트확정(필요하면)
	if (mCombat) mCombat->ConfirmHit();

	CLog::PrintLog("PlayerAttack Hit Monster");
}

void CPlayerObject::OnPlayerSkillColliderHit(const FVector3D& HitPoint, CColliderBase* Dest)
{
	if (!Dest) return;

	CSceneObject* other = Dest->GetOwner();
	if (!other) return;

	CMonsterObject* mon = dynamic_cast<CMonsterObject*>(other);
	if (!mon) return;

	mon->Damage(500.f, this); // 스킬 데미지 예시
	CLog::PrintLog("PlayerSkill Hit Monster");


}

void CPlayerObject::OnPlayerParryColliderHit(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CLog::PrintLog("AttackCollider BEGIN"); //  여기 찍히나?
	if (!Dest) return;

	CSceneObject* other = Dest->GetOwner();
	if (!other) return;

	// 여기서 "막을 수 있는 것"만 필터링하는 게 베스트
	// (미사일/근접공격 콜라이더 등)
	if (mCombat)
		mCombat->ConfirmParrySuccess();
}


void CPlayerObject::FallingOverEnd()
{
	mDefault = PlayerState::GettingUp;
	if (mAnimation) mAnimation->ChangeAnimation("PlayerGettingUp");
}

void CPlayerObject::GettingUpEnd()
{
	mAutoBasePose = true;
	mDefault = PlayerState::Idle;
	if (mAnimation) mAnimation->ChangeAnimation("PlayerIdle");
}