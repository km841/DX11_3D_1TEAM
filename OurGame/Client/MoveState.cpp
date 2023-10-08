#include "pch.h"
#include "MoveState.h"
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
#include "State.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"

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

MoveState::MoveState()
	: State(PlayerState::MoveState)
	, mEndTime(0.07f)
{
}

void MoveState::Initialize()
{
}

void MoveState::Update()
{
	//조건 걸어서 다른 스테이트 넘어가게 해주는 구조 만들기
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	Transform* tr = pPlayer->GetTransform();
	RigidBody* rb = pPlayer->GetRigidBody();
	DirectionEvasion Dir = pPlayer->GetDirectioninfo();

#pragma region "이동 방향 힘 결정"
	float mMoveSpeed = pPlayer->GetMoveSpeed();

	if (IS_PRESS(P_UP))
	{
		rb->SetVelocity(AXIS_Z, mMoveSpeed);
		tr->SetRotation(Vec3(0.f, 180.f, 90.f));
		//tr->SetRotation(Vec3(-90.f, 0.f, 180.f));
	}

	if (IS_PRESS(P_DOWN))
	{
		rb->SetVelocity(AXIS_Z, -mMoveSpeed);
		tr->SetRotation(Vec3(0.f, 0.f, 90.f));

	}

	if (IS_PRESS(P_LEFT))
	{
		rb->SetVelocity(AXIS_X, -mMoveSpeed);
		tr->SetRotation(Vec3(0.f, 90.f, 90.f));

	}

	if (IS_PRESS(P_RIGHT))
	{
		rb->SetVelocity(AXIS_X, mMoveSpeed);
		tr->SetRotation(Vec3(0.f, -90.f, 90.f));

	}

	if (IS_DOWN(KeyType::SPACE))
	{
		rb->SetVelocity(AXIS_Y, mMoveSpeed * 5.f);
	}

	if (IS_PRESS(P_UP) && IS_PRESS(P_LEFT))
	{
		mMoveSpeed = mMoveSpeed / 1.5f;
		rb->SetVelocity(Vec3(-mMoveSpeed, 0.f, mMoveSpeed));
		tr->SetRotation(Vec3(0.f, 135.f, 90.f));
	}
	if (IS_PRESS(P_UP) && IS_PRESS(P_RIGHT))
	{
		mMoveSpeed = mMoveSpeed / 1.5f;
		rb->SetVelocity(Vec3(mMoveSpeed, 0.f, mMoveSpeed));
		tr->SetRotation(Vec3(0.f, 225.f, 90.f));
	}
	if (IS_PRESS(P_DOWN) && IS_PRESS(P_LEFT))
	{
		mMoveSpeed = mMoveSpeed / 1.5f;
		rb->SetVelocity(Vec3(-mMoveSpeed, 0.f, -mMoveSpeed));
		tr->SetRotation(Vec3(0.f, 45.f, 90.f));
	}
	if (IS_PRESS(P_DOWN) && IS_PRESS(P_RIGHT))
	{
		mMoveSpeed = mMoveSpeed / 1.5f;
		rb->SetVelocity(Vec3(mMoveSpeed, 0.f, -mMoveSpeed));
		tr->SetRotation(Vec3(0.f, 315.f, 90.f));
	}
#pragma endregion


#pragma region "방향 설정"

	if (IS_PRESS(P_UP))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::FORWARD);
	}

	if (IS_PRESS(P_DOWN))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::BACKWARD);
	}

	if (IS_PRESS(P_RIGHT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::RIGHT);
	}
	
	if (IS_PRESS(P_LEFT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::LEFT);
	}
	
	if (IS_PRESS(P_UP) && IS_PRESS(P_LEFT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::TOPLEFT);
	}

	if (IS_PRESS(P_UP) && IS_PRESS(P_RIGHT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::TOPRIGHT);
	}

	if (IS_PRESS(P_DOWN) && IS_PRESS(P_LEFT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::BOTTOMLEFT);
	}

	if (IS_PRESS(P_DOWN) && IS_PRESS(P_RIGHT))
	{
		pPlayer->SetDirectionChange(DirectionEvasion::BOTTOMRIGHT);
	}

	PlayerMoveScript* pScript = PLAYER->GetScript<PlayerMoveScript>();
	pScript->AutoStepping(1.0f);

#pragma endregion

	/*키 입력시 넘어가는 행동들*/
	if (IS_UP(P_UP) || IS_UP(P_DOWN) ||
		IS_UP(P_LEFT) || IS_UP(P_RIGHT))
	{
		pPlayer->StateChange(PlayerState::IdleState);
	}
	if (IS_DOWN(KeyType::LBUTTON) || IS_DOWN(KeyType::LCTRL))
	{
		pPlayer->StateChange(PlayerState::AttackState);
	}
	if (IS_DOWN(KeyType::RBUTTON))
	{
		pPlayer->StateChange(PlayerState::BowState);
	}
	if (IS_DOWN(KeyType::SHIFT_L))
	{
		pPlayer->StateChange(PlayerState::EvasionState);
	}
	if (IS_DOWN(KeyType::G))
	{
		pPlayer->StateChange(PlayerState::ClimingUpState);
	}
	if (IS_DOWN(KeyType::B))
	{
		pPlayer->StateChange(PlayerState::ClimingDownState);
	}


	//MOVE 애니메이션 반복 
	if(pAni->GetFrameRatio() > 0.7)
		PlayAnimation();
}

void MoveState::Enter()
{
	PlayAnimation();
}

void MoveState::Exit()
{
}

void MoveState::PlayAnimation()
{
	//조건 걸어서 다른 스테이트 넘어가게 해주는 구조 만들기
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();


	pAni->Play(67, true);
}
