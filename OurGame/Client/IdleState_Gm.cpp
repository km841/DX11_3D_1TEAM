#include "pch.h"
#include "IdleState_Gm.h"
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

IdleState_Gm::IdleState_Gm()
	:State_Grandma(GrandmaState::IdleState)
{
	int a = 0;
}

void IdleState_Gm::Initialize()
{
}

void IdleState_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	if (IS_DOWN(KeyType::UP))
	{
		pGrandma->StateChange_Grandma(GrandmaState::SpinStartState);
	}
	if (IS_DOWN(KeyType::RIGHT))
	{
		pGrandma->StateChange_Grandma(GrandmaState::SmallTransStartState);
	}
	if (IS_DOWN(KeyType::DOWN))
	{
		pGrandma->StateChange_Grandma(GrandmaState::RangeAttack01State);
	}
	if (IS_DOWN(KeyType::LEFT))
	{
		pGrandma->StateChange_Grandma(GrandmaState::RangeAttack02State);
	}
}

void IdleState_Gm::Enter()
{
	PlayAnimation();
}

void IdleState_Gm::Exit()
{
}

void IdleState_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	pAni_Gm->Play(0, true);

}
