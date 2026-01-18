#include "HeadInfo.h"

#include "../../Device.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"


CHeadInfo::CHeadInfo()
{
}

CHeadInfo::~CHeadInfo()
{
}

bool CHeadInfo::Init()
{
	CUserWidget::Init();

	mNameText = mScene->GetUIManager()->CreateWidget<CTextBlock>("NameText");

	mNameText->SetText(L"Last Son of the Miracle");
	mNameText->SetFontSize(20.f);
	mNameText->SetPos(-270.f, -250.f);
//	mNameText->SetPivot(FVector2D(0.5f, 0.5f));
	mNameText->SetAlignH(ETextAlignH::Center);
	mNameText->SetSize(600.f, 100.f);
	mNameText->SetTextColor(255, 255, 0, 255);

	AddWidget(mNameText);

	CProgressBar* HPBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("HPBar");

	HPBar->SetPos(-300.f, -250.f);
	HPBar->SetSize(650.f, 20.f);
	//block_bar.png
	//MPBar.png
	HPBar->SetTexture(EProgressBarImageType::Back, "HPBarBack", TEXT("Texture\\RealAsset\\UIimage\\inventory-spritesheet_72.png"));
	HPBar->SetTexture(EProgressBarImageType::Fill, "HPBar", TEXT("Texture\\RealAsset\\UIimage\\inventory-spritesheet_121.png"));
	HPBar->SetPercent(1.0f);
	AddWidget(HPBar);

	//CImage* HPBack = mScene->GetUIManager()->CreateWidget<CImage>("HPBarBackImg");
	//HPBack->SetPos(-304.f, -253.f);     // HPBar보다 약간 위/왼쪽
	//HPBack->SetSize(658.f, 26.f);       // HPBar보다 약간 크게
	//HPBack->SetPivot(FVector2D(0.f, 0.f));
	//HPBack->SetTexture("HPBarBackTex", TEXT("Texture\\RealAsset\\UIimage\\inventory-spritesheet_72.png"));
	//AddWidget(HPBack);

	//// 2) ProgressBar는 Fill 중심으로(Back은 그냥 둬도 되지만 겹칠 수 있음)
	//CProgressBar* HPBar = mScene->GetUIManager()->CreateWidget<CProgressBar>("HPBar");
	//HPBar->SetPos(-300.f, -250.f);
	//HPBar->SetSize(650.f, 20.f);
	//HPBar->SetTexture(EProgressBarImageType::Fill, "HPBar", TEXT("Texture\\RealAsset\\UIimage\\inventory-spritesheet_121.png"));
	//// (가능하면) ProgressBar Back을 안 그리게 하거나, 투명으로 만들 수 있으면 처리
	//HPBar->SetPercent(1.0f);
	//AddWidget(HPBar);

	return true;

}

void CHeadInfo::Render()
{
	CUserWidget::Render();
}

void CHeadInfo::Render(const FVector3D& Pos)
{
	CUserWidget::Render(Pos);

}
