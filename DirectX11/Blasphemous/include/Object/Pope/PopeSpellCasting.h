#pragma once

#include "../../Share/SharedPtr.h"

class CSpriteComponent;
class CAnimation2D;

class CPopeSpellCasting {	

	friend class CScene;

private:

	CSharedPtr<CSpriteComponent> mCastSprite;
	class CAnimation2D* mCastAnim = nullptr; 
	bool mReady = false;

public:
	CPopeSpellCasting();
	CPopeSpellCasting(const CPopeSpellCasting& Cast);
	CPopeSpellCasting(CPopeSpellCasting&& Cast);
	virtual ~CPopeSpellCasting();

	virtual bool Init();
	virtual void Update(float DeltaTime);

	void Bind(const CSharedPtr<CSpriteComponent>& sprite, CAnimation2D* anim)
	{
		mCastSprite = sprite;
		mCastAnim = anim;
	}

	bool Setup();          
	void Play(bool bFlip); 
	void Stop();         
	void CastEnd();
};

