
#pragma once
#include "Monster_ProjectTile.h"
class Grimace_ProjectTile :
	public Monster_ProjectTile
{
public:
	Grimace_ProjectTile();
	virtual ~Grimace_ProjectTile();
	Grimace_ProjectTile* Clone()
	{
		Grimace_ProjectTile* pGrimace_projecttile = GameObject::Clone<Grimace_ProjectTile>();
		return pGrimace_projecttile;
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
	void FollowPos();
	void Mirror();
	void FollowRot();

	bool isbool = false;
};