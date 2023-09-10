#include "pch.h"
#include "SpinningState_Gm.h"
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
SpinningState_Gm::SpinningState_Gm()
	:State_Grandma(GrandmaState::SpinningState)
{
}

void SpinningState_Gm::Initialize()
{
}

void SpinningState_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();
	//pGrandma->StateChange_Grandma(GrandmaState::IdleState);
}

void SpinningState_Gm::Enter()
{
	PlayAnimation();
}

void SpinningState_Gm::Exit()
{
}

void SpinningState_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();
}
