#pragma once
#include "UserWidget.h"
#include "../Common/TextBlock.h"
#include "../Common/ProgressBar.h"
#include "../Common/Image.h"
class CPopeUIInfo : public CUserWidget
{
    friend class CSceneUIManager;

protected:
    CPopeUIInfo();
    ~CPopeUIInfo();

protected:
    CSharedPtr<CTextBlock> mNameText;
    CSharedPtr<CProgressBar> mHPBar;
    CSharedPtr<CImage> HPBack;

public:
    virtual bool Init();
    virtual void Render();
    virtual void Render(const FVector3D& Pos);

};

