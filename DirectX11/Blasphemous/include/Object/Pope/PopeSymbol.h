#pragma once
#include "../../Share/SharedPtr.h"

class CSpriteComponent;
class CAnimation2D;

class CPopeSymbol
{
	friend class CScene;

private:

	CSharedPtr<CSpriteComponent> mSymBolSprite;
	class CAnimation2D* mSymBolAnim = nullptr;
	bool mReady = false;

public:
	CPopeSymbol();
	CPopeSymbol(const CPopeSymbol& Symbol);
	CPopeSymbol(CPopeSymbol&& Symbol);
	virtual ~CPopeSymbol();

	virtual bool Init();
	virtual void Update(float DeltaTime);

	void Bind(const CSharedPtr<CSpriteComponent>& sprite, CAnimation2D* anim)
	{
		mSymBolSprite = sprite;
		mSymBolAnim = anim;
	}

	bool Setup();
	void Play(bool bFlip);
	void Stop();
	void SymbolEnd();
};

