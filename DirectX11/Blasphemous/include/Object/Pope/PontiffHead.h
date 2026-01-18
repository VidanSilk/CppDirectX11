#pragma once
#include "../SceneObject.h"
// 이친구도 석상 역할 
// pontiff_Headidle따로 뺴서 역할만 하되 좌표 맞춰서 얼굴 열렸다가 닫혔다가 하기. 
class CPontiffBody;

class CPontiffHead : public CSceneObject
{
	friend class CScene;

protected:
	CPontiffHead();
	CPontiffHead(const CPontiffHead& Obj);
	CPontiffHead(CPontiffHead&& Obj);
	virtual ~CPontiffHead();

	class CAnimation2D* mAnimation = nullptr;
	CSharedPtr<class CSpriteComponent> mRoot;
//	CSharedPtr<class CWidgetComponent> mWidgetCoponent;
	//콜라이더는 조금 생각 해보기. 
	// 무적 판정이라 사실 안넣어줘도 됨 
private:
	CPontiffBody* mBody = nullptr;
	FVector3D mBodyOffset = FVector3D(0.f, 200.f, 0.f);

public:

	virtual bool Init();
	virtual void Update(float DeltaTime);
public:
	void SetBody(CPontiffBody* body) { mBody = body; }
	void SetBodyOffset(const FVector3D& off) { mBodyOffset = off; }
};

