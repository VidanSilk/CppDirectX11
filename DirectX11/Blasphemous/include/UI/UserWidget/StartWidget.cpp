#include "StartWidget.h"

#include "../../Device.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneMain.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/SceneUIManager.h"
#include "../../Scene/SceneEditor.h"
#include "../Common/Button.h"
#include "../Common/Image.h"
#include "../../Share/Log.h"

CStartWidget::CStartWidget()
{
}

CStartWidget::~CStartWidget()
{
}

bool CStartWidget::Init()
{
	CUserWidget::Init();

	FResolution RS = CDevice::GetInst()->GetResolution();

	//배경
	CSharedPtr<CImage> Back = mScene->GetUIManager()->CreateWidget<CImage>("Back");
	CSharedPtr<CImage> Title = mScene->GetUIManager()->CreateWidget<CImage>("Title");
	//버튼을 추가하기 
	mButton = mScene->GetUIManager()->CreateWidget<CButton>("TestButton");
	mEditorButton = mScene->GetUIManager()->CreateWidget<CButton>("SceneEditorButton");
	Back->SetTexture("StartBakc", TEXT("Texture/RealAsset/UIimage/MainMenuBackground_0.png"));
	Back->SetSize(1280.f, 720.f); //원본 640 x 360

	// 애니메이션 0 ~ 21 22장 
	//Title->SetTexture("StartTitle", TEXT("Texture\\RealAsset\\UIimage\\MainMenuPenitent-anim-spritesheet_0.png"));
	
	Title->SetTexture("StartTitle", TEXT("Texture\\RealAsset\\UIimage\\TestUITitle.png"));
	// 나중에 미세조정 들어가기 
	Title->SetSize(1050.f , 720.f); //520x360
	Title->SetBrushAnimation(true);
	//  14080 / 22 = 540
	for (int i = 0; i < 22; ++i)
	{
		Title->AddBurshFrame( i * 640.f , 0.f, 640.f, 360.f);
	}
	Title->SetAnimationPlayRate(0.05f);
//	Title->SetAnimationPlayTime(20.f);

	//뎁스이슈인가?버튼이 앞에있으면 버튼이 안먹힘 
	Back->SetZOrder(5);
	Title->SetZOrder(7);
	mButton->SetZOrder(10);
	mEditorButton->SetZOrder(10);
	
	AddWidget(Back);
	AddWidget(Title);
	AddWidget(mButton);
	AddWidget(mEditorButton);

	mButton->SetPos(1100.f, 225.f);
	mButton->SetSize(80.f, 80.f);
	mButton->SetPivot(FVector2D(0.5f, 0.5f));
	mButton->SetTexture(EButtonState::Normal, "StartButton", TEXT("Texture\\RealAsset\\UIimage\\Start_Button.png"));
	mButton->SetTexture(EButtonState::Hovered, "StartButton");
	mButton->SetTexture(EButtonState::Click, "StartButton", TEXT("Texture\\RealAsset\\UIimage\\Start_Button.png"));
	mButton->SetTexture(EButtonState::Disable, "StartButton", TEXT("Texture\\RealAsset\\UIimage\\Start_Button.png"));

	mButton->SetTint(EButtonState::Normal, 0.8f, 0.8f, 0.8f);
	mButton->SetTint(EButtonState::Hovered, 1.f, 1.f, 1.f);
	mButton->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mButton->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	mButton->SetEventCallBack(EButtonEventState::Click, this, &CStartWidget::StartButtonClick);

	// 에디터 모드 가는 버튼 
	mEditorButton->SetPos(1100.f, 125.f);
	mEditorButton->SetSize(80.f, 80.f);
	mEditorButton->SetPivot(FVector2D(0.5f, 0.5f));
	mEditorButton->SetTexture(EButtonState::Normal, "EditButton", TEXT("Texture\\RealAsset\\UIimage\\Edit_Button.png"));
	mEditorButton->SetTexture(EButtonState::Hovered, "EditButton");
	mEditorButton->SetTexture(EButtonState::Click, "EditButton", TEXT("Texture\\RealAsset\\UIimage\\Edit_Button.png"));
	mEditorButton->SetTexture(EButtonState::Disable, "EditButton", TEXT("Texture\\RealAsset\\UIimage\\Edit_Button.png"));
	mEditorButton->SetTint(EButtonState::Normal, 0.8f, 0.8f, 0.8f);
	mEditorButton->SetTint(EButtonState::Hovered, 1.f, 1.f, 1.f);
	mEditorButton->SetTint(EButtonState::Click, 0.5f, 0.5f, 0.5f);
	mEditorButton->SetTint(EButtonState::Disable, 0.1f, 0.1f, 0.1f);

	mEditorButton->SetEventCallBack(EButtonEventState::Click, this, &CStartWidget::StartEidtButtonClick);

	return true;
}


void CStartWidget::StartButtonClick()
{
	CLog::PrintLog("Start Button Click");

	CSceneManager::GetInst()->CreateLoadScene<CSceneMain>();
}


void CStartWidget::StartEidtButtonClick()
{
	CLog::PrintLog("Start SceneEditor Button Click");

	CSceneManager::GetInst()->CreateLoadScene<CSceneEditor>();
}