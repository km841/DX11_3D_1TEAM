#pragma once
#include "State.h"
class AttackState :
	public State
{
public:
	AttackState();
	virtual ~AttackState() = default;

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void Enter()  override;
	virtual void Exit()  override;
	virtual void PlayAnimation() override;
private:
	void DirSlash();

	void ForwardSlash();
	void BackwardSlash();
	void LeftSlash();
	void RightSlash();
	void TopLeftSlash();
	void TopRightSlash();
	void BottomLeftSlash();
	void BottomRightSlash();
	
private:
	bool mbTrigger;
	
};