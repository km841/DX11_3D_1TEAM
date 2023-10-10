#pragma once
#include "GameObject.h"
#include "BreakablePotCell.h"
#include "TimerObject.h"

class Pot_ProjectTile :
    public GameObject
{
public:
	Pot_ProjectTile(GameObject* _pBase);
	virtual ~Pot_ProjectTile();
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render();

	virtual void OnTriggerEnter(Collider* _pOther);
	virtual void OnTriggerStay(Collider* _pOther);
	virtual void OnTriggerExit(Collider* _pOther);

public:
	void BreakPots(const Vec3 _hitPos);
	void RestorePots(bool _isTemp);

private:
	GameObject* mpBasePot;
	std::vector<jh::BreakablePotCell*> mpPotCells;
	TimerObject pTimer;

	bool isGround = false;
};

