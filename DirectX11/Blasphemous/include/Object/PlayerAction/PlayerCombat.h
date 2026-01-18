#pragma once
// 공격 콜라이더 추가해주기. 
// 패링 기능도 같이 포함해서 만들기 
// 여긴 이제 ATK기능만하는게 아니라 전투기능, 공격과 패링을 하는 기능으로 수정함 
// 공격 
// 상단 공격, 하단 공격, 콤보공격
// 화살표 + 공격 상하단, 
// 패링 판정을 3가지로 나눠서해줘야할 듯 
// if (패링 성공) -> 카운터 어택을 한다, 넉백이 된다. 그냥 강한 공격시 넉백 되는것 같은데? 판단 기준을 모르겠음.
// 2. 실패시 바닥에 눕는 모션 

//수정해야할 점 
// 공격/패링 콜라이더 수정 
// 패링 성공 -> 작은 확률로 카운터 어택, 아니면 넉백 ? 실패시 쓰러지기 -> 추가해줘야할듯? 
// + 공격 or 패링동작시 콜라이더가 생성안되게 수정할것  

class CPlayerObject;
class CAnimation2D;
class CColliderAABB2D;


enum class EPlayerAtkType
{
	None,
	Combo,
	Up,
	Dodge
};


class CPlayerCombat {

private:
	friend class CScene;
	friend class CPlayerObject;

protected:
	CPlayerCombat();
	CPlayerCombat(const CPlayerCombat& ATK);
	CPlayerCombat(CPlayerCombat&& ATK);
	virtual ~CPlayerCombat();

private:
	class CPlayerObject* mOwner = nullptr;
	class CAnimation2D* mAnimation = nullptr;
	class CColliderAABB2D* mATKCollider = nullptr; //공격용 콜라이더
	class CColliderAABB2D* mUpATKCollider = nullptr;   
	class CColliderAABB2D* mParryCollider = nullptr;  //패링용 콜라이더 

	//플레이어 공격력 
	float mPlayerATK = 10.0f;
	bool mParryTF = false; //패링 성공 여부 

	// 공격 패링
	EPlayerAtkType mAtkType = EPlayerAtkType::None;
	int   mComboIndex = 0;        // 1~3
	bool  mAtkBuffered = false;   // 공격 중 Z 추가입력 버퍼
	bool  mHitConfirmed = false;  // 이번 공격에서 히트 성공 여부(= 다음 콤보 조건)

	// 패링
	bool  mParryActive = false;
	bool  mParrySuccess = false;
	float mParryFailDamage = 10.f; // 실패시 받을 데미지
	bool  mLastParrySuccess = false;     


	// DodgeATK
	bool  mFlipCache = false;
	bool  mDodgeAtkDash = false;
	float mDodgeAtkDashAcc = 0.f;
	float mDodgeAtkDashDuration = 500.0f; 
	float mDodgeAtkDashSpeed = 300.f;     
	bool mComboAfterDodgeBuffered = false;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	
	// 입력키 
	void OnComboInput(bool bFlip);      // Z
	void OnUpAtkInput(bool bFlip);      // A
	void OnDodgeAtkInput(bool bFlip);   // S (대쉬하면서 공격)
	void OnParryInput(bool bFlip);      // X

	// 살려줘요  너무 귀찮아요 
	void ComboNotify(bool bFlip);       // 콤보 히트 프레임
	void UpAtkNotify(bool bFlip);       // 상단 히트 프레임
	void DodgeAtkNotify(bool bFlip);    // 대쉬 히트 프레임

	// ===== 애니 EndFunction에서 호출 =====
	// return true: 다음 공격 이어짐(Idle로 안 돌아감)
	bool OnAttackEnd();
	// return true: 패링 끝(Idle로 돌아가도 됨)
	bool OnParryEnd();

	// 피격/넉다운 등으로 강제 캔슬할 때
	void SetupColliders();
	void CancelAll();


public:

	// 바인드(Owner가 포인터 직접 세팅하는 기존 방식 유지해도 됨)
	void Bind(CPlayerObject* owner, CAnimation2D* anim,
		CColliderAABB2D* atk, CColliderAABB2D* upAtk, CColliderAABB2D* parry)
	{
		mOwner = owner; mAnimation = anim;
		mATKCollider = atk; mUpATKCollider = upAtk; mParryCollider = parry;
	}

	void ConfirmParrySuccess();

	void ConfirmHit() { 
		mHitConfirmed = true; 
	}
	
	bool IsParryActive() const { 
		return mParryActive; 
	}


	bool WasParrySuccess() const { return mLastParrySuccess; }
	void ClearParryResult() { mLastParrySuccess = false; }

	float GetParryFailDamage() const { return mParryFailDamage; }
	void  SetParryFailDamage(float v) { mParryFailDamage = v; }
	
	EPlayerAtkType GetAtkType() const { return mAtkType; }
	
	bool IsDodgeAttacking() const { return mAtkType == EPlayerAtkType::Dodge; }
private:
	void StartCombo(int idx);
	void StartUpAtk();
	void StartDodgeAtk();

	void EnableAtkCollider(bool on, bool bFlip, float x, float y);
	void EnableUpAtkCollider(bool on, bool bFlip, float x, float y);

	void ResetHit();

	
};