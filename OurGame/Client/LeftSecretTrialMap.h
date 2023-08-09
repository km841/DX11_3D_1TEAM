#pragma once
#include "Map.h"
class LeftSecretTrialMap :
    public Map
{
public:
	LeftSecretTrialMap();
	virtual ~LeftSecretTrialMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();

};

