

#pragma once
#include "State.h"
class FallState :
	public State
{
public:
	FallState();
	virtual ~FallState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};