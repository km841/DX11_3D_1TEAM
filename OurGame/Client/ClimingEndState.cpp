#include "pch.h"
#include "ClimingEndState.h"
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
#include "Grandma.h"

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
ClimingEndState::ClimingEndState()
	:State(PlayerState::ClimingEndState)
{
}

void ClimingEndState::Initialize()
{
}

void ClimingEndState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();



	if (pAni->GetFrameRatio() > 0.25)
	{
		pPlayer->StateChange(PlayerState::IdleState);
	}
}

void ClimingEndState::Enter()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	Transform* pTr = pPlayer->GetTransform();
	RigidBody* pRb = pPlayer->GetRigidBody();

	pTr->SetPosition(pPlayer->GetToMovePos());

	PlayAnimation();
}

void ClimingEndState::Exit()
{
	Player* pPlayer = Player::GetPlayer();
	pPlayer->SetDirectionChange(pPlayer->GetToRotPos());
}

void ClimingEndState::PlayAnimation()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(22, false);
}
