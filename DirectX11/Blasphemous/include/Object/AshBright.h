#pragma once
#include "SceneObject.h"
#include <random>
//쟂빛 그냥 랜덤으로 좌표 날려서 좌우로 뿌릴 예정 
// 볼렛 오브젝트랑 비슷한 느낌이지만 충돌체는 아니고, 그냥 배경에 뿌리는 용도임

class CAshBright : public CSceneObject
{
	friend class CScene;

protected:
	CAshBright();
	CAshBright(const CAshBright& Obj);
	CAshBright(CAshBright&& Obj);
	virtual ~CAshBright();

protected:
	
	CSharedPtr<class CSpriteComponent> mAshRoot; //눈덩어리 

	//애니메이션
	class CAnimation2D* mAshAnim = nullptr; // 눈 덩어리 애니메이션

	// 눈뿌리기 
	float mVelX = 0.f;     // 좌우 드리프트
	float mVelY = -150.f;  // 아래로 떨어지는 속도 (너 좌표계에서 아래가 -Y면 음수)

	// 스폰/리셋 범위
	float mMinX = -100.f;
	float mMaxX = 1380.f;

	// 화면 위에서 시작
	float mSpawnYMin = 400.f;
	float mSpawnYMax = 900.f;

	float mKillY = -900.f;
	// 랜덤 엔진
	std::mt19937 mRng;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void randomAsh();

	void SetArea(float MinX, float MaxX, float SpawnYMin, float SpawnYMax, float KillY)
	{
		mMinX = MinX; mMaxX = MaxX;
		mSpawnYMin = SpawnYMin; mSpawnYMax = SpawnYMax;
		mKillY = KillY;
	}

};

