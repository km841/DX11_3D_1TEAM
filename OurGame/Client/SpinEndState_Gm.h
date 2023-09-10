#pragma once
#include "State_Grandma.h"
class SpinEndState_Gm :
    public State_Grandma
{
public:
	SpinEndState_Gm();
	virtual ~SpinEndState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

