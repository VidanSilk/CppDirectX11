#include "Animation2DManager.h"
#include "Animation2DData.h"
#include "../../Animation/Animation2D.h"
#include "../../Share/Log.h"

CAnimation2DManager::CAnimation2DManager()
{
}

CAnimation2DManager::~CAnimation2DManager()
{
	CAnimation2D::DestroyCBuffer();
}

bool CAnimation2DManager::Init()
{
	CLog::PrintLog("CAnimation2DManager::Init Start");

	//애니메이션용 상수 버퍼 생성
	CAnimation2D::CreateCBuffer();
	//애니메이션을 하나 등록하였다.

	///////////////////////////////////////////////////////////////////////////////////
	//플레이어 등록 
	//penintent_idle_anim_0~12
	CLog::PrintLog("CAnimation2DManager::PlayerIdle Start");
	std::vector<const TCHAR*> FileNames;
	CreateAnimation("PlayerIdle");
	SetAnimationTextureType("PlayerIdle" , EAnimationTextureType::Frame);
	TCHAR IdlePath[13][MAX_PATH] = {};
	FileNames.clear();
	//penintent_idle_anim_
	for (int i = 0; i < 13; i++)
	{
		wsprintf(IdlePath[i], TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Idle\\penintent_idle_anim_%d.png"), i);
		FileNames.emplace_back(IdlePath[i]);
	}
	SetTexture("PlayerIdle", "PlayerIdle", FileNames);
	AddFrameCount("PlayerIdle", 13, 0.f, 0.f, 100.f, 100.f);

	// 플레이어 움직임 애니메이션 등록! (Move - 관련!)  Penitent_Move
	// 달리기 RUN
	CreateAnimation("PlayerRunStart");
	SetAnimationTextureType("PlayerRunStart", EAnimationTextureType::Frame);
	FileNames.clear();
	//달리기 시작  penintent_start_run_anim_0 ~ 7 8장 
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_start_run_anim_7.png"));
	SetTexture("PlayerRunStart", "PlayerRunStart", FileNames);
	AddFrameCount("PlayerRunStart", 8, 0.f, 0.f, 100.f, 100.f);


	CLog::PrintLog("CAnimation2DManager::PlayerRun Start");
	CreateAnimation("PlayerRun");
	SetAnimationTextureType("PlayerRun", EAnimationTextureType::Frame);
	FileNames.clear();
	// 달리는 동작penitent_running_anim_0 ~ 13 14장
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penitent_running_anim_13.png"));
	SetTexture("PlayerRun", "PlayerRun", FileNames);
	AddFrameCount("PlayerRun", 14, 0.f, 0.f, 100.f, 100.f);

	CLog::PrintLog("CAnimation2DManager::RunStop");
	CreateAnimation("PlayerRunStop");
	SetAnimationTextureType("PlayerRunStop", EAnimationTextureType::Frame);
	FileNames.clear();
	//달리기 멈춤 penintent_stop_run_anim_0 ~ 6 7장
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_Running\\penintent_stop_run_anim_6.png"));
	SetTexture("PlayerRunStop", "PlayerRunStop", FileNames);
	AddFrameCount("PlayerRunStop", 7, 0.f, 0.f, 100.f, 100.f);
	
	//회피 추가 
	// penitent_start_to_run_from_dodge_anim_5 6 7 8 9 
	CLog::PrintLog("CAnimation2DManager::Dodge Check");
	CreateAnimation("PlayerDodge");
	SetAnimationTextureType("PlayerDodge", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\RunFromDodge\\penitent_dodge_anim_20.png"));
	SetTexture("PlayerDodge", "PlayerDodge", FileNames);
	AddFrameCount("PlayerDodge", 13, 0.f, 0.f, 100.f, 100.f);
	
	//회피 공격 
	// penitent_dodge_attack_anim_1 ~ 28 쪼갬
	CLog::PrintLog("CAnimation2DManager::PlayerDodgeATK");
	CreateAnimation("PlayerDodgeATK");
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\Penitent_Dodge\\penitent_dodge_attack_anim_25.png"));
	SetAnimationTextureType("PlayerDodgeATK", EAnimationTextureType::Frame);
	SetTexture("PlayerDodgeATK", "PlayerDodgeATK", FileNames);
	AddFrameCount("PlayerDodgeATK", 25, 0.f, 0.f, 100.f, 100.f);

	// 참회자 점프  - 하단 점프, 
	// 앞으로 이동하면서 점프 - penitent_jum_forward_anim_0
	// 점프 - Texture\\RealAsset\\PenitentPlayer\\penitent_jump_anim_0 ~ 4
	// 하단 - penitent_jumpoff_new_
	CLog::PrintLog("CAnimation2DManager::PlayerJump Start");
	CreateAnimation("PlayerJump");
	SetAnimationTextureType("PlayerJump", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR JumpPath[5][MAX_PATH] = {};
	for (int i = 0; i < 5; i++)
	{
		wsprintf(JumpPath[i], TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\Jump\\penitent_jump_anim_%d.png"), i);
		FileNames.emplace_back(JumpPath[i]);
	}
	SetTexture("PlayerJump", "PlayerJump", FileNames);
	AddFrameCount("PlayerJump", 5, 0.f, 0.f, 100.f, 100.f);

	CLog::PrintLog("CAnimation2DManager::PlayerForwardJump Start");
	// 앞으로 가면서 점프 중간에 8번, 9번 사진이 없음 (하드코딩)
	CreateAnimation("PlayerForwardJump");
	SetAnimationTextureType("PlayerForwardJump", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_7.png"));
	//아마 이사이에 추가적인 상호작용같은걸 추가해야할것 같은데 ?
	// 공격 동작 들어간듯? 
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpForward\\penitent_jum_forward_anim_16.png"));
	SetTexture("PlayerForwardJump", "PlayerForwardJump", FileNames);
	AddFrameCount("PlayerForwardJump", 15, 0.f, 0.f, 100.f, 100.f);

	CLog::PrintLog("CAnimation2DManager::PlayerJumpDown Start");
	//하단 점프 
	CreateAnimation("PlayerJumpDown");
	SetAnimationTextureType("PlayerJumpDown", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpOff\\penitent_jumpoff_new_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpOff\\penitent_jumpoff_new_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpOff\\penitent_jumpoff_new_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\JumpOff\\penitent_jumpoff_new_4.png"));
	SetTexture("PlayerJumpDown", "PlayerJumpDown", FileNames);
	AddFrameCount("PlayerJumpDown", 4, 0.f, 0.f, 100.f, 100.f);

	//플레이어 점프 착지  모션 
	CLog::PrintLog("CAnimation2DManager::PlayerJumpLand");
	//하단 점프 
	CreateAnimation("PlayerJumpLand");
	SetAnimationTextureType("PlayerJumpLand", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Jump\\HardLandingEffect\\penitent_hardlanding_rocks_anim_17.png"));
	SetTexture("PlayerJumpLand", "PlayerJumpLand", FileNames);
	AddFrameCount("PlayerJumpLand", 17, 0.f, 0.f, 100.f, 100.f);

	// 플레이어 피격 모션 
	CLog::PrintLog("CAnimation2DManager::FallingOverCheack");
	CreateAnimation("FallingOver");
	SetAnimationTextureType("FallingOver", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_falling_over_anim_11.png"));
	SetTexture("FallingOver", "FallingOver", FileNames);
	AddFrameCount("FallingOver", 11, 0.f, 0.f, 125.f, 135.f);

	//피격후 일어나는 모션 
	CLog::PrintLog("CAnimation2DManager::GettingUp Cheack");
	CreateAnimation("GettingUp");
	SetAnimationTextureType("GettingUp", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_getting_up_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_getting_up_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_getting_up_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_getting_up_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Move\\Penitent_GettingUp\\penitent_getting_up_4.png"));
	SetTexture("GettingUp", "GettingUp", FileNames);
	AddFrameCount("GettingUp", 5, 0.f, 0.f, 100.f, 100.f);


	// 플레이어 죽은 모션 
	// death_anim_0 ~ 23 24 장 
	CLog::PrintLog("CAnimation2DManager::death Cheack");
	CreateAnimation("PlayerDeath");
	SetAnimationTextureType("PlayerDeath", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR PlayerDeathPath[24][MAX_PATH] = {};
	for (int i = 0; i < 24; i++)
	{
		wsprintf(PlayerDeathPath[i], TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Death_anim\\death_anim_%d.png"), i);
		FileNames.emplace_back(PlayerDeathPath[i]);
	}
	SetTexture("PlayerDeath", "PlayerDeath", FileNames);
	AddFrameCount("PlayerDeath", 24, 0.f, 0.f, 100.f, 100.f);

	////////////////////////////////////////////////////////////////////////////////////////////

	//플레이어 공격 
	// 어택 기능 많으니 더찾아보고 수정할 것
	// "E:\SVN\BlasStart1201\Blasphemous\Bin\Asset\Texture\RealAsset\PenitentPlayer\Penitent_ComBet\ThreeComboNoSlashes\penitent_three_hits_attack_combo_no_slashes_1.png"
	// penitent_three_hits_attack_combo_no_slashes_1
	CLog::PrintLog("CAnimation2DManager::PlayerAttack1 Start");
	CreateAnimation("PlayerAttack1");
	SetAnimationTextureType("PlayerAttack1", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR ComboATKPath[28][MAX_PATH] = {};
	for (int i = 1; i < 10; i++)
	{
		wsprintf(ComboATKPath[i - 1], TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_%d.png"), i);
		FileNames.emplace_back(ComboATKPath[i - 1]);
	}

	SetTexture("PlayerAttack1", "PlayerAttack1", FileNames);
	AddFrameCount("PlayerAttack1", 9, 0.f, 0.f, 100.f, 100.f);

	CLog::PrintLog("CAnimation2DManager::PlayerAttack2 Start");
	CreateAnimation("PlayerAttack2");
	SetAnimationTextureType("PlayerAttack2", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_16.png"));
	SetTexture("PlayerAttack2", "PlayerAttack2", FileNames);
	AddFrameCount("PlayerAttack2", 6, 0.f, 0.f, 100.f, 100.f);


	CLog::PrintLog("CAnimation2DManager::PlayerAttack3 Start");
	CreateAnimation("PlayerAttack3");
	SetAnimationTextureType("PlayerAttack3", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_16.png")); 
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_26.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_27.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\ThreeComboNoSlashes\\penitent_three_hits_attack_combo_no_slashes_28.png"));

	SetTexture("PlayerAttack3", "PlayerAttack3", FileNames);
	AddFrameCount("PlayerAttack3", 13, 0.f, 0.f, 100.f, 100.f);

	//플레이어 윗 공격 
	//위로 공격 penitent_upward_attack_clamped_anim_1
	CLog::PrintLog("CAnimation2DManager::Player UpATK");
	CreateAnimation("PlayerUpATK");
	SetAnimationTextureType("PlayerUpATK", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_ComBet\\UpWardAttack\\penitent_upward_attack_clamped_anim_11.png"));
	SetTexture("PlayerUpATK", "PlayerUpATK", FileNames);
	AddFrameCount("PlayerUpATK", 10, 0.f, 0.f, 100.f, 100.f);
		
	//플레이어 스킬 등록 
	// 스킬모션을 시작하겠다 
	// penitent_aura_anim_0 ~ 41 - 42장
	CLog::PrintLog("CAnimation2DManager:: penitent_aura");
	CreateAnimation("PlayerAura");
	SetAnimationTextureType("PlayerAura", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR PlayerAuraPath[42][MAX_PATH] = {};
	for (int i = 0; i < 42; i++)
	{
		wsprintf(PlayerAuraPath[i], TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Skill\\Skill_Aura\\penitent_aura_anim_%d.png"), i);
		FileNames.emplace_back(PlayerAuraPath[i]);
	}
	SetTexture("PlayerAura", "PlayerAura", FileNames);
	AddFrameCount("PlayerAura", 42, 0.f, 0.f, 100.f, 100.f);
	
	// divine_beam_0 ~ divine_beam_63 - 64장
	CLog::PrintLog("CAnimation2DManager::Player divine");
	CreateAnimation("PlayerDivineSkill");
	SetAnimationTextureType("PlayerDivineSkill", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR DivineSkillPath[64][MAX_PATH] = {};
	for (int i = 0; i < 64; i++)
	{
		wsprintf(DivineSkillPath[i], TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Skill\\PlayerBeam\\divine_beam_%d.png"), i);
		FileNames.emplace_back(DivineSkillPath[i]);
	}
	SetTexture("PlayerDivineSkill", "PlayerDivineSkill", FileNames);
	AddFrameCount("PlayerDivineSkill", 64, 0.f, 0.f, 100.f, 100.f);


	//패링
	// 가드 
	//penitent_parry_counter_v2_anim_1 ~ 19
	// penitent_parry_failed_0~3
	//Parry_anim 4~14
	//"E:\SVN\BlasImitation\Blasphemous\Bin\Asset\Texture\RealAsset\PenitentPlayer\penitent_parry_anim_4.png"
	CLog::PrintLog("CAnimation2DManager::PlayerParry Start");
	CreateAnimation("PlayerParry");
	SetAnimationTextureType("PlayerParry", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryFailed\\penitent_parry_failed_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryFailed\\penitent_parry_failed_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryFailed\\penitent_parry_failed_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryFailed\\penitent_parry_failed_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\ParryMotion\\penitent_parry_anim_14.png"));
	SetTexture("PlayerParry", "PlayerParry", FileNames);			
	AddFrameCount("PlayerParry", 14, 0.f, 0.f, 125.f, 135.f);

	//넉백 추가해주기 
	// penitent_guardSlide_back_to_idle_1
	// penitent_guardslide_sparks_anim_0

	CLog::PrintLog("CAnimation2DManager::PlayerBack Start");
	CreateAnimation("PlayerBackIdle");
	SetAnimationTextureType("PlayerBackIdle", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardSlide_back_to_idle_11.png"));
	SetTexture("PlayerBackIdle", "PlayerBackIdle", FileNames);
	AddFrameCount("PlayerBackIdle", 12, 0.f, 0.f, 100.f, 100.f);

	//패링 스파크 
	CLog::PrintLog("CAnimation2DManager::PlayerBackSparks");
	CreateAnimation("PlayerBackSparks");
	SetAnimationTextureType("PlayerBackSparks", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\Penitent_Parry\\Guard_Slide\\penitent_guardslide_sparks_anim_7.png"));

	SetTexture("PlayerBackSparks", "PlayerBackSparks", FileNames);
	AddFrameCount("PlayerBackSparks", 8, 0.f, 0.f, 100.f, 100.f);

	// 회복 모션 
	// "E:\SVN\BlasStart1201\Blasphemous\Bin\Asset\Texture\RealAsset\PenitentPlayer\HP\penitent_healthpotion_consuming_anim_1 ~ 37.png"  37
	// 회피 dodge
	CLog::PrintLog("CAnimation2DManager::HPRecovery Start");
	CreateAnimation("HPRecovery");
	SetAnimationTextureType("HPRecovery", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_14.png"));
	//이펙트 추가 penitent_healthpotion_consuming_aura_anim_0 ~ 22 23장 19, 20만 추가하기 14
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_26.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_27.png"));
	//28 없음  -> 이래서 오류발생 
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_29.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_30.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_31.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_32.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_33.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_34.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_35.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_36.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_anim_37.png"));
	SetTexture("HPRecovery", "HPRecovery", FileNames);
	AddFrameCount("HPRecovery", 36, 0.f, 0.f, 100.f, 100.f);


	// penitent_healthpotion_consuming_aura_anim_0 ~ penitent_healthpotion_consuming_aura_anim_22
	CLog::PrintLog("CAnimation2DManager::HealFX Start");
	CreateAnimation("HealFX");
	SetAnimationTextureType("HealFX", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\PenitentPlayer\\HP\\penitent_healthpotion_consuming_aura_anim_22.png"));
	SetTexture("HealFX", "HealFX", FileNames);
	AddFrameCount("HealFX", 23, 0.f, 0.f, 100.f, 100.f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////// 밑줄 부터는 몬스터 애니메이션을 등록 /////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	//교황 1페이즈 Pope pope_idle_0 ~12 13장 등록 
	// pope_appear_0 ~ 14 15장 등록
	// pope_death_ 0 ~34
	// pope_hitReaction_1 ~ 10
	// pope_spellCast_0 ~ 54
	// pope_spellCast_FXS_0 ~ 48스킬 이펙트
	// pope_twistedOne_symbol_0 ~ 23 
	// pope_vanishing_0 ~ 14 교황이 사라지는 이펙트 

	//교황 IDLE 0 ~ 12 13장
	CLog::PrintLog("CAnimation2DManager::pope_idle_Start");
	CreateAnimation("pope_idle");
	SetAnimationTextureType("pope_idle", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_IdlePath[13][MAX_PATH] = {};
	for (int i = 0; i < 13; ++i)
	{
		wsprintf(Pope1_IdlePath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_idle_%d.png"), i);
		FileNames.emplace_back(Pope1_IdlePath[i]);
	}
	SetTexture("pope_idle", "pope_idle", FileNames);
	AddFrameCount("pope_idle", 13, 100.f, 100.f, 0.f, 0.f);

	//교황  pope_appear_0 ~ 14 15장 
	CLog::PrintLog("CAnimation2DManager::pope_appear_Start");
	CreateAnimation("pope_appear");
	SetAnimationTextureType("pope_appear", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_AppearPath[15][MAX_PATH] = {};
	for (int i = 0; i < 15; ++i)
	{
		wsprintf(Pope1_AppearPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_appear_%d.png"), i);
		FileNames.emplace_back(Pope1_AppearPath[i]);
	}
	SetTexture("pope_appear", "pope_appear", FileNames);
	AddFrameCount("pope_appear", 15, 100.f, 100.f, 0.f, 0.f);

	// 교황 Depath 0 ~34 35장
	CLog::PrintLog("CAnimation2DManager::pope_death_Start");
	CreateAnimation("pope_death");
	SetAnimationTextureType("pope_death", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_DeathPath[35][MAX_PATH] = {};
	for (int i = 0; i < 35; ++i)
	{
		wsprintf(Pope1_DeathPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_death_%d.png"), i);
		FileNames.emplace_back(Pope1_DeathPath[i]);
	}
	SetTexture("pope_death", "pope_death", FileNames);
	AddFrameCount("pope_death", 35, 100.f, 100.f, 0.f, 0.f);

	// pope_hitReaction_1 ~ 10 10장
	CLog::PrintLog("CAnimation2DManager::pope_hitReaction ");
	CreateAnimation("pope_hitReaction");
	SetAnimationTextureType("pope_hitReaction", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_HitReactionPath[11][MAX_PATH] = {};
	for (int i = 1; i < 11; ++i)
	{
		wsprintf(Pope1_DeathPath[i - 1], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_hitReaction_%d.png"), i);
		FileNames.emplace_back(Pope1_DeathPath[i - 1]);
	}
	SetTexture("pope_hitReaction", "pope_hitReaction", FileNames);
	AddFrameCount("pope_hitReaction", 10, 100.f, 100.f, 0.f, 0.f);

	// pope_spellCast_0 ~ 54
	CLog::PrintLog("CAnimation2DManager::pope_spellCast ");
	CreateAnimation("pope_spellCast");
	SetAnimationTextureType("pope_spellCast", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_spellCastPath[55][MAX_PATH] = {};
	for (int i = 0; i < 55; ++i)
	{
		wsprintf(Pope1_spellCastPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_spellCast_%d.png"), i);
		FileNames.emplace_back(Pope1_spellCastPath[i]);
	}
	SetTexture("pope_spellCast", "pope_spellCast", FileNames);
	AddFrameCount("pope_spellCast", 54, 100.f, 100.f, 0.f, 0.f);

	// pope_spellCast_FXS_0 ~ 48스킬 이펙트
	CLog::PrintLog("CAnimation2DManager::pope_spellCast_FXS");
	CreateAnimation("pope_spellCast_FXS");
	SetAnimationTextureType("pope_spellCast_FXS", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_SpellCastFXSPath[49][MAX_PATH] = {};
	for (int i = 0; i < 49; ++i)
	{
		wsprintf(Pope1_SpellCastFXSPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_spellCast_FXS_%d.png"), i);
		FileNames.emplace_back(Pope1_SpellCastFXSPath[i]);
	}

	SetTexture("pope_spellCast_FXS", "pope_spellCast_FXS", FileNames);
	AddFrameCount("pope_spellCast_FXS", 49, 0.f, 0.f, 100.f, 100.f);

	// pope_twistedOne_symbol_0 ~ 23 24
	CLog::PrintLog("CAnimation2DManager::pope_twistedOne_symbol");
	CreateAnimation("pope_twistedOne_symbol");
	SetAnimationTextureType("pope_twistedOne_symbol", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_twistedOnePath[24][MAX_PATH] = {};
	for (int i = 0; i < 24; ++i)
	{
		wsprintf(Pope1_twistedOnePath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_twistedOne_symbol_%d.png"), i);
		FileNames.emplace_back(Pope1_twistedOnePath[i]);
	}
	SetTexture("pope_twistedOne_symbol", "pope_twistedOne_symbol", FileNames);
	AddFrameCount("pope_twistedOne_symbol", 24, 100.f, 100.f, 0.f, 0.f);

	// pope_vanishing_0 ~ 14 교황이 사라지는 이펙트  15
	CLog::PrintLog("CAnimation2DManager::pope_vanishing");
	CreateAnimation("pope_vanishing");
	SetAnimationTextureType("pope_vanishing", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR Pope1_VanishPath[15][MAX_PATH] = {};
	for (int i = 0; i < 15; ++i)
	{
		wsprintf(Pope1_VanishPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\pope_phase1\\pope_vanishing_%d.png"), i);
		FileNames.emplace_back(Pope1_VanishPath[i]);
	}
	SetTexture("pope_vanishing", "pope_vanishing", FileNames);
	AddFrameCount("pope_vanishing", 15, 100.f, 100.f, 0.f, 0.f);

	// 교황 2페이즈 Ponetiff 
	// idle 
	//pontiff_idle_helmet_0 ~ 30  31장 
	//pontiff_idle_torso_0  ~ 30 31장
	CLog::PrintLog("CAnimation2DManager::pontiff_Headidle");
	CreateAnimation("pontiff_Headidle");
	SetAnimationTextureType("pontiff_Headidle", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_26.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_27.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_28.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_29.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_helmet_30.png"));
	SetTexture("pontiff_Headidle", "pontiff_Headidle", FileNames);
	AddFrameCount("pontiff_Headidle", 31, 0, 0.f, 100.f, 100.f);

	// 교황 바디 IDLE
	CLog::PrintLog("CAnimation2DManager::pontiff_Bodyidle");
	CreateAnimation("pontiff_Bodyidle");
	SetAnimationTextureType("pontiff_Bodyidle", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR Pontiff2_IdleBody[31][MAX_PATH] = {};
	for (int i = 0; i < 31; ++i)
	{
		wsprintf(Pontiff2_IdleBody[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Idle\\pontiff_idle_torso_%d.png"), i);
		FileNames.emplace_back(Pontiff2_IdleBody[i]);
	}
	SetTexture("pontiff_Bodyidle", "pontiff_Bodyidle", FileNames);
	AddFrameCount("pontiff_Bodyidle", 31, 0.f, 0.f, 450.f, 350.f);
	
	// 헤드 열리는거 pontiff_opening_face_0 ~ 17 -> 18장 
	// 12번 빠짐 총 17장 
	CLog::PrintLog("CAnimation2DManager::PontiffOpeningFace");
	CreateAnimation("PontiffOpeningFace");
	SetAnimationTextureType("PontiffOpeningFace", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_11.png"));
	//12번 없음 
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\opeing\\pontiff_opening_face_17.png"));

	SetTexture("PontiffOpeningFace", "PontiffOpeningFace", FileNames);
	AddFrameCount("PontiffOpeningFace", 17, 0.f, 0.f, 100.f, 100.f);

	//뚜껑 닫히는 idle
	// pontiff_closing_face_0 ~ 14  + 닫힐 때 까지 -> 16장 
	CLog::PrintLog("CAnimation2DManager::PontiffClosingHead");
	CreateAnimation("PontiffClosingHead");
	SetAnimationTextureType("PontiffClosingHead", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_face_14.png"));
	//FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\cloing\\pontiff_closing_helmet.png"));
	SetTexture("PontiffClosingHead", "PontiffClosingHead", FileNames);
	AddFrameCount("PontiffClosingHead", 15, 0.f, 0.f, 100.f, 100.f);

	//페이즈 2 뚜껑 열렸을 떄 IDle + Death
	// pontiff_openedIdle_face_0 ~  30 -> 31장  
	CLog::PrintLog("CAnimation2DManager::pontiff_openedIdle_face");
	CreateAnimation("pontiff_openedIdle_face");
	SetAnimationTextureType("pontiff_openedIdle_face", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_26.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_27.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_28.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_29.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_30.png"));
	SetTexture("pontiff_openedIdle_face", "pontiff_openedIdle_face", FileNames);
	AddFrameCount("pontiff_openedIdle_face", 31, 0.f, 0.f, 100.f, 100.f);

	//교황이 죽었을 때  pontiff_openedIdle_face_DEATH_0 64 -> 65장
	CLog::PrintLog("CAnimation2DManager::pontiff_openedIdle_face_DEATH");
	CreateAnimation("pontiff_openedIdle_face_DEATH");
	SetAnimationTextureType("pontiff_openedIdle_face_DEATH", EAnimationTextureType::Frame);
	FileNames.clear();

	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_26.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_27.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_28.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_29.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_30.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_31.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_32.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_33.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_34.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_35.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_36.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_37.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_38.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_39.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_40.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_41.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_42.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_43.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_44.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_45.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_46.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_47.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_48.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_49.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_50.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_51.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_52.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_53.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_54.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_55.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_56.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_57.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_58.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_59.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_60.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_61.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_62.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_63.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\openedidle\\pontiff_openedIdle_face_DEATH_64.png"));

	SetTexture("pontiff_openedIdle_face_DEATH", "pontiff_openedIdle_face_DEATH", FileNames);
	AddFrameCount("pontiff_openedIdle_face_DEATH", 65, 0, 0.f, 100.f, 0.f);


	// 검은 구현할 때 추가 
	//pontiff_giantSword_eyeGlobeSprite
	//pontiff_giantSword_swordSprite
	//pontiff_giantSword_eyeLids_0
	//pontiff_giantSword_teleportIN_0 ~ 18
	//pontiff_giantSword_teleportOUT_0 ~ 18

	// 교황 스킬 
	// 파이어볼 + 스킬 이펙트 스킬 1
	CLog::PrintLog("CAnimation2DManager::FireBall Start");
	CreateAnimation("FireBall");
	SetAnimationTextureType("FireBall", EAnimationTextureType::Frame);
	FileNames.clear();

	TCHAR FrieBallPath[10][MAX_PATH] = {};

	for (int i = 0 ; i < 10; ++i)
	{
		wsprintf(FrieBallPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\pope_fireBall_%d.png"), i);
		FileNames.emplace_back(FrieBallPath[i]);
	}
	SetTexture("FireBall", "FireBall", FileNames);
	AddFrameCount("FireBall", 10, 0.f, 0.f, 150.f, 150.f);


	CLog::PrintLog("CAnimation2DManager::Explosion Start");
	CreateAnimation("Explosion");
	SetAnimationTextureType("Explosion", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR FrieEffectPath[45][MAX_PATH] = {};

//터지는 이펙트가아니라 파이어볼이 나오는 이펙트임 
	for (int i = 0; i < 45; ++i)
	{
		wsprintf(FrieEffectPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\pope_fireBallVortex_%d.png"), i);
		FileNames.emplace_back(FrieEffectPath[i]);
	}
	SetTexture("Explosion", "Explosion", FileNames);
	AddFrameCount("Explosion", 45, 0.f, 0.f, 150.f, 150.f);
	
	//터지는 이펙트 추가  fireTrap_projectile_destroyed_0 ~ 17 
	CLog::PrintLog("CAnimation2DManager::FireEffect Start");
	CreateAnimation("FireEffect");
	SetAnimationTextureType("FireEffect", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill1-FrieBall\\fireTrap_projectile_destroyed_17.png"));
	SetTexture("FireEffect", "FireEffect", FileNames);
	AddFrameCount("FireEffect", 18, 0.f, 0.f, 150.f, 150.f);


	// 스킬2 - 독뎀 + 구슬 
	// pope_toxicOrb_0 ~ 26 
	CLog::PrintLog("CAnimation2DManager::pope_toxicOrb Start");
	CreateAnimation("pope_toxicOrb");
	SetAnimationTextureType("pope_toxicOrb", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\pope_toxicOrb_26.png"));
	SetTexture("pope_toxicOrb", "pope_toxicOrb", FileNames);
	AddFrameCount("pope_toxicOrb", 27, 100.f, 100.f, 150.f, 150.f);
	
	// Pope_toxicCloud_0 ~ 26 이펙트
	CLog::PrintLog("CAnimation2DManager::Pope_toxicCloud Start");
	CreateAnimation("Pope_toxicCloud");
	SetAnimationTextureType("Pope_toxicCloud", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_19.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill2-Toxic\\Pope_toxicCloud_25.png"));

	SetTexture("Pope_toxicCloud", "Pope_toxicCloud", FileNames);
	AddFrameCount("Pope_toxicCloud", 26, 100.f, 100.f, 150.f, 150.f);

	// 스킬3 - 매직 미사일 스킬 
	// pope_magicMissile_0  ~ 29
	CLog::PrintLog("CAnimation2DManager::pope_magicMissile Start");
	CreateAnimation("pope_magicMissile");
	SetAnimationTextureType("pope_magicMissile", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_19.png"));
	SetTexture("pope_magicMissile", "pope_magicMissile", FileNames);
	AddFrameCount("pope_magicMissile", 20, 0.f, 0.f, 100.f, 100.f);
	//터질 떄의 이펙트 
	CLog::PrintLog("CAnimation2DManager::pope_magicMissile Start");
	CreateAnimation("pope_magicMissileFXS");
	SetAnimationTextureType("pope_magicMissileFXS", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_20.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_21.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_22.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_23.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_24.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_25.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_26.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_27.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\SKill3-MagicMissile\\pope_magicMissile_28.png"));
	SetTexture("pope_magicMissileFXS", "pope_magicMissileFXS", FileNames);
	AddFrameCount("pope_magicMissileFXS", 9, 0.f, 0.f, 100.f, 100.f);

	// 스킬4 - 빔 
	// threeAnguishBigBeam_0 ~ 65 66장
	CLog::PrintLog("CAnimation2DManager::threeAnguishBigBeam Start");
	CreateAnimation("threeAnguishBigBeam");
	SetAnimationTextureType("threeAnguishBigBeam", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR BigBeamPath[66][MAX_PATH] = {};

	for (int i = 0; i < 66; ++i)
	{
		wsprintf(BigBeamPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill5-PopeBeam\\threeAnguishBigBeam_%d.png"), i);
		FileNames.emplace_back(BigBeamPath[i]);
	}
	SetTexture("threeAnguishBigBeam", "threeAnguishBigBeam", FileNames);
	AddFrameCount("threeAnguishBigBeam", 66, 100.f, 100.f, 0.f, 0.f);

	// 교황 스킬 5 번개 추가 
	// lightningBolt_Tileable_fxs_0 ~ 63
	// lightningBolt_fxs_49
	CLog::PrintLog("CAnimation2DManager::lightningBolt_Tileable_fxs Start");
	CreateAnimation("LightningBolt");
	SetAnimationTextureType("LightningBolt", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR LightningPath[64][MAX_PATH] = {};

	for (int i = 0; i < 64; ++i)
	{
		wsprintf(LightningPath[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\Skill4-Lightning\\lightningBolt_Tileable_fxs_%d.png"), i);
		FileNames.emplace_back(LightningPath[i]);
	}
	SetTexture("LightningBolt", "LightningBolt", FileNames);
	AddFrameCount("LightningBolt", 64, 0.f, 0.f, 100.f, 100.f);
	
	// 교황의 검 
	// Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeGlobeSprite.png
	// pontiff_giantSword_eyeGlobeSprite -> 1장 
	// pontiff_giantSword_irisSprite -> 1장 
	// pontiff_giantSword_swordSprite  -> 1장 
	// pontiff_giantSword_eyeLids_0 ~ 5 -> 6장
	// pontiff_giantSword_teleportIN_0 ~ 18 텔레포트 / 죽을 때 사용 
	// pontiff_giantSword_teleportOUT_0 ~ 18 텔레포트용 / 첫등장시에 사용 

	// pontiff_giantSword_eyeGlobeSprite -> 1장 
	CLog::PrintLog("CAnimation2DManager:: SwordeyeGlobeSprite");
	CreateAnimation("SwordeyeGlobeSprite");
	SetAnimationTextureType("SwordeyeGlobeSprite", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeGlobeSprite.png"));
	SetTexture("SwordeyeGlobeSprite", "SwordeyeGlobeSprite", FileNames);
	AddFrameCount("SwordeyeGlobeSprite", 1, 100.f, 100.f, 0.f, 0.f);

	//pontiff_giantSword_irisSprite
	CLog::PrintLog("CAnimation2DManager::SowrdIrisSprite");
	CreateAnimation("SowrdIrisSprite");
	SetAnimationTextureType("SowrdIrisSprite", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_irisSprite.png"));
	SetTexture("SowrdIrisSprite", "SowrdIrisSprite", FileNames);
	AddFrameCount("SowrdIrisSprite", 1, 100.f, 100.f, 0.f, 0.f);

	//pontiff_giantSword_swordSprite
	CLog::PrintLog("CAnimation2DManager::SwordSprite");
	CreateAnimation("SwordSprite");
	SetAnimationTextureType("SwordSprite", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_swordSprite.png"));
	SetTexture("SwordSprite", "SwordSprite", FileNames);
	AddFrameCount("SwordSprite", 1, 100.f, 100.f, 0.f, 0.f);

	// pontiff_giantSword_eyeLids_0 ~ 5 -> 6장 
	CLog::PrintLog("CAnimation2DManager::SwordEyeLids");
	CreateAnimation("SwordEyeLids");
	SetAnimationTextureType("SwordEyeLids", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeLids_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeLids_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeLids_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeLids_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeLids_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_eyeLids_5.png"));
	
	SetTexture("SwordEyeLids", "SwordEyeLids", FileNames);
	AddFrameCount("SwordEyeLids", 6, 100.f, 100.f, 0.f, 0.f);

	// pontiff_giantSword_teleportIN_0 ~ 18 19장 
	CLog::PrintLog("CAnimation2DManager::SwordTeleportIn");
	CreateAnimation("SwordTeleportIn");
	SetAnimationTextureType("SwordTeleportIn", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR TeleportIn[19][MAX_PATH] = {};

	for (int i = 0; i < 19; ++i)
	{
		wsprintf(TeleportIn[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_teleportIN_%d.png"), i);
		FileNames.emplace_back(TeleportIn[i]);
	}
	SetTexture("SwordTeleportIn", "SwordTeleportIn", FileNames);
	AddFrameCount("SwordTeleportIn", 19, 100.f, 100.f, 0.f, 0.f);
	CLog::PrintLog("CAnimation2DManager::Init End");


	CLog::PrintLog("CAnimation2DManager::SwordTeleportOut");
	CreateAnimation("SwordTeleportOut");
	SetAnimationTextureType("SwordTeleportOut", EAnimationTextureType::Frame);
	FileNames.clear();
	TCHAR TeleportOut[19][MAX_PATH] = {};

	for (int i = 0; i <19; ++i)
	{
		wsprintf(TeleportOut[i], TEXT("Texture\\RealAsset\\Boss\\LastSun\\Pontiff_phase2\\Sowrd\\pontiff_giantSword_teleportOUT_%d.png"), i);
		FileNames.emplace_back(TeleportOut[i]);
	}
	SetTexture("SwordTeleportOut", "SwordTeleportOut", FileNames);
	AddFrameCount("SwordTeleportOut", 19, 100.f, 100.f, 0.f, 0.f);

	// 맵 장판 깔개용 
	// ashplatform_64x64_anim_0  ~ 10 11장 장판 생성 
	// ashplatform_64x64_novisible_to_visible_0 ~ 17
	// ashplatform_64x64_visible_to_novisible_0 ~ 17
	// 눈덩어리 추가 ashplatform_32x32_deactivev_brightbackground_0
	// "E:\SVN\BlasStart1201\Blasphemous\Bin\Asset\Texture\RealAsset\Map\4\ashplatform_64x64_anim_0.png"
	
	// ashplatform_64x64_anim_0  ~10 11장 장판 유지
	CLog::PrintLog("CAnimation2DManager::ashplatform_64x64_anim_0");
	CreateAnimation("ashplatform_64x64_anim");
	SetAnimationTextureType("ashplatform_64x64_anim", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_anim_10.png"));
	SetTexture("ashplatform_64x64_anim", "ashplatform_64x64_anim", FileNames);
	AddFrameCount("ashplatform_64x64_anim", 11, 0.f, 0.f, 64.f, 64.f);

	// ashplatform_64x64_novisible_to_visible_0 ~ 17 사라졌다가 등장하는 장판 
	CLog::PrintLog("CAnimation2DManager::ashplatform_64x64_novisible_to_visible");
	CreateAnimation("AshplatformO");
	SetAnimationTextureType("AshplatformO", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_novisible_to_visible_17.png"));
	SetTexture("AshplatformO", "AshplatformO", FileNames);
	AddFrameCount("AshplatformO", 18, 0.f, 0.f, 100.f, 100.f);

	// ashplatform_64x64_visible_to_novisible_0 ~ 17 등장했다가 사라지는 장판. 
	CLog::PrintLog("CAnimation2DManager::ashplatform_64x64_visible_to_novisible_0");
	CreateAnimation("AshplatformX");
	SetAnimationTextureType("AshplatformX", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_64x64_visible_to_novisible_17.png"));
	SetTexture("AshplatformX", "AshplatformX", FileNames);
	AddFrameCount("AshplatformX", 18, 0.f, 0.f, 100.f, 100.f);


	// 눈덩어리 추가 ashplatform_32x32_deactivev_brightbackground_0 ~ 19 장 
	CLog::PrintLog("CAnimation2DManager::AshBright");
	CreateAnimation("AshBright");
	SetAnimationTextureType("AshBright", EAnimationTextureType::Frame);
	FileNames.clear();
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_0.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_1.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_2.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_3.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_4.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_5.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_6.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_7.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_8.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_9.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_10.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_11.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_12.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_13.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_14.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_15.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_16.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_17.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_18.png"));
	FileNames.emplace_back(TEXT("Texture\\RealAsset\\Map\\4\\ashplatform_32x32_deactivev_brightbackground_19.png"));
	SetTexture("AshBright", "AshBright", FileNames);
	AddFrameCount("AshBright", 20, 0.f, 0.f, 32.f, 32.f);

	CLog::PrintLog("CAnimation2DManager::Init End");
	return true;
}


bool CAnimation2DManager::CreateAnimation(const std::string& Name)
{
	// 생성해야하는데 같은 이름이 있으면 false
	if (FindAnimation(Name))
	{
		return false;
	}

	CAnimation2DData* Animation = new CAnimation2DData;

	Animation->SetName(Name);

	mAnimationMap.insert(std::make_pair(Name, Animation));

	return true;
}

class CAnimation2DData* CAnimation2DManager::FindAnimation(const std::string& Name)
{

	auto iter = mAnimationMap.find(Name);

	if (iter == mAnimationMap.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CAnimation2DManager::ReleaseAnimation(class CAsset* Animation)
{
	auto iter = mAnimationMap.find(Animation->GetName());

	if (iter != mAnimationMap.end())
	{
		mAnimationMap.erase(iter);
	}
}

bool CAnimation2DManager::SetAnimationTextureType(const std::string& Name, EAnimationTextureType Type)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetAnimationTextureType(Type);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, class CTexture* Texture)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(Texture);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, const TCHAR* FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName,
	std::vector<const TCHAR*> FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CAnimation2DManager::SetTexture(const std::string& Name, const std::string& TextureName, const TCHAR* FileName,
	const TCHAR* Ext, int Count)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTexture(TextureName, FileName, Ext, Count);

	return true;
}

bool CAnimation2DManager::SetTextureFullPath(const std::string& Name, const std::string& TextureName,
	const TCHAR* FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

bool CAnimation2DManager::SetTextureFullPath(const std::string& Name, const std::string& TextureName,
	const std::vector<const TCHAR*>& FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

//프레임 설정 
bool CAnimation2DManager::AddFrame(const std::string& Name, const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrame(Start, Size);

	return true;
}

bool CAnimation2DManager::AddFrame(const std::string& Name, float StartX, float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrame(StartX, StartY, SizeX, SizeY);

	return true;
}

bool CAnimation2DManager::AddFrameCount(const std::string& Name, int Count, const FVector2D& Start,
	const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrameCount(Count, Start, Size);

	return true;
}

bool CAnimation2DManager::AddFrameCount(const std::string& Name, int Count, float StartX, float StartY,
	float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
	{
		return false;
	}

	Animation->AddFrameCount(Count, StartX, StartY, SizeX, SizeY);

	return true;
}
