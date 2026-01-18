#include "CameraObject.h"
#include "../Component/CameraComponent.h"

CCameraObject::CCameraObject()
{
}

CCameraObject::CCameraObject(const CCameraObject& Obj)
{
}

CCameraObject::CCameraObject(CCameraObject&& Obj)
{
}

CCameraObject::~CCameraObject()
{
}

bool CCameraObject::Init()
{
	mCamera = CreateComponent<CCameraComponent>();

	mCamera->SetProjectionType(ECameraProjectionType::Ortho);
	mCamera->SetWorldPos(0.f, -10.f, 0.f);
	//mCamera->SetWorldPos(500.f, -60.f, 0.f); //중력체크용
	//mRoot->AddChild(mCamera);
	SetRootComponent(mCamera);
	return true;
}
