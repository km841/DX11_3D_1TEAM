#include "pch.h"
#include "ClimingUpState.h"
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
ClimingUpState::ClimingUpState()
	:State(PlayerState::ClimingUpState)
	, mCount_Ani(0)
{
}

void ClimingUpState::Initialize()
{
}

void ClimingUpState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	Transform* pTr = pPlayer->GetTransform();
	RigidBody* pRb = pPlayer->GetRigidBody();

	
	pRb->SetVelocity(AXIS_Y, 2.f);


	if (mCount_Ani > 4) {
		mCount_Ani = 0;
		pPlayer->StateChange(PlayerState::ClimingEndState);
	}

	if (pAni->GetFrameRatio() > 0.3) {
		PlayAnimation();
		mCount_Ani++;
	}


}

void ClimingUpState::Enter()
{
	PlayAnimation();
}

void ClimingUpState::Exit()
{
}

void ClimingUpState::PlayAnimation()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(20, false);
}
