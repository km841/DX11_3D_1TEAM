

#pragma once
#include "State.h"
class HitStartState :
	public State
{
public:
	HitStartState();
	virtual ~HitStartState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};