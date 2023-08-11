#pragma once
#include "Map.h"
class LeftSecretFightMap :
    public Map
{
public:
	LeftSecretFightMap();
	virtual ~LeftSecretFightMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();
};
