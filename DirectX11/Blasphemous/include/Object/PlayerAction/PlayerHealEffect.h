#pragma once

// 콜라이더는 필요 없을거임 
// 여긴 이펙트 + UI 체력바만 담당할 예정 
// 이펙트가 안보이는 이유는 캐릭터, 따로 보여줘야함 
// 그럼 매쉬를 가져와서 그러줄까? 그럼 상대 좌표가 있어야하지않을까 ?
// 스프라이트 이펙트 잘 사용하면 될듯 
// 스폰 + 레이어 같은거 잘사용하면 될듯? 
#include "../../Share/SharedPtr.h"

class CSpriteComponent;
class CAnimation2D;

class CPlayerHealEffect  {
		
	friend class CScene;

private:

	CSharedPtr<CSpriteComponent> mFXSprite;
	class CAnimation2D* mFXAnim = nullptr; 
	bool mReady = false;

public:
	CPlayerHealEffect();
	CPlayerHealEffect(const CPlayerHealEffect& Heal);
	CPlayerHealEffect(CPlayerHealEffect&& Heal);
	virtual ~CPlayerHealEffect();

	virtual bool Init();
	virtual void Update(float DeltaTime);

	void Bind(const CSharedPtr<CSpriteComponent>& sprite, CAnimation2D* anim)
	{
		mFXSprite = sprite;
		mFXAnim = anim;
	}

	bool Setup();          
	void Play(bool bFlip); 
	void Stop();         
	void HealEnd();
};

