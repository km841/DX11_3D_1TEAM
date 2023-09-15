#pragma once

#include "GameObject.h"
#include "RigidBody.h"

class PlayerInChecker : public GameObject
{
public:

	PlayerInChecker();
	virtual ~PlayerInChecker();

	PlayerInChecker* Clone()
	{
		PlayerInChecker* pPlayerInChecker = GameObject::Clone<PlayerInChecker>();
		return pPlayerInChecker;
	}




public:
	virtual void Initialize();
	virtual void Update();

	bool isIn;

};