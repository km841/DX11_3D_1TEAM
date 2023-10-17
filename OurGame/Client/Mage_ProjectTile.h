#pragma once
#include "Monster_ProjectTile.h"
class Mage_ProjectTile :
    public Monster_ProjectTile
{
public:
	Mage_ProjectTile();
	virtual ~Mage_ProjectTile();
	Mage_ProjectTile* Clone()
	{
		Mage_ProjectTile* pMage_projecttile = GameObject::Clone<Mage_ProjectTile>();
		return pMage_projecttile;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void OnCollisionEnter(Collider * _pOtherCollider); //다이나믹,스태틱이 충돌 일어났을떄 이함수로
	virtual void OnCollisionStay(Collider * _pOtherCollider);
	virtual void OnCollisionExit(Collider * _pOtherCollider);

	virtual void OnTriggerEnter(Collider * _pOtherCollider); //키네틱이 충돌이일어났을때 이함수로
	virtual void OnTriggerStay(Collider * _pOtherCollider);
	virtual void OnTriggerExit(Collider * _pOtherCollider);

	void SetLight(GameObject* _pLight) { mpLight = _pLight; }

private:
	void FollowPos();
	void FollowRot();
	void Mirror();

private:
	GameObject* mpLight;
};