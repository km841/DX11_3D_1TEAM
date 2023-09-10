#pragma once
#include "State_Grandma.h"
class Teleport_InState_Gm :
    public State_Grandma
{
public:
	Teleport_InState_Gm();
	virtual ~Teleport_InState_Gm() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};

