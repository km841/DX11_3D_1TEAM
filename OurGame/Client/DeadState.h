
#pragma once
#include "State.h"
class DeadState :
	public State
{
public:
	DeadState();
	virtual ~DeadState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};