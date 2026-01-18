#include "PopeSymbol.h"
#include "../SceneObject.h"
#include "../../Component/SpriteComponent.h"
#include "../../Animation/Animation2D.h"
#include "../../Share/Log.h"

CPopeSymbol::CPopeSymbol()
{
}

CPopeSymbol::CPopeSymbol(const CPopeSymbol& Symbol)
{
}

CPopeSymbol::CPopeSymbol(CPopeSymbol&& Symbol)
{
}

CPopeSymbol::~CPopeSymbol()
{
}

bool CPopeSymbol::Init()
{

	return true;
}

void CPopeSymbol::Update(float DeltaTime)
{
}

bool CPopeSymbol::Setup()
{
	if (!mSymBolAnim || !mSymBolSprite) return false ; 
	if (mReady) return true;
	if (!mSymBolAnim->AddSequence("pope_twistedOne_symbol",3.0f,1.2f, true, false)) {
		CLog::PrintLog("Pope SymBol False");
		return false; 
	}

	mSymBolAnim->SetEndFunction("pope_twistedOne_symbol", this, &CPopeSymbol::SymbolEnd);
	mSymBolSprite->SetEnable(false);
	mReady = true;

	return true;
}

void CPopeSymbol::Play(bool bFlip)
{
	if (!mSymBolAnim || !mSymBolSprite) return;

	if (!Setup()) return;

	mSymBolSprite->SetFlip(bFlip);
	mSymBolAnim->ChangeAnimation("pope_twistedOne_symbol");
	mSymBolSprite->SetEnable(true);

}

void CPopeSymbol::Stop()
{
	if (mSymBolSprite)
		mSymBolSprite->SetEnable(false);
}

void CPopeSymbol::SymbolEnd()
{
	Stop();
}
