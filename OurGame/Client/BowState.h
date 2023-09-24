#pragma once
#include "State.h"
class BowState :
	public State
{
public:
	BowState();
	virtual ~BowState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;

};