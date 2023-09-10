#pragma once
#include "State_Grandma.h"
class Small_IdleState_Gm :
    public State_Grandma
{
public:
	Small_IdleState_Gm();
	virtual ~Small_IdleState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

