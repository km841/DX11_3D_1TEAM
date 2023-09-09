
#pragma once
#include "State_Grandma.h"
class IdleState_Gm :
	public State_Grandma
{
public:
	IdleState_Gm();
	virtual ~IdleState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};