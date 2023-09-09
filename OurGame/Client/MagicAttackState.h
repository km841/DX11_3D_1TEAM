

#pragma once
#include "State.h"
class MagicAttackState :
	public State
{
public:
	MagicAttackState();
	virtual ~MagicAttackState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
};