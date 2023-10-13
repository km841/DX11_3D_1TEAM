#pragma once
#include "State.h"
class AttackBigState :
    public State
{
public:
	AttackBigState();
	virtual ~AttackBigState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;


private:
	void DirSlash();

private:
	bool mbTrigger;
};

