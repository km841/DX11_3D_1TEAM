#pragma once
#include "Map.h"
class CorridorRightMap :
    public Map
{
public:
	CorridorRightMap();
	virtual ~CorridorRightMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();
};

