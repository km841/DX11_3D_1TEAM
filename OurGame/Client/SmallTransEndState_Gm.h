#pragma once
#include "State_Grandma.h"
class SmallTransEndState_Gm :
    public State_Grandma
{
public:
	SmallTransEndState_Gm();
	virtual ~SmallTransEndState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

