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
	:State(PlayerState::MoveState)
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

//#pragma region "방향 설정"
//	if (IS_DOWN(KeyType::UP))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::FORWARD);
//	}
//
//	if (IS_DOWN(KeyType::DOWN))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::BACKWARD);
//	}
//
//	if (IS_DOWN(KeyType::RIGHT))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::RIGHT);
//	}
//
//	if (IS_DOWN(KeyType::LEFT))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::LEFT);
//	}
//
//	if (IS_DOWN(KeyType::UP) && IS_PRESS(KeyType::LEFT))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::TOPLEFT);
//	}
//
//	if (IS_DOWN(KeyType::UP) && IS_PRESS(KeyType::RIGHT))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::TOPRIGHT);
//	}
//
//	if (IS_DOWN(KeyType::DOWN) && IS_PRESS(KeyType::LEFT))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::BOTTOMLEFT);
//	}
//
//	if (IS_DOWN(KeyType::DOWN) && IS_PRESS(KeyType::RIGHT))
//	{
//		pPlayer->DirectionEvasionChange(DirectionEvasion::BOTTOMRIGHT);
//	}

#pragma endregion

	if (IS_UP(KeyType::UP) || IS_UP(KeyType::DOWN) ||
		IS_UP(KeyType::LEFT) || IS_UP(KeyType::RIGHT))
	{
		pPlayer->StateChange(PlayerState::IdleState);
	}
	if (IS_DOWN(KeyType::LBUTTON))
	{
		pPlayer->StateChange(PlayerState::AttackState);
	}
	if (IS_DOWN(KeyType::SHIFT_L))
	{
		pPlayer->StateChange(PlayerState::EvasionState);
	}

	if(pAni->GetFrameRatio() > 0.7)
		PlayAnimation();


	//pPlayer->StateChange(PlayerState::AttackState);
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
