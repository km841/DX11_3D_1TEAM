#pragma once
#include "State_Grandma.h"
class BigTransEndState_Gm :
    public State_Grandma
{
public:
	BigTransEndState_Gm();
	virtual ~BigTransEndState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

