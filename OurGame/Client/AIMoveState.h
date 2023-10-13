#pragma once
#include "State.h"
class AIMoveState :
    public State
{
public:
	AIMoveState();
	virtual ~AIMoveState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

