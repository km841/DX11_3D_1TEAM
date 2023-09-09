
#pragma once
#include "State.h"
class EvasionState :
	public State
{
public:
	EvasionState();
	virtual ~EvasionState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};