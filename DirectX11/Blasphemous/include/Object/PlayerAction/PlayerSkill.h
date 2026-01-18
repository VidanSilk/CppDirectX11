#pragma once

#include "../../Share/Object.h"
// Q 스킬 동작 흐름(단일 BeamSprite로 시전FX+발사체 겸용)
// 1) skillAction(): 플레이어 모션(PlayerAura) 시작 + BeamSprite를 몸 근처에 켜서 "시전 FX"처럼 보여줌(콜라이더 OFF, 이동 OFF)
// 2) Fire(): 애니 Notify에서 호출. BeamSprite를 플레이어 앞쪽으로 옮기고 "발사체 모드"로 전환(콜라이더 ON, 이동 ON)
// 3) Update(): 발사체 이동/수명 관리
// 4) SkillEnd(): 스킬 종료 정리(강제 종료 포함)

class CSpriteComponent;
class CPlayerObject;
class CAnimation2D;
class CColliderAABB2D;

class CPlayerSkill
{
	friend class CScene;
	friend class CPlayerObject;

protected:
	CPlayerSkill();
	CPlayerSkill(const CPlayerSkill& Skill);
	CPlayerSkill(CPlayerSkill&& Skill);
	virtual ~CPlayerSkill();

private:
	// Owner / 플레이어 본체 애니
	CPlayerObject* mOwner = nullptr;
	CAnimation2D* mPlayerAnim = nullptr;

	// 빔 스프라이트(시전 FX + 발사체 겸용)
	CSharedPtr<CSpriteComponent> mBeamSprite;
	CAnimation2D* mBeamAnim = nullptr;
	CColliderAABB2D* mBeamCollider = nullptr;

	// 상태/파라미터
	bool  mReady = false;
	bool  mCasting = false;    // 시전 연출 중(BeamSprite는 켜져 있지만 발사체 이동은 안 함)
	bool  mBeamActive = false; // 발사체 활성(이동/충돌 ON)
	float mBeamLife = 1.0f;
	float mBeamTime = 0.f;

	// 연출/위치 파라미터(필요시 튜닝)
	float mCastOffsetX = 0.f;     // 시전 중 BeamSprite 상대좌표
	float mCastOffsetY = 20.f;

	float mFireOffsetX = 140.f;   // 발사 시작 위치(플레이어 앞)
	float mFireOffsetY = 20.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	bool Setup();

	// 스킬 시작: PlayerAura(플레이어 모션) + BeamSprite를 시전FX로 ON
	void skillAction(bool bFlip);

	// Notify에서 발사체 전환
	void Fire(bool bFlip);

	// 스킬 종료 정리(강제 종료 포함)
	void SkillEnd();

public:
	// PlayerObject에서 Bind
	void SkillBind(
		CPlayerObject* owner,
		CAnimation2D* playerAnim,
		const CSharedPtr<CSpriteComponent>& beamSprite,
		CAnimation2D* beamAnim,
		CColliderAABB2D* beamCollider)
	{
		mOwner = owner;
		mPlayerAnim = playerAnim;
		mBeamSprite = beamSprite;
		mBeamAnim = beamAnim;
		mBeamCollider = beamCollider;
	}

	void SetCastOffset(float x, float y) { mCastOffsetX = x; mCastOffsetY = y; }
	void SetFireOffset(float x, float y) { mFireOffsetX = x; mFireOffsetY = y; }

private:
	void StopBeam(); // 발사체/시전 연출 정리
};