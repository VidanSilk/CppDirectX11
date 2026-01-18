#include "TwisterWidget.h"

#include "../../Device.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/Image.h"

CTwisterWidget::CTwisterWidget()
{
}

CTwisterWidget::~CTwisterWidget()
{
}

bool CTwisterWidget::Init()
{
	CWindowWidget::Init();

	FResolution RS = CDevice::GetInst()->GetResolution();

	// 위젯(부모)은 화면 전체
	SetPos(0.f, 0.f);
	SetSize((float)RS.Width, (float)RS.Height);
	SetPivot(FVector2D(0.f, 0.f));
	
	//백그라운드 
	mColorBG = mScene->GetUIManager()->CreateWidget<CImage>("Twister_ColorBG");
	mColorBG->SetPos(0.f, 0.f);
	mColorBG->SetSize((float)RS.Width, (float)RS.Height);
	mColorBG->SetPivot(FVector2D(0.f, 0.f));
	mColorBG->SetTexture("TwisterColorBGTex", TEXT("Texture\\RealAsset\\Map\\4\\pontiff-boss-twister-background-color.png"));

	mColorBG->SetTint(0.1f, 0.1f, 0.1f);
	AddWidget(mColorBG);

	// 이미지 2장(타일링)
	mImg0 = mScene->GetUIManager()->CreateWidget<CImage>("Twister_0");
	mImg1 = mScene->GetUIManager()->CreateWidget<CImage>("Twister_1");

	mImg0->SetTexture("TwisterTex", TEXT("Texture\\RealAsset\\Map\\4\\pontif-twister-background.png"));
	mImg1->SetTexture("TwisterTex", TEXT("Texture\\RealAsset\\Map\\4\\pontif-twister-background.png"));

	// 화면 꽉 채우는 배경으로 사용 (원본 비율 유지하고 싶으면 별도 계산 필요)
	const float W = (float)RS.Width;
	const float H = (float)RS.Height;

	mImg0->SetSize(W, H);
	mImg1->SetSize(W, H);

	mImg0->SetPivot(FVector2D(0.f, 0.f));
	mImg1->SetPivot(FVector2D(0.f, 0.f));

	// 시작 위치: 0과 +W(살짝 겹치게)
	mX = 0.f;
	mY = 0.f;

	mImg0->SetPos(mX, mY);
	mImg1->SetPos(mX + (W - mOverlap), mY);

	// 처음 알파
	mImg0->SetTint(0.3f, 0.3f, 0.3f, 0.3f);
	mImg1->SetTint(0.3f, 0.3f, 0.3f, 0.3f);

	AddWidget(mImg0);
	AddWidget(mImg1);

	return true;
}

void CTwisterWidget::Update(float DeltaTime)
{
	CWindowWidget::Update(DeltaTime);

	if (mColorBG) mColorBG->SetTint(0.5f, 0.5f, 0.5f, mAlpha);
	if (mImg0)    mImg0->SetTint(0.5f, 0.5f, 0.5f, mAlpha);
	if (mImg1)    mImg1->SetTint(0.5f, 0.5f, 0.5f, mAlpha);

	if (!mMove) return;

	FResolution RS = CDevice::GetInst()->GetResolution();
	const float W = (float)RS.Width;

	// 우->좌로 이동
	mX -= mSpeed * DeltaTime;

	const float Span = (W - mOverlap);

	// 한 타일 길이만큼 넘어가면 되감기
	while (mX <= -Span) {
		mX += Span;
	}

	mImg0->SetPos(mX, mY);
	mImg1->SetPos(mX + Span, mY);


}