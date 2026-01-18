#include "CloudWidget.h"

#include "../../Device.h"
#include "../../Scene/Scene.h"
#include "../../Scene/SceneUIManager.h"
#include "../Common/Image.h"

CCloudWidget::CCloudWidget()
{
}

CCloudWidget::~CCloudWidget()
{
}

bool CCloudWidget::Init()
{
	CWindowWidget::Init();

	FResolution RS = CDevice::GetInst()->GetResolution();

	// 이 위젯 자체는 화면 전체 기준
	SetPos(0.f, 0.f);
	SetSize((float)RS.Width, (float)RS.Height);
	SetPivot(FVector2D(0.f, 0.f));

	mMountain = mScene->GetUIManager()->CreateWidget<CImage>("Cloud_Mountain");
	mMountain->SetPos(0.f, 0.f);
	mMountain->SetSize((float)RS.Width, (float)RS.Height);
	mMountain->SetPivot(FVector2D(0.f, 0.f));
	mMountain->SetTexture("AshMountain", TEXT("Texture\\RealAsset\\Map\\4\\ash-mountain-spritesheet_10.png"));
	mMountain->SetTint(1.f, 1.f, 1.f);
	AddWidget(mMountain);

	// 1) 검정 오버레이(텍스처 없이 Tint만) - 구름 구멍/투명부 때문에 배경이 비치지 않게
	mBack = mScene->GetUIManager()->CreateWidget<CImage>("Cloud_Back");
	mBack->SetPos(0.f, 0.f);
	mBack->SetSize((float)RS.Width, (float)RS.Height);
	mBack->SetPivot(FVector2D(0.f, 0.f));
	mBack->SetTint(1.f, 1.f,1.f);
	AddWidget(mBack);

	// =========================
	// 2) 3장 구름 텍스처(레이어)
	// 원본 이미지 크기(비율 유지용)
	// ash-clouds_0 : 818 x 380
	// ash-clouds_1 : 850 x 372
	// ash-clouds_2 : 692 x 252
	// =========================

	struct FTexInfo { const TCHAR* Path; float W; float H; };
	FTexInfo Tex[3] =
	{
		{ TEXT("Texture\\RealAsset\\Map\\4\\ash-clouds_0.png"), 818.f, 380.f },
		{ TEXT("Texture\\RealAsset\\Map\\4\\ash-clouds_1.png"), 850.f, 372.f },
		{ TEXT("Texture\\RealAsset\\Map\\4\\ash-clouds_2.png"), 692.f, 252.f }
	};

	// 레이어 파라미터(뒤->앞)
	// 뒤: 느리고 연함 / 앞: 빠르고 진함
	float BaseAlpha[3] = { 0.45f, 0.70f, 1.00f };
	float Speed[3] = { 40.f,  80.f,  140.f };
	float WidthMul[3] = { 1.15f, 1.20f, 1.30f }; // 화면 대비 타일 폭 배율(덮임용)

	for (int i = 0; i < 3; ++i)
	{
		mLayer[i].BaseAlpha = BaseAlpha[i];
		mLayer[i].Speed = Speed[i];
		mLayer[i].Overlap = 90.f;

		// 타일 폭을 화면 기준으로 잡고 비율 유지해서 높이 계산
		mLayer[i].Width = RS.Width * WidthMul[i];
		float Aspect = Tex[i].H / Tex[i].W;
		mLayer[i].Height = mLayer[i].Width * Aspect;

		// Y 배치(조금씩 높이 차)
		// 좌표계가 위->아래 증가인 경우 바닥에 붙이려면 (RS.Height - Height)
		// 만약 반대로 보이면 Y=0 쪽으로 바꿔.
		mLayer[i].Y = (float)RS.Height - mLayer[i].Height - i * 25.f;

		mLayer[i].Img0 = mScene->GetUIManager()->CreateWidget<CImage>("Cloud_Layer_" + std::to_string(i) + "_0");
		mLayer[i].Img1 = mScene->GetUIManager()->CreateWidget<CImage>("Cloud_Layer_" + std::to_string(i) + "_1");

		mLayer[i].Img0->SetTexture("AshCloudTex_" + std::to_string(i), Tex[i].Path);
		mLayer[i].Img1->SetTexture("AshCloudTex_" + std::to_string(i), Tex[i].Path);

		mLayer[i].Img0->SetSize(mLayer[i].Width, mLayer[i].Height);
		mLayer[i].Img1->SetSize(mLayer[i].Width, mLayer[i].Height);

		mLayer[i].Img0->SetPivot(FVector2D(0.f, 0.f));
		mLayer[i].Img1->SetPivot(FVector2D(0.f, 0.f));

		// 타일 시작 위치(레이어마다 조금씩 어긋나게)
		mLayer[i].X = -i * 220.f;

		mLayer[i].Img0->SetPos(mLayer[i].X, mLayer[i].Y);
		mLayer[i].Img1->SetPos(mLayer[i].X + (mLayer[i].Width - mLayer[i].Overlap), mLayer[i].Y);

		// 처음은 안 보이게
		mLayer[i].Img0->SetTint(1.f, 1.f, 1.f, 0.f);
		mLayer[i].Img1->SetTint(1.f, 1.f, 1.f, 0.f);

		AddWidget(mLayer[i].Img0);
		AddWidget(mLayer[i].Img1);
	}

	mPhase = EPhase::None;
	mCoverAlpha = 0.f;
	return true;
}

