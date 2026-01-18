#pragma once
#include "WindowWidget.h"

class CPontiffDieWidget : public CWindowWidget
{
    friend class CSceneUIManager;

protected:
    CPontiffDieWidget();
    virtual ~CPontiffDieWidget();

private:
    CSharedPtr<class CImage> mBack;
    CSharedPtr<class CImage> mImg1;   // 1번 이미지
    CSharedPtr<class CImage> mImg2;   // 2번 이미지

    // 연출 파라미터
    float mAlpha = 0.f;        // 공통 페이드(Back/Img1용)
    float mFadeInTime = 0.35f;

    float mAccTime = 0.f;
    float mSwitchTime = 3.f;  // 3초 뒤 전환
    bool  mSwitched = false;

    // (선택) 2번 이미지도 따로 페이드 인
    float mAlpha2 = 0.f;
    float mFadeIn2Time = 0.25f;

public:
    virtual bool Init() override;
    virtual void Update(float DeltaTime) override;

public:
    void SetSwitchTime(float Time) { mSwitchTime = Time; }
    void SetFadeInTime(float Time) { mFadeInTime = Time; }
    void SetFadeIn2Time(float Time) { mFadeIn2Time = Time; }
};