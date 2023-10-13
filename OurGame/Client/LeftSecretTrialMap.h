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
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();	
	virtual void Enter();
	virtual void Exit();
private:
	void InitObjectAdd();
	void InitColliderAdd();
	void FuncObjectAdd();
private:
	int mSpawnPoint = -1;
};