void CCloudWidget::ApplyAlphaToAll()
{
	// Mountain (배경)
	if (mMountain)
		mMountain->SetTint(1.f, 1.f, 1.f, 1.0f * mCoverAlpha);

	// 배경(검정)도 같이 올려서 완전히 가리기
	float cover = (mCoverAlpha > mMountainAlpha) ? mCoverAlpha : mMountainAlpha;
	if (mBack)
		mBack->SetTint(0.f, 0.f, 0.f, 0.55f * cover);

	for (int i = 0; i < 3; ++i)
	{
		float A = mLayer[i].BaseAlpha * mCoverAlpha;
		mLayer[i].Img0->SetTint(1.f, 1.f, 1.f, A);
		mLayer[i].Img1->SetTint(1.f, 1.f, 1.f, A);
	}
}

void CCloudWidget::StartTransition(const std::function<void()>& OnCovered,
	const std::function<void()>& OnFinished,
	float CloseTime, float HoldTime, float OpenTime)
{
	mOnCovered = OnCovered;
	mOnFinished = OnFinished;

	mCloseTime = CloseTime;
	mHoldTime = HoldTime;
	mOpenTime = OpenTime;

	mAccTime = 0.f;
	mCoverAlpha = 0.f;
	mMountainAlpha = 0.f;   
	mPhase = EPhase::Closing;

	ApplyAlphaToAll();
}

void CCloudWidget::Update(float DeltaTime)
{
	CWindowWidget::Update(DeltaTime);

	if (mPhase == EPhase::None || mPhase == EPhase::Done)
		return;


	// 1) 구름 가로 무한 스크롤(덮기/열기 상태와 무관하게 계속 움직이면 더 자연스러움)
	for (int i = 0; i < 3; ++i)
	{
		mLayer[i].X -= mLayer[i].Speed * DeltaTime;

		float TileSpan = (mLayer[i].Width - mLayer[i].Overlap);
		while (mLayer[i].X <= -TileSpan)
			mLayer[i].X += TileSpan;

		mLayer[i].Img0->SetPos(mLayer[i].X, mLayer[i].Y);
		mLayer[i].Img1->SetPos(mLayer[i].X + TileSpan, mLayer[i].Y);
	}

	// 2) 전환(알파로 덮고/열기)

	if (mPhase == EPhase::Closing)
	{
		// 구름
		mCoverAlpha += (mCloseTime <= 0.f) ? 1.f : (DeltaTime / mCloseTime);
		if (mCoverAlpha > 1.f) mCoverAlpha = 1.f;

		// 산(등장): 동일하거나 조금 느리게 하고 싶으면 mMountainInMul을 1.2 같은 값으로
		float mountainInTime = (mCloseTime <= 0.f) ? 0.01f : (mCloseTime * mMountainInMul);
		mMountainAlpha += DeltaTime / mountainInTime;
		if (mMountainAlpha > 1.f) mMountainAlpha = 1.f;

		ApplyAlphaToAll();

		if (mCoverAlpha >= 1.f)
		{
			mPhase = EPhase::Hold;
			mAccTime = 0.f;
			if (mOnCovered) mOnCovered();
		}
	}
	else if (mPhase == EPhase::Hold)
	{
		mAccTime += DeltaTime;
		if (mAccTime >= mHoldTime)
			mPhase = EPhase::Opening;
	}
	else if (mPhase == EPhase::Opening)
	{
		// 구름(기존 속도)
		mCoverAlpha -= (mOpenTime <= 0.f) ? 1.f : (DeltaTime / mOpenTime);
		if (mCoverAlpha < 0.f) mCoverAlpha = 0.f;

		// 산(퇴장): 구름보다 더 천천히 사라지게
		float mountainOutTime = (mOpenTime <= 0.f) ? 0.01f : (mOpenTime * mMountainOutMul);
		mMountainAlpha -= DeltaTime / mountainOutTime;
		if (mMountainAlpha < 0.f) mMountainAlpha = 0.f;

		ApplyAlphaToAll();

		//  구름이 먼저 끝나도, 산이 남아있으면 계속 유지
		if (mCoverAlpha <= 0.f && mMountainAlpha <= 0.f)
		{
			mPhase = EPhase::Done;
			if (mOnFinished) mOnFinished();
		}
	}
}