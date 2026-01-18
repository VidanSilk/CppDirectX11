#pragma once
#include "WindowWidget.h"

//스테이지2 배경 겸 위젯역할 
class CTwisterWidget : public CWindowWidget
{
	friend class CSceneUIManager;

protected:
	CTwisterWidget();
	virtual ~CTwisterWidget();

private:
	CSharedPtr<class CImage> mColorBG;

	CSharedPtr<class CImage> mImg0;
	CSharedPtr<class CImage> mImg1;

	float mSpeed = 300.f;      // px/sec (우->좌로 흐르는 속도)
	float mOverlap = 2.f;     // 이음새 방지용 겹침 픽셀
	float mX = 0.f;           // 타일 기준 X
	float mY = 0.f;

	float mAlpha = 0.02f;       // 전체 투명도
	bool  mMove = true;

public:
	void SetSpeed(float Speed) { mSpeed = Speed; }
	void SetAlpha(float Alpha) { mAlpha = Alpha; }
	void SetMove(bool Move) { mMove = Move; }

public:
	virtual bool Init() override;
	virtual void Update(float DeltaTime) override;
};