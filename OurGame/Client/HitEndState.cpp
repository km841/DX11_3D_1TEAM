#include "pch.h"
#include "HitEndState.h"
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
HitEndState::HitEndState()
	:State(PlayerState::HitEndState)
{
}

void HitEndState::Initialize()
{
}

void HitEndState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	if (pAni->GetFrameRatio() > 0.6)
		pPlayer->StateChange(PlayerState::IdleState);
}

void HitEndState::Enter()
{
	PlayAnimation();
}

void HitEndState::Exit()
{
	Player* pPlayer = Player::GetPlayer();

	GameObject* pObj = pPlayer->GetGreatSword();
	pObj->Enable();
}

void HitEndState::PlayAnimation()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	pAni->Play(39, false);
}
