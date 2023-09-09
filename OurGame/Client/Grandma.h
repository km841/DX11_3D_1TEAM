#pragma once
#include "GameObject.h"

class State_Grandma;
class Grandma :
	public GameObject
{
public:
	Grandma();
	virtual ~Grandma();
	Grandma* Clone()
	{
		Grandma* pGrandma = GameObject::Clone<Grandma>();
		return pGrandma;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnTriggerEnter(Collider* pOtherCollider);
	virtual void OnTriggerStay(Collider* pOtherCollider);
	virtual void OnTriggerExit(Collider* pOtherCollider);

public:
	void StateChange_Grandma(GrandmaState _eState);

public:
	static Grandma* spGrandma;
	static Grandma* GetGrandma();

	State_Grandma* mState_Grandma[GRANDMA_STATE_COUNT]; //조건 확인용
	State_Grandma* mActiveState_Grandma; //현재 상태 확인

};