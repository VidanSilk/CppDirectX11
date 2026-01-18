#pragma once
#include "../BulletObject.h"

// 좌표 고정되어 있음 6 곳 스폰
// 3발 쏘고 다음 좌표로 이동.  

class CPopeFireBall : public CBulletObject
{

	friend class CScene;

	private:

		float mFireBallDamage = 12.0f;
		FVector3D mPrevPos;
		bool      mPrevPosInit = false;
		// 스프라이트 기본 방향 보정용(필요할 때만 값 바꾸면 됨)
		float     mAngleOffsetDeg = 0.f;

		bool mExploded = false;

	public:

		float GetFireBallDamage() const {
			return mFireBallDamage;
		}

		void SetFireBall(const float& FireDmg) {
			mFireBallDamage = FireDmg;
		}
		//void SetBulletCollisionProfile(const std::string& Name);
		float RadToDeg(float rad)
		{
			return rad * (180.0f / 3.14f);
		}
	protected:
		CPopeFireBall();
		CPopeFireBall(const CPopeFireBall & Obj);
		CPopeFireBall(CPopeFireBall && Obj);
		virtual ~CPopeFireBall();
		//CSharedPtr<class CColliderSphere2D> mFireBody; //Obb로 수정하는게 좋을듯?
		CSharedPtr<class CColliderOBB2D> mFireBody;
		//CSharedPtr<class CColliderAABB2D> mFireBody;
		//class CAnimation2D* mAnimation = nullptr;

	public:

		virtual bool Init();
		virtual void Update(float DeltaTime);
		void FireStartMotion();

	private:
		virtual void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);
		void FiretoTarget(CPlayerObject* Player); 
		void OnFireEffectEnd();
};

