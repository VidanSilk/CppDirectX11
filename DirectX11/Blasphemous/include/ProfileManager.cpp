#include "ProfileManager.h"

CProfileManager::CProfileManager()
{

}

CProfileManager::~CProfileManager()
{
	auto iter = mProfileMap.begin();
	auto iterEnd = mProfileMap.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CProfileManager::Init()
{
	//우리가 사용할 프로파일 등록 
	//프로파일등록 
	CreateProfile("Default", ECollisionChannel::Default, true, ECollisionInteraction::Collision);
	//플레이어 
	CreateProfile("Player", ECollisionChannel::Player, true, ECollisionInteraction::Collision);
	//몬스터 
	CreateProfile("Monster", ECollisionChannel::Monster, true, ECollisionInteraction::Collision);
	//플레이어 공격
	CreateProfile("PlayerAttack", ECollisionChannel::PlayerAttack, true, ECollisionInteraction::Collision);
	//플레이어 패링
	CreateProfile("PlayerParry", ECollisionChannel::PlayerParry, true, ECollisionInteraction::Collision);
	//플레이어 움직임 콜라이더  - PlayerMove
	CreateProfile("PlayerMove", ECollisionChannel::PlayerMove, true, ECollisionInteraction::Collision);
	//몬스터 공격 
	CreateProfile("MonsterAttack", ECollisionChannel::MonsterAttack, true, ECollisionInteraction::Collision);

	CreateProfile("Floor", ECollisionChannel::Floor, true, ECollisionInteraction::Collision);

	//플레이어 프로파일 셋팅 
	/*
		Interaction[Default] = Collision;
		Interaction[Player] = Ignore;
		Interaction[Monster] = Collision;
		Interaction[PlayerAttack] = Ignore;
		Interaction[MonsterAttack] = Collision;
	*/
	SetInteraction("Player", ECollisionChannel::Player, ECollisionInteraction::Ignore);
	SetInteraction("Player", ECollisionChannel::PlayerAttack, ECollisionInteraction::Ignore);
	SetInteraction("Player", ECollisionChannel::PlayerParry, ECollisionInteraction::Ignore);
	SetInteraction("Player", ECollisionChannel::PlayerMove, ECollisionInteraction::Ignore);
	SetInteraction("Player", ECollisionChannel::MonsterAttack, ECollisionInteraction::Collision);

	//PlayerAttack
	SetInteraction("PlayerAttack", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetInteraction("PlayerAttack", ECollisionChannel::Player, ECollisionInteraction::Ignore);
	SetInteraction("PlayerAttack", ECollisionChannel::PlayerAttack, ECollisionInteraction::Ignore);
	SetInteraction("PlayerAttack", ECollisionChannel::PlayerParry, ECollisionInteraction::Ignore);
	SetInteraction("PlayerAttack", ECollisionChannel::Monster, ECollisionInteraction::Collision);
	SetInteraction("PlayerAttack", ECollisionChannel::MonsterAttack, ECollisionInteraction::Ignore);
	SetInteraction("PlayerAttack", ECollisionChannel::Floor, ECollisionInteraction::Ignore);

	//PlayerParry 1218 update
	SetInteraction("PlayerParry", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetInteraction("PlayerParry", ECollisionChannel::Monster, ECollisionInteraction::Ignore);
	SetInteraction("PlayerParry", ECollisionChannel::MonsterAttack, ECollisionInteraction::Collision);

	//PlayerMove Update
	SetInteraction("PlayerMove", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetInteraction("PlayerMove", ECollisionChannel::Floor, ECollisionInteraction::Collision);

	//Monster
	SetInteraction("Monster", ECollisionChannel::Monster, ECollisionInteraction::Ignore);
	SetInteraction("Monster", ECollisionChannel::MonsterAttack, ECollisionInteraction::Ignore);
	
	//MonsterAttack
	SetInteraction("MonsterAttack", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetInteraction("MonsterAttack", ECollisionChannel::Monster, ECollisionInteraction::Ignore);
	SetInteraction("MonsterAttack", ECollisionChannel::MonsterAttack, ECollisionInteraction::Ignore);
	SetInteraction("MonsterAttack", ECollisionChannel::Player, ECollisionInteraction::Collision);
	SetInteraction("MonsterAttack", ECollisionChannel::PlayerParry, ECollisionInteraction::Collision);
	SetInteraction("MonsterAttack", ECollisionChannel::Floor, ECollisionInteraction::Collision);
	//바닥 충돌 채널 추가 1218
	SetInteraction("Floor", ECollisionChannel::Default, ECollisionInteraction::Collision);
	SetInteraction("Floor", ECollisionChannel::Player, ECollisionInteraction::Ignore);
	SetInteraction("Floor", ECollisionChannel::PlayerAttack, ECollisionInteraction::Ignore);
	SetInteraction("Floor", ECollisionChannel::PlayerMove, ECollisionInteraction::Collision);
	SetInteraction("Floor", ECollisionChannel::Monster, ECollisionInteraction::Collision);
	SetInteraction("Floor", ECollisionChannel::MonsterAttack, ECollisionInteraction::Collision);

	return true;
}

bool CProfileManager::CreateProfile(const std::string& Name, ECollisionChannel::Type Channel, bool Enable, ECollisionInteraction::Type Interaction)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (Profile != nullptr)
	{
		return false;
	}

	Profile = new FCollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;

	for (int i = 0; i < ECollisionChannel::End; ++i)
	{
		Profile->Interaction[i] = Interaction;
	}

	mProfileMap.insert(std::make_pair(Name, Profile));

	return true;
}

bool CProfileManager::SetInteraction(const std::string& Name, ECollisionChannel::Type Channel, ECollisionInteraction::Type Interaction)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (Profile == nullptr)
	{
		return false;
	}
	Profile->Interaction[Channel] = Interaction;

	return true;
}

bool CProfileManager::SetEnable(const std::string& Name, bool Enable)
{
	FCollisionProfile* Profile = FindProfile(Name);

	if (Profile == nullptr)
	{
		return false;
	}
	Profile->Enable = Enable;

	return true;
}

FCollisionProfile* CProfileManager::FindProfile(const std::string& Name)
{
	//auto iter;
	std::unordered_map<std::string, FCollisionProfile*>::iterator iter = mProfileMap.find(Name);

	if (iter == mProfileMap.end())
	{
		return nullptr;
	}

	//iter->first;	// 키값
	//iter->second;	// 벨류값
	return iter->second;
}
