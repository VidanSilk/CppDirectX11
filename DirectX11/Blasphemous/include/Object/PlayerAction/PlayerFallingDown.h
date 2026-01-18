#pragma once
// 피격 시 쓰러지고 일어나는 곳을 처리하는 클래스

class CPlayerObject;
class CAnimation2D;
//class CColliderAABB2D;

class CPlayerFallingDown
{

public:
	CPlayerFallingDown();
	CPlayerFallingDown(const CPlayerFallingDown& Obj);
	CPlayerFallingDown(CPlayerFallingDown&& Obj);
	virtual ~CPlayerFallingDown();

private:
	class CPlayerObject* mOwner = nullptr;
	class CAnimation2D* mAnimation = nullptr;
	bool mReady = false;
	bool mGettingUp = false;
	float mDownTime = 0.f;
	float mDownDelay = 0.15f; // 넘어짐 후 잠깐 눕는 시간(원하면 0으로)

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void Bind(CPlayerObject* Owner, CAnimation2D* Anim)
	{
		mOwner = Owner;
		mAnimation = Anim;
	}

	// PlayerObject::Damage 등에서 호출
	void StartKnockDown();


private:
	void FallDownAction();
	void GetUpAction();
	void OnFallDownEnd();
	void OnGetUpEnd();
};

