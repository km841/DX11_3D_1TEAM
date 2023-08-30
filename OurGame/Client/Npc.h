#pragma once
#include "GameObject.h"
class Npc :
    public GameObject
{
public:
	Npc();
	virtual ~Npc();
	Npc* Clone()
	{
		Npc* pNpc = GameObject::Clone<Npc>();
		return pNpc;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();
};

