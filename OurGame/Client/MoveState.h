
#pragma once
#include "State.h"
class TimerObject;
class MoveState :
	public State
{
public:
	MoveState();
	virtual ~MoveState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
private:

	float mEndTime;
};