#pragma once
#include "Monster.h"
class LORD_BOSS_ROLL;
class LORD_BOSS :
    public Monster
{
public:
	LORD_BOSS();
	virtual ~LORD_BOSS();
	LORD_BOSS* Clone()
	{
		LORD_BOSS* pLORD_BOSS = GameObject::Clone<LORD_BOSS>();
		return pLORD_BOSS;
	}

	virtual void SetBehaviorTree();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollisionEnter(Collider* _pOtherCollider); //다이나믹,스태틱이 충돌 일어났을떄 이함수로
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider); //키네틱이 충돌이일어났을때 이함수로
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);

public:
	void SetObject(LORD_BOSS_ROLL* _obj) { pObject = _obj; }

private:
	
	void SlowTurnLive();
	void SlowTurn(); // 안씀
	void Follow(); // 안씀 
	void PrevFollowSet();
	void PrevFollowLive();
	bool LookRay(); // 안씀


	void LaserFollow_Turn();
	void LaserPrevFollowSet();
	void LaserPrevFollowLive();
private:
	Vec3 RotDir;
	Vec3 PosDir;
	Vec3 PrevDir;

	Vec3 LaserPos = Vec3(0.f, 15.f, 20.f);
	Vec3 LaserRot = Vec3(-90.f, 360.f, 360.f);

	int Health;
	float TurnSpeed;
	float mMagnScale;
	bool isGround = false;
	bool isWall = false;
	bool isCrash = true;

	MonsterBasicState PrevState;

	LORD_BOSS_ROLL* pObject;
};

