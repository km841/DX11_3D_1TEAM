#pragma once
#include "Map.h"
class EntranceHallMap :
    public Map
{
public:
	EntranceHallMap();
	virtual ~EntranceHallMap();

public:
	virtual void Initialize();
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();
};

