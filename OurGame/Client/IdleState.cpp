#include "pch.h"
#include "IdleState.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "TimerObject.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"

IdleState::IdleState()
	: State(PlayerState::IdleState)
	, mIdleStatebool(true)
	, mFallStartbool(false)
{
	mTimerObj[0].SetEndTime(1.3f);
	mTimerObj.push_back(TimerObject());
	mTimerObj[1].SetEndTime(0.2f);
}

void IdleState::Initialize()
{
}

void IdleState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	RigidBody* pRb = pPlayer->GetRigidBody();

	if (pAni->GetFrameRatio() > 0.99f) {
		if (mIdleStatebool == true)
		{
			mIdleStatebool = false;
			PlayAnimation();
			return;
		}
		if (mIdleStatebool == false)
		{
			mIdleStatebool = true;
			PlayAnimayton2();
			return;
		}
	}

	if(IS_PRESS(KeyType::UP) || IS_PRESS(KeyType::DOWN) || 
		IS_PRESS(KeyType::LEFT) || IS_PRESS(KeyType::RIGHT))
	{
		pPlayer->StateChange(PlayerState::MoveState);
	}


	if (IS_DOWN(KeyType::LBUTTON))
	{
		pPlayer->StateChange(PlayerState::AttackState);
	}
	if (IS_DOWN(KeyType::SHIFT_L))
	{
		pPlayer->StateChange(PlayerState::EvasionState);
	}
	if (IS_DOWN(KeyType::SPACE))
	{
		pRb->SetVelocity(AXIS_Y, 25.f);
		mFallStartbool = true;
		mTimerObj[0].Start();
	}
	FallLate(); // 낙하 지연 시작

	if (IS_DOWN(KeyType::G))
	{
		pPlayer->StateChange(PlayerState::ClimingUpState);
	}
	if (IS_DOWN(KeyType::B))
	{
		pPlayer->StateChange(PlayerState::ClimingDownState);
	}
		
	
}

void IdleState::Enter()
{
	PlayAnimation();
}

void IdleState::Exit()
{
	mTimerObj[0].Stop();
}

void IdleState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(42, false);
}

void IdleState::PlayAnimayton2()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(43, false);
}

void IdleState::FallLate()
{
	if (mFallStartbool == false) {
		return;
	}
	if (mFallStartbool == true )
	{
		mTimerObj[0].Update(); // 타이머 업데이트

		if (mTimerObj[0].IsFinished() == true) {
			Player* pPlayer = Player::GetPlayer();
			pPlayer->StateChange(PlayerState::FallState);
			mFallStartbool = false;
			mTimerObj[0].Stop();
		}

	}
}
