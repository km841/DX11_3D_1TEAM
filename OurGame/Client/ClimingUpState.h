
#pragma once
#include "State.h"
class ClimingUpState :
	public State
{

public:
	ClimingUpState();
	virtual ~ClimingUpState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;

private:
	int mCount_Ani;
};