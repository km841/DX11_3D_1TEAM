#pragma once
#include "Map.h"
class RightSecretPassageMap :
    public Map
{
public:
	RightSecretPassageMap();
	virtual ~RightSecretPassageMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();

	virtual void Enter();
	virtual void Exit();
};

