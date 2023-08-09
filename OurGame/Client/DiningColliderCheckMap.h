#pragma once
#include "Map.h"
class DiningColliderCheckMap :
    public Map
{
public:
	DiningColliderCheckMap();
	virtual ~DiningColliderCheckMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();
};

