#pragma once
#include "State_Grandma.h"
class SpinStartState_Gm :
    public State_Grandma
{
public:
	SpinStartState_Gm();
	virtual ~SpinStartState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

