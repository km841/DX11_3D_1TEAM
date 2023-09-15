

#pragma once
#include "State.h"
class ClimingEndState :
	public State
{

public:
	ClimingEndState();
	virtual ~ClimingEndState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;

};