#pragma once
#include "State_Grandma.h"
class RangeAttack01State_Gm :
    public State_Grandma
{
public:
	RangeAttack01State_Gm();
	virtual ~RangeAttack01State_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

