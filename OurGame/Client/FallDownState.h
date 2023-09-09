

#pragma once
#include "State.h"
class FallDownState :
	public State
{
public:
	FallDownState();
	virtual ~FallDownState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};