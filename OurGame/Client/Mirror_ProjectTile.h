#pragma once
#include "GameObject.h"
class Mirror_ProjectTile :
    public GameObject
{
public:
	Mirror_ProjectTile();
	virtual ~Mirror_ProjectTile();
	Mirror_ProjectTile* Clone()
	{
		Mirror_ProjectTile* pMirror_projecttile = GameObject::Clone<Mirror_ProjectTile>();
		return pMirror_projecttile;
	}

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


private:

	void MirrorPos();

	float mHP; // 피통
	float mSpeed; //이동속도
	int mAttackDamage; // 공격력

	
};

