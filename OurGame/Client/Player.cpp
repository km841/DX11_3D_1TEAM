#include "pch.h"
#include "Player.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"

 /*State 모음*/
#include "State.h"
#include "PauseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "MagicAttackState.h"
#include "EvasionState.h"
#include "FallState.h"
#include "HitState.h"
#include "FallDownState.h"
#include "DeadState.h"

Player* Player::spPlayer;

Player::Player()
	: GameObject(LayerType::Player)
	, mHP(4)
	, mCost(4)
	, mSpeed(5.f)
	, mAttack(1.f)
	, mAttack_Speed(0.04f)
	, mDash_Speed(25.f)
	, meDirectionEvasion(DirectionEvasion::NONE)
	
{
	AssertEx(spPlayer == nullptr, L"이미 정적 플레이어 존재함");
	spPlayer = this; //정적변수 선언

	mState[int(PlayerState::PauseState)] = new PauseState;
	mState[int(PlayerState::IdleState)] = new IdleState;
	mState[int(PlayerState::MoveState)] = new MoveState;
	mState[int(PlayerState::AttackState)] = new AttackState;
	mState[int(PlayerState::MagicAttackState)] = new MagicAttackState;
	mState[int(PlayerState::EvasionState)] = new EvasionState;
	mState[int(PlayerState::FallState)] = new FallState;
	mState[int(PlayerState::HitState)] = new HitState;
	mState[int(PlayerState::FallDownState)] = new FallDownState;
	mState[int(PlayerState::DeadState)] = new DeadState;

	


	
}

Player::~Player()
{
	for (size_t i = 0; i < PLAYER_STATE_COUNT; i++)
	{
		SAFE_DELETE(mState[i]);
	}
}

void Player::Initialize()
{
	GameObject::Initialize();
	
	StateChange(PlayerState::IdleState);

	//mActiveState->Initialize();
	
#pragma region "플레이어 애니메이션 이름 변경"
/*애니메이션 이름 변경*/
	//아이들
	GetAnimator()->RenameAnimation(42, L"_Player_Idle01"); //이름변경
	GetAnimator()->SetLoop(42, true); //루프
	GetAnimator()->SetHasExitFlag(42, true); // 기존 애니메이션 다끝나고 실행 f ? t
	GetAnimator()->RenameAnimation(43, L"_Player_Idle02");
	GetAnimator()->SetLoop(43, true); 
	GetAnimator()->SetHasExitFlag(43, true); 

	//이동
	GetAnimator()->RenameAnimation(67, L"_Player_Move");
	GetAnimator()->SetLoop(67, true);
	GetAnimator()->SetHasExitFlag(67, true);

	//회피
	GetAnimator()->RenameAnimation(63, L"_Player_Evasion");
	GetAnimator()->SetLoop(63, true);
	GetAnimator()->SetHasExitFlag(63, true);
	
	//공격
	GetAnimator()->RenameAnimation(69, L"_Player_Attack01");
	GetAnimator()->SetLoop(69, true);
	GetAnimator()->SetHasExitFlag(69, true);
	GetAnimator()->RenameAnimation(70, L"_Player_Attack02");
	GetAnimator()->SetLoop(70, true);
	GetAnimator()->SetHasExitFlag(70, true);

	//낙하
	GetAnimator()->RenameAnimation(7, L"_Player_Fallstart");
	GetAnimator()->SetLoop(7, true);
	GetAnimator()->SetHasExitFlag(7, true);
	GetAnimator()->RenameAnimation(8, L"_Player_Fallend");
	GetAnimator()->SetLoop(8, true);
	GetAnimator()->SetHasExitFlag(8, true);

	//사다리
	GetAnimator()->RenameAnimation(20, L"_Player_ClimingUp");
	GetAnimator()->SetLoop(20, true);
	GetAnimator()->SetHasExitFlag(20, true);
	GetAnimator()->RenameAnimation(21, L"_Player_ClimingDown");
	GetAnimator()->SetLoop(21, true);
	GetAnimator()->SetHasExitFlag(21, true);
	GetAnimator()->RenameAnimation(22, L"_Player_ClimingEnd");
	GetAnimator()->SetLoop(22, true);
	GetAnimator()->SetHasExitFlag(22, true);





#pragma endregion















	//GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	/* 애니메이션의 이름은 FBX에 저장되어 있는 것을 그대로 가져오므로 해당 FBX를 사용하는 클래스의 생성자와 같은 특정 부분에서
			 사용하기 편한 이름으로 일괄적으로 바꿔줄 필요가 있음
	pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	 반복 여부를 설정하는 함수 (Finished 플래그를 사용할 수 없음)
	pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

	 인덱스 번호로도 사용 가능
	pPotHead->GetAnimator()->SetLoop(9, true);

	 HasExit는 현재 애니메이션 실행중에 다른 애니메이션이 실행되었을 때 바로 넘길건지 여부를 결정 (기본적으로 true)
	 이 값이 false면 애니메이션 플레이 도중 다른 애니메이션 Play가 실행되었을 때 기존 애니메이션이 다 끝나고 실행됨
	pPotHead->GetAnimator()->SetHasExitFlag(9, false);*/

	
}

void Player::Update()
{
	GameObject::Update();
	mActiveState->Update();
}

void Player::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Player::Render()
{
	GameObject::Render();
}

void Player::Destroy()
{
	GameObject::Destroy();
}

void Player::OnTriggerEnter(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}

	if (LayerType::Monster == pOtherCollider->GetGameObject()->GetLayerType())
	{
		
	}
}

void Player::OnTriggerStay(Collider* pOtherCollider)
{
}

void Player::OnTriggerExit(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}

void Player::StateChange(PlayerState _eState)
{
	if (mActiveState != nullptr) {
		mActiveState->Exit();
	}

	mActiveState = mState[int(_eState)];
	mActiveState->Enter();
}

void Player::SetDirectionChange(DirectionEvasion _eState)
{
	meDirectionEvasion = _eState;
}

Player* Player::GetPlayer()
{
	AssertEx(spPlayer != nullptr, L"플레이어가 Nullptr 이다 _ GetPlayer()~");
	return spPlayer; 
}
