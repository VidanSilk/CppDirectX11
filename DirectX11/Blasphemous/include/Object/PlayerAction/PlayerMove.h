#pragma once

// 다시 설계해야함 
// IS-a 관계로 셋팅해서 문제가 생긴거엿음 
// has-a 관계로 셋팅해야함 
// is-a 관계 - 일반적인 상속 부모 - 자식 관계 예 : 동물(부모) -> 개, 고양이, 캥거루 등 (서브) 
// has-a 관계 - 부품 같은 느낌 -> 컴퓨터(객체)에는 cpu(객체1), gpu(객체2), ram..., 파워..등이 존재함, cpu를 포함하고 있다라고 표현가능 
// 즉, 컴퓨터 (객체)는 씨피유를 가지고 있다고 표현이 가능함 

class CPlayerObject;
class CAnimation2D;
class CMovementComponent;

class CPlayerMove  {

	friend class CScene;
	friend class CPlayerObject; // PlyaerObject가  CPlayerMove를 접근하게 해줌 
	
private:
	class CAnimation2D* mAnimation = nullptr;
	class CPlayerObject* mOwner = nullptr;
	class CMovementComponent* mMovement = nullptr; 

public:
	CPlayerMove();
	CPlayerMove(const CPlayerMove& Move);
	CPlayerMove(CPlayerMove&& Move);
	virtual ~CPlayerMove();

	virtual bool Init();
	virtual void Update(float DeltaTime);

	//이동 

	void Move();
	void Dodge();

	// 점프 
	void Jump();
	void JumpOff();
	void ForwardJump();
	void JumpLanding();

};

