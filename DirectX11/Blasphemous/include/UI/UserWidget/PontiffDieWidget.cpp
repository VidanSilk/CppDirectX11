#include "PontiffDieWidget.h"

#include "../../Device.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/Image.h"

CPontiffDieWidget::CPontiffDieWidget()
{
}

CPontiffDieWidget::~CPontiffDieWidget()
{
}

bool CPontiffDieWidget::Init()
{
    if (!CWindowWidget::Init())
        return false;

    FResolution RS = CDevice::GetInst()->GetResolution();

    SetPos(0.f, 0.f);
    SetSize((float)RS.Width, (float)RS.Height);
    SetPivot(FVector2D(0.f, 0.f));

    // 1) 검정 오버레이 (Pontiff 죽음 연출에도 배경 정리용으로 추천)
    mBack = mScene->GetUIManager()->CreateWidget<CImage>("PontiffDie_Back");
    mBack->SetPos(0.f, 0.f);
    mBack->SetSize((float)RS.Width, (float)RS.Height);
    mBack->SetPivot(FVector2D(0.f, 0.f));
    mBack->SetTint(0.f, 0.f, 0.f, 0.f);
    AddWidget(mBack);

    // 2) 1번 이미지
    mImg1 = mScene->GetUIManager()->CreateWidget<CImage>("PontiffDie_Img1");
    mImg1->SetTexture("PontiffDie_1", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-fight-spritesheet_8.png"));
    mImg1->SetPivot(FVector2D(0.5f, 0.5f));
    mImg1->SetPos((float)RS.Width * 0.5f, (float)RS.Height * 0.5f);

    // 크기: 일단 화면 기준(원하면 고정 픽셀로 바꿔도 됨)
    mImg1->SetSize((float)RS.Width, (float)RS.Height);
    mImg1->SetTint(1.f, 1.f, 1.f, 0.f);
    AddWidget(mImg1);

    // 3) 2번 이미지 (처음엔 안 보이게)
    mImg2 = mScene->GetUIManager()->CreateWidget<CImage>("PontiffDie_Img2");

    mImg2->SetTexture("PontiffDie_2", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-defeated-screen-title.png"));
    
    mImg2->SetPivot(FVector2D(0.5f, 0.5f));
    mImg2->SetPos((float)RS.Width * 0.5f, (float)RS.Height * 0.5f);
    mImg2->SetSize((float)RS.Width, (float)RS.Height);
    mImg2->SetTint(1.f, 1.f, 1.f, 0.f);
    AddWidget(mImg2);

    // 상태 초기화
    mAlpha = 0.f;
    mAlpha2 = 0.f;
    mAccTime = 0.f;
    mSwitched = false;

    return true;
}

void CPontiffDieWidget::Update(float DeltaTime)
{
    CWindowWidget::Update(DeltaTime);

    // 공통 페이드 인 (Back + Img1)
    if (mAlpha < 1.f)
    {
        mAlpha += (mFadeInTime <= 0.f) ? 1.f : (DeltaTime / mFadeInTime);
        if (mAlpha > 1.f) mAlpha = 1.f;

        if (mBack)
            mBack->SetTint(0.f, 0.f, 0.f, 1.0f* mAlpha);

        if (mImg1 && !mSwitched)
            mImg1->SetTint(1.f, 1.f, 1.f, 1.0f * mAlpha);
    }

    // 3초 카운트
    mAccTime += DeltaTime;

    // 3초 뒤에 2번 이미지로 전환
    if (!mSwitched && mAccTime >= mSwitchTime)
    {
        mSwitched = true;

        // 1번 즉시 숨김(혹은 알파 0으로)
        if (mImg1) mImg1->SetTint(1.f, 1.f, 1.f, 0.f);

        // 2번 페이드 인 시작
        mAlpha2 = 0.f;
    }

    // 전환 후: 2번 페이드 인
    if (mSwitched && mImg2)
    {
        if (mAlpha2 < 1.f)
        {
            mAlpha2 += (mFadeIn2Time <= 0.f) ? 1.f : (DeltaTime / mFadeIn2Time);
            if (mAlpha2 > 1.f) mAlpha2 = 1.f;
        }

        mImg2->SetTint(1.f, 1.f, 1.f, mAlpha2);
    }
}

