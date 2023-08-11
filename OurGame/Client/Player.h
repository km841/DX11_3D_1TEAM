#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
public:
    Player();
	virtual ~Player();
	Player* Clone()
	{
		Player* pPlayer = GameObject::Clone<Player>();
		return pPlayer;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

public:

};

