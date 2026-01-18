#pragma once
#include "../MonsterObject.h"

// 검 이미지 이슈 IDLE를 어떻게 처리할지? -> 고민 
class CBigSword : public CMonsterObject
{
	friend class CScene;

protected:
	CBigSword();
	CBigSword(const CBigSword& Obj);
	CBigSword(CBigSword&& Obj);
	virtual ~CBigSword();
	class CAnimation2D* mAnimation = nullptr;
//	CSharedPtr<class CColliderOBB2D> mSwordBody;

private:
	float mSwordHp = 100.0f;
	float mSwordATK = 5.0f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual float Damage(float Attack, CSceneObject* Obj);


private:
	//교황의 움직임 
	void SwordIDLE();
	void SwordAppear();
	void PopeVanishing();
	void SowrdDeath();


};

