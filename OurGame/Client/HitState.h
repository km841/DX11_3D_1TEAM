

#pragma once
#include "State.h"
class HitState :
	public State
{
public:
	HitState();
	virtual ~HitState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};