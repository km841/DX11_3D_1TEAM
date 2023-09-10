#pragma once
#include "State_Grandma.h"
class DeathState_Gm :
    public State_Grandma
{
public:
	DeathState_Gm();
	virtual ~DeathState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

