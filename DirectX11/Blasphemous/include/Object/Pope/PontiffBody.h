#pragma once
#include "../SceneObject.h"

// 어차피 콜라이더 없고, 백그라운드역할임 
//그럼 배경처럼 깔아도 문제 없어보임 

class CPontiffBody : public CSceneObject
{
	friend class CScene;

protected:
	CPontiffBody();
	CPontiffBody(const CPontiffBody& Obj);
	CPontiffBody(CPontiffBody&& Obj);
	virtual ~CPontiffBody();


	class CAnimation2D* mAnimation = nullptr;
	CSharedPtr<class CSpriteComponent> mRoot;

public:

	virtual bool Init();

};

 