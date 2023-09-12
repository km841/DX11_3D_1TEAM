#pragma once
#include "State_Grandma.h"
class SmallAttack01State_Gm :
    public State_Grandma
{
public:
	SmallAttack01State_Gm();
	virtual ~SmallAttack01State_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
private:
	int mCount_Ani;
};

