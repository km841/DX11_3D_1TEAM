#include "pch.h"
#include "Teleport_InState_Gm.h"
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
Teleport_InState_Gm::Teleport_InState_Gm()
	:State_Grandma(GrandmaState::Teleport_InState)
{
}

void Teleport_InState_Gm::Initialize()
{
}

void Teleport_InState_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	if (pAni_Gm->GetFrameRatio() > 0.20) {
		pGrandma->StateChange_Grandma(GrandmaState::IdleState);
	}
}

void Teleport_InState_Gm::Enter()
{
	PlayAnimation();
}

void Teleport_InState_Gm::Exit()
{
}

void Teleport_InState_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();

	pAni_Gm->Play(6, false);

}
