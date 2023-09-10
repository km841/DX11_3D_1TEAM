#pragma once
#include "State_Grandma.h"
class SmallTransStartState_Gm :
    public State_Grandma
{
public:
	SmallTransStartState_Gm();
	virtual ~SmallTransStartState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

