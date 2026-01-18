#pragma once
#include "WindowWidget.h"
#include <functional>

class CPlayerDieWidget : public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CPlayerDieWidget();
	virtual ~CPlayerDieWidget();

private:
	CSharedPtr<class CImage> mBack;     // 검정 빽그라운드 
	CSharedPtr<class CImage> mGameOver;   //게임오버 임지

	float mAlpha = 0.f;
	float mFadeInTime = 0.35f;

	std::function<void()> mOnReturnToStart;
	float mHoldAfterFade = 2.5f;   // 페이드 끝나고 1.5초 보여주기
	float mHoldAcc = 0.f;
	bool  mCalled = false;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	void SetOnReturnToStart(const std::function<void()>& CB) { 
		mOnReturnToStart = CB; 
	}
};


