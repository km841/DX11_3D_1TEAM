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
	:State(PlayerState::IdleState)
{

}

void IdleState::Initialize()
{
}

void IdleState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	if (IS_DOWN(KeyType::LBUTTON))
	{
		pPlayer->StateChange(PlayerState::AttackState);
	}
		
	
}

void IdleState::Enter()
{
	PlayAnimation();
}

void IdleState::Exit()
{
}

void IdleState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(1, true);
}
