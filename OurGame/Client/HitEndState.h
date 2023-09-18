

#pragma once
#include "State.h"
class HitEndState :
	public State
{
public:
	HitEndState();
	virtual ~HitEndState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};