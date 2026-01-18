#include "PontiffHead.h"
#include "PontiffBody.h"
#include "../../Scene/Scene.h"
#include "../../Component/StaticMeshComponent.h"
#include "../../Component/SpriteComponent.h"
#include "../../Animation/Animation2D.h"

CPontiffHead::CPontiffHead() : CSceneObject()
{
}

CPontiffHead::CPontiffHead(const CPontiffHead& Obj) : CSceneObject(Obj){

}


CPontiffHead::CPontiffHead(CPontiffHead&& Obj) : CSceneObject(Obj)
{
}

CPontiffHead::~CPontiffHead()
{
}

bool CPontiffHead::Init()
{
    if (!CSceneObject::Init()) return false;
	
	mRoot = CreateComponent<CSpriteComponent>();
	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();

	SetRootComponent(mRoot);
	mRoot->SetPivot(0.55f, 0.1275f);

    mAnimation->AddSequence("pontiff_Headidle", 4.0f, 0.7f, true, false); // 기본 헤드 -> 석상으로 뺴기 
	mAnimation->ChangeAnimation("pontiff_Headidle");
	return true;
}

void CPontiffHead::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime); 

	if (mBody && mBody->IsActive())
	{
		SetWorldPos(mBody->GetWorldPosition() + mBodyOffset);
	}
}