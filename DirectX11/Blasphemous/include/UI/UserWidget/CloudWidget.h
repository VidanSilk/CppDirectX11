#pragma once
#include "WindowWidget.h"
#include <functional>
#include <array>

class CCloudWidget : public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CCloudWidget();
	virtual ~CCloudWidget();

public:
	enum class EPhase
	{
		None,
		Closing,   // 덮기
		Hold,      // 덮인 상태(씬 전환 타이밍)
		Opening,   // 열기
		Done
	};

private:
	struct FLayer
	{
		CSharedPtr<class CImage> Img0;
		CSharedPtr<class CImage> Img1;

		float BaseAlpha = 1.f;   // 레이어 기본 투명도
		float Speed = 0.f;       // 가로 스크롤 속도(px/sec)

		float Width = 0.f;       // 타일 폭
		float Height = 0.f;
		float Y = 0.f;

		float X = 0.f;           // 타일 기준 X
		float Overlap = 80.f;    // 이음새 방지 겹침
	};

private:
	CSharedPtr<class CImage> mBack;   // 검정 오버레이(텍스처 없이 Tint만)
	CSharedPtr<class CImage> mMountain;
	std::array<FLayer, 3> mLayer;

	EPhase mPhase = EPhase::None;

	float mMountainAlpha = 0.f;
	float mMountainInMul = 1.0f;  // 등장 속도(1.0이면 동일)
	float mMountainOutMul = 1.6f;  // 퇴장 속도(클수록 더 천천히 사라짐)
	
	
	float mCoverAlpha = 0.f;     // 0~1 (덮는 정도)
	float mCloseTime = 0.35f;    // 덮기 시간
	float mOpenTime = 0.35f;     // 열기 시간
	float mHoldTime = 0.05f;
	float mAccTime = 0.f;

	std::function<void()> mOnCovered;
	std::function<void()> mOnFinished;

private:
	void ApplyAlphaToAll();

public:
	void StartTransition(const std::function<void()>& OnCovered,
		const std::function<void()>& OnFinished = nullptr,
		float CloseTime = 0.35f, float HoldTime = 0.3f, float OpenTime = 0.5f);

	bool IsDone() const { return mPhase == EPhase::Done; }

public:
	virtual bool Init() override;
	virtual void Update(float DeltaTime) override;
};