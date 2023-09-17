

#pragma once
#include "State.h"
class HittingState :
	public State
{
public:
	HittingState();
	virtual ~HittingState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};