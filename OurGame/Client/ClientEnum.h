#pragma once

#define PLAYER Player::GetPlayer()
#define GRANDMA Grandma::GetGrandma()

enum class PlayerState
{
	PauseState,
	IdleState,
	MoveState,
	AttackState,
	MagicAttackState,
	EvasionState,
	FallState,
	HitState,
	FallDownState,
	DeadState,

	End
};

enum
{
	PLAYER_STATE_COUNT = PlayerState::End,
};

enum class GrandmaState
{
	IdleState,
	RangeAttack01State,
	Teleport_InState,
	RangeAttack02State,
	AngryMotionState,
	SpinStartState,
	SpinningState,
	SpinEndState,
	DeathState,
	Teleport_OutState,
	SmallTransStartState,
	SmallTransEndState,
	BigTransStartState,
	SmallAttack01State,
	Small_IdleState,
	BigTransEndState,

	End
};

enum
{
	GRANDMA_STATE_COUNT = GrandmaState::End,
};