#include "PlayerDieWidget.h"
#include "../../Device.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/Image.h"


CPlayerDieWidget::CPlayerDieWidget()
{
}

CPlayerDieWidget::~CPlayerDieWidget()
{
}

bool CPlayerDieWidget::Init()
{
    if (!CWindowWidget::Init())
        return false;

    FResolution RS = CDevice::GetInst()->GetResolution();

    // 위젯 자체 = 화면 전체
    SetPos(0.f, 0.f);
    SetSize(RS.Width, RS.Height);
    SetPivot(FVector2D(0.f, 0.f));

    // 1) 검정 오버레이 (CloudWidget처럼 텍스처 없이 Tint만)
    mBack = mScene->GetUIManager()->CreateWidget<CImage>("PlayerDie_Back");
    mBack->SetPos(0.f, 0.f);
    mBack->SetSize((float)RS.Width, (float)RS.Height);
    mBack->SetPivot(FVector2D(0.f, 0.f));
    mBack->SetTint(0.f, 0.f, 0.f, 0.f);   // 시작은 투명(페이드 인)
    AddWidget(mBack);

    // 2) GameOver 이미지 (가운데)
    mGameOver = mScene->GetUIManager()->CreateWidget<CImage>("PlayerDie_GameOver");
    // "E:\SVN\BlasStart1201\Blasphemous\Bin\Asset\Texture\RealAsset\UIimage\demake-death-sceen.png"
    mGameOver->SetTexture("GameOver", TEXT("Texture\\RealAsset\\UIimage\\death-sreen-title.png"));

    // 이미지 크기: 일단 화면의 60% 정도로 (원하면 고정 픽셀로 바꿔도 됨)
    float imgW = RS.Width;
    float imgH = RS.Height; // 가로로 긴 이미지 가정 (너 이미지 비율에 맞게 조절)
    mGameOver->SetSize(imgW, imgH);

    mGameOver->SetPivot(FVector2D(0.5f, 0.5f));
    mGameOver->SetPos(RS.Width * 0.5f, (float)RS.Height * 0.5f);
    mGameOver->SetTint(1.f, 1.f, 1.f, 0.f); // 시작은 투명(페이드 인)
    AddWidget(mGameOver);

    // 페이드 초기화
    mAlpha = 0.f;

    return true;
}

void CPlayerDieWidget::Update(float DeltaTime)
{
    CWindowWidget::Update(DeltaTime);

    // (선택) 페이드 인
    if (mAlpha < 1.f)
    {
        mAlpha += (mFadeInTime <= 0.f) ? 1.f : (DeltaTime / mFadeInTime);
        if (mAlpha > 1.f) mAlpha = 1.f;

        if (mBack)
            mBack->SetTint(0.f, 0.f, 0.f, 1.f * mAlpha);   // 암전 강도(0.75~0.9 추천)

        if (mGameOver)
            mGameOver->SetTint(1.f, 1.f, 1.f, 1.0f * mAlpha);
    }
    else
    {
        // 페이드 끝난 뒤 잠깐 보여주고 Start로
        if (!mCalled)
        {
            mHoldAcc += DeltaTime;
            if (mHoldAcc >= mHoldAfterFade)
            {
                mCalled = true;
                if (mOnReturnToStart) mOnReturnToStart();
            }
        }
    }
}
