#pragma once
#include "State_Grandma.h"
class AngryMotionState_Gm :
    public State_Grandma
{
public:
	AngryMotionState_Gm();
	virtual ~AngryMotionState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

