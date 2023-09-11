#pragma once
#include "GameObject.h"
class Player;
class Monster :
    public GameObject
{
public:
	Monster();
	virtual ~Monster();
	Monster* Clone()
	{
		Monster* pMonster = GameObject::Clone<Monster>();
		return pMonster;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();
};

