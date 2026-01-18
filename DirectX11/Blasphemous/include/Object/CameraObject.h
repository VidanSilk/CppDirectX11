#pragma once
#include "SceneObject.h"

class CCameraObject : public CSceneObject
{
	friend class CScene;

private :
	CSharedPtr<class CCameraComponent> mCamera;
	
protected:
	CCameraObject();
	CCameraObject(const CCameraObject& Obj);
	CCameraObject(CCameraObject&& Obj);
	virtual ~CCameraObject();
	
public:
	virtual bool Init();


	

};

