#pragma once
#include "../BulletObject.h"

// 1 ~ 2개 씩 스폰하기
// 애도 좌표 고정 되어 있음 


class CPopeToxic : public CBulletObject
{

		friend class CScene;

	private:
		float mToxicDamage = 9.0f;

	public:
	
		float GetToxicDamage() const {
			return mToxicDamage;
		}

		void SetToxic(const float& ToxicDmg) {
			mToxicDamage = ToxicDmg;
		}

	protected:
		CPopeToxic();
		CPopeToxic(const CPopeToxic& Obj);
		CPopeToxic(CPopeToxic&& Obj);
		virtual ~CPopeToxic();
		//class CAnimation2D* mAnimation = nullptr;
		CSharedPtr<class CColliderSphere2D> mToxicBody;
		


	public:
		virtual bool Init();
		virtual void Update(float DeltaTime);

	private:
		virtual void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);


};

