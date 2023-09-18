
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
	TimerObject mTimeTopLeft01;
	TimerObject mTimeTopLeft02;
	TimerObject mTimeTopRight01;
	TimerObject mTimeTopRight02;
	TimerObject mTimeBottomLeft01;
	TimerObject mTimeBottomLeft02;
	TimerObject mTimeBottomRight01;
	TimerObject mTimeBottomRight02;

	float mEndTime;
};