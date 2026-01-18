#pragma once
#include "Component.h"

//중력 담당 

class CGravityComponent : public CComponent
{
	friend class CScene;
	friend class CSceneObject;

private:
	float mGravity = -3000.f;          //  중력
	float mVelocityY = 10.f;            // Y축 벨로시티
	float mTerminalVelocity = -4000.f; // 중력속도 

	bool  mGrounded = false;

protected:
	CGravityComponent();
	CGravityComponent(const CGravityComponent& Com);
	CGravityComponent(CGravityComponent&& Com);
	virtual ~CGravityComponent();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);


	// 착지/이탈 판정
	void SetGrounded(bool Grounded);
	// 착지 
	void GravityLand(float SnapWorldY, bool bSnap);
	// 점프
	void GravityJump(float JumpSpeed);
	// 임펄스
	void AddImpulseY(float ImpulseY);
	// 속도 리셋
	void ResetY(float NewVelY = 0.f);

	void SetGravity(float Gravity) {
		mGravity = Gravity; 
	}
	
	void SetTerminalVelocity(float TerminalVel) { 
		mTerminalVelocity = TerminalVel; 
	}

	bool  IsGrounded() const { 
		return mGrounded; 
	}

	float GetVelocityY() const { 
		return mVelocityY; 
	}


};

