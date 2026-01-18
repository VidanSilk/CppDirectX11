#include "PopeSpellCasting.h"
#include "../SceneObject.h"
#include "../../Component/SpriteComponent.h"
#include "../../Animation/Animation2D.h"
#include "../../Share/Log.h"

CPopeSpellCasting::CPopeSpellCasting()
{
}

CPopeSpellCasting::CPopeSpellCasting(const CPopeSpellCasting& Cast)
{
}

CPopeSpellCasting::CPopeSpellCasting(CPopeSpellCasting&& Cast)
{
}

CPopeSpellCasting::~CPopeSpellCasting()
{
}

bool CPopeSpellCasting::Init()
{
	return true;
}

void CPopeSpellCasting::Update(float DeltaTime)
{
}

bool CPopeSpellCasting::Setup()
{
	if (!mCastAnim || !mCastSprite) return false;
	if (mReady) return true;
	if (!mCastAnim->AddSequence("pope_spellCast_FXS", 3.0f, 0.8f, true, false )) {
		mReady = false;
		return false;
	}
	mCastAnim->SetEndFunction("pope_spellCast_FXS", this, &CPopeSpellCasting::CastEnd);
	mCastSprite->SetEnable(false);
	mCastSprite->SetFlip(false);
	mReady = true;
	return true;
}

void CPopeSpellCasting::Play(bool bFlip)
{
	if (!mCastAnim || !mCastSprite) return;

	if (!Setup()) return;

	mCastSprite->SetFlip(bFlip);
	mCastSprite->SetEnable(true);
	mCastAnim->ChangeAnimation("pope_spellCast_FXS");
	mReady = true;
}

void CPopeSpellCasting::Stop()
{
	if (mCastSprite)
		mCastSprite->SetEnable(false);
}

void CPopeSpellCasting::CastEnd()
{
	Stop();
}
