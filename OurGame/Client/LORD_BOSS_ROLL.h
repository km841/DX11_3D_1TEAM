#pragma once
#include "Monster.h"
class LORD_BOSS;
class LORD_BOSS_ROLL :
    public Monster
{
public:
	LORD_BOSS_ROLL();
	virtual ~LORD_BOSS_ROLL();
	LORD_BOSS_ROLL* Clone()
	{
		LORD_BOSS_ROLL* pLORD_BOSS_ROLL = GameObject::Clone<LORD_BOSS_ROLL>();
		return pLORD_BOSS_ROLL;
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

	void SetLORD_BOSS(LORD_BOSS* _Boss) { pLord_Boss = _Boss; }
private:


private:
	Vec3 Dir;
	Vec3 PrevDir;
	int Health;

	MonsterBasicState PrevState;

	LORD_BOSS* pLord_Boss;
};

