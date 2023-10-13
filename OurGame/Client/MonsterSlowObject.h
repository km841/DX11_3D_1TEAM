#pragma once
#include "GameObject.h"
class MonsterSlowObject :
    public GameObject
{
public:
	MonsterSlowObject();
	virtual ~MonsterSlowObject();
	MonsterSlowObject* Clone()
	{
		MonsterSlowObject* pMonsterSlowObject = GameObject::Clone<MonsterSlowObject>();
		return pMonsterSlowObject;
	}
public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

	bool GetColCheck() { return isColCheck; }
	void SetColCheck(bool _ColCheck) { isColCheck = _ColCheck; }

public:
	virtual void OnCollisionEnter(Collider* _pOtherCollider); //다이나믹,스태틱이 충돌 일어났을떄 이함수로
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider); //키네틱이 충돌이일어났을때 이함수로
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);

private:
	bool isColCheck = false;
};

