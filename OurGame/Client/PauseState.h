
#pragma once
#include "State.h"
class PauseState :
	public State
{
public:
	PauseState();
	virtual ~PauseState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};