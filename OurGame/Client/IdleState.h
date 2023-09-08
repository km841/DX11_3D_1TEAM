#pragma once
#include "State.h"
class IdleState :
    public State
{
public:
	IdleState();
	virtual ~IdleState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

