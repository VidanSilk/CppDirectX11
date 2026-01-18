#include "PlayerHealEffect.h"
#include "../SceneObject.h"
#include "../../Component/SpriteComponent.h"
#include "../../Animation/Animation2D.h"
#include "../../Share/Log.h"

CPlayerHealEffect::CPlayerHealEffect()
{
}

CPlayerHealEffect::CPlayerHealEffect(const CPlayerHealEffect& Heal)
{
}

CPlayerHealEffect::CPlayerHealEffect(CPlayerHealEffect&& Heal)
{
}

CPlayerHealEffect::~CPlayerHealEffect()
{
}

bool CPlayerHealEffect::Init()
{
   

	return true;
}

void CPlayerHealEffect::Update(float DeltaTime)
{

}


bool CPlayerHealEffect::Setup()
{
    if (!mFXSprite || !mFXAnim)
        return false;

    if (mReady)
        return true;

    if (!mFXAnim->AddSequence("HealFX", 3.0f, 1.2f, true, false))
    {
        CLog::PrintLog("HealFX AddSequence FAILED");
        mReady = false;
        return false;
    }

  
    mFXAnim->SetEndFunction("HealFX", this, &CPlayerHealEffect::HealEnd);
    mFXSprite->SetEnable(false);
    mReady = true;
    return true;
}

void CPlayerHealEffect::Play(bool bFlip)
{
    if (!mFXSprite || !mFXAnim)
        return;

    if (!mReady && !Setup())
        return;

    mFXSprite->SetFlip(bFlip);
    mFXAnim->ChangeAnimation("HealFX");
    mFXSprite->SetEnable(true);
}

void CPlayerHealEffect::Stop()
{
    if (mFXSprite)
        mFXSprite->SetEnable(false);
}

void CPlayerHealEffect::HealEnd()
{
    Stop();
}
