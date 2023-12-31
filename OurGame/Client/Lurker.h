#pragma once
#include "Monster.h"
class Lurker :
	public Monster
{
public:
	Lurker();
	virtual ~Lurker();
	Lurker* Clone()
	{
		Lurker* pLurker = GameObject::Clone<Lurker>();
		return pLurker;
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
	virtual void OnCollisionEnter(Collider* _pOtherCollider); //���̳���,����ƽ�� �浹 �Ͼ���� ���Լ���
	virtual void OnCollisionStay(Collider* _pOtherCollider);
	virtual void OnCollisionExit(Collider* _pOtherCollider);

	virtual void OnTriggerEnter(Collider* _pOtherCollider); //Ű��ƽ�� �浹���Ͼ���� ���Լ���
	virtual void OnTriggerStay(Collider* _pOtherCollider);
	virtual void OnTriggerExit(Collider* _pOtherCollider);

	void SlowTurnLive();
	void PrevFollowSet();
	void PrevFollowLive();
private:
	Vec3 dir;
	Vec3 PosDir;
	Vec3 RotDir;
};