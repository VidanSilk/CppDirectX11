#include "PontiffBody.h"

#include "../../Scene/Scene.h"
#include "../../Component/StaticMeshComponent.h"
#include "../../Component/SpriteComponent.h"
#include "../../Animation/Animation2D.h"

#include "../../Vector3D.h"


CPontiffBody::CPontiffBody() : CSceneObject()
{
	
}

CPontiffBody::CPontiffBody(const CPontiffBody& Obj) : CSceneObject(Obj)
{
}

CPontiffBody::CPontiffBody(CPontiffBody&& Obj) : CSceneObject(Obj)
{
}

CPontiffBody::~CPontiffBody()
{
}

bool CPontiffBody::Init()
{
	if (!CSceneObject::Init()) {
		return false;
	}
	mRoot = CreateComponent<CSpriteComponent>();
	mAnimation = mRoot->CreateAnimation2D<CAnimation2D>();
	SetRootComponent(mRoot);
	mRoot->SetPivot(0.5f, 0.5f);
	mRoot->SetTexture("PontiffBody");

	mAnimation->AddSequence("pontiff_Bodyidle", 3.0f, 0.4f, true, false);
	mAnimation->ChangeAnimation("pontiff_Bodyidle");

	return true;
}

