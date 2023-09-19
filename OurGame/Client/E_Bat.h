#pragma once
#include "Monster.h"
class E_Bat :
	public Monster
{
public:
	E_Bat();
	virtual ~E_Bat();
	E_Bat* Clone()
	{
		E_Bat* pBat = GameObject::Clone<E_Bat>();
		return pBat;
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
	virtual void OnCollisionEnter(Collider* _pOtherCollider);
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider);
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);


};