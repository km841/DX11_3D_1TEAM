#pragma once

#define PLAYER Player::GetPlayer()
#define HPUI yj::HpUi::GetHpUI()
#define MPUI yj::ManaUi::GetMpUI()
#define TEXTBOX yj::TextBox::GetTextBox()
#define DIALOUGEBOX DialogBox::GetDialogBox()
#define GRANDMA Grandma::GetGrandma()

enum class PlayerState
{
	PauseState,
	IdleState,
	MoveState,
	AttackState,
	AttackBigState,
	MagicAttackState,
	EvasionState,
	FallState,
	HitStartState,
	HittingState,
	HitEndState,
	FallDownState,
	DeadState,
	ClimingUpState,
	ClimingDownState,
	ClimingEndState,
	BowState,
	AIMoveState,

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

enum class DirectionEvasion {
	NONE,

	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	TOPLEFT,
	TOPRIGHT,
	BOTTOMLEFT,
	BOTTOMRIGHT,

	END,

};

enum
{
	EVASION_STATE_COUNT = DirectionEvasion::END,
};

enum class MonsterBasicState
{
	Idle, // 기본 상태
	Patrol, //정찰 상태
	Trace, // 추적 상태
	Attack01, // 공격
	Hit, // 맞는거
	Dead, //죽는거


	//idle    //박쥐
	Idle_to_Trace, 
	//trace
	//attack
	//hit
	//dead


	//idle    //마법사
	Teleport_Out,
	Teleport_In,
	//attack
	//hit
	//dead


	Birth,    // 초록거미
	Hop_dojge,
	//idle
	//Trace
	Trace2,
	Trace_to_Attack,
	//attack
	//hit
	//dead


	//Idle    // 콩벌레
	//Idle_to_Trace 
	//Trace_to_Attack
	//Attack
	Stun,
	//hit
	//dead

	//Idle //내루미 중간보스
	//trace
	Trace_BackStep,
	Delay,
	//attack
	Attack02,
	Attack03,
	Defend_Start,
	Defend,
	Defend_Break,
	Dazed,
	//dead

	CutScene,
	//Idle //LOAD_BOSS
	Melee_Chain,
	Silent_Clap,
	Snap_Once,
	Mega_Aoe,
	Backswing_Left,
	Backswing_Right,
	Roll_Start,
	Roll_01,
	Roll_02,
	Roll_03,
	Roll_End,
	Laser_Start,
	Laser,
	Laser_End,
	Fall_Loop,
	Land_Slam,

	
};

enum class MonsterType
{
	Grimace,
	Bat,
	HeadRoller,
	Lurker,
	Mage,
	End,
};