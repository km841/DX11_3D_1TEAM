#include "pch.h"
#include "BigTransEndState_Gm.h"
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
#include "PaperBurnScript.h"
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"
BigTransEndState_Gm::BigTransEndState_Gm()
	:State_Grandma(GrandmaState::BigTransEndState)
{
}

void BigTransEndState_Gm::Initialize()
{
}

void BigTransEndState_Gm::Update()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();
	//pGrandma->StateChange_Grandma(GrandmaState::IdleState);
}

void BigTransEndState_Gm::Enter()
{
	PlayAnimation();
}

void BigTransEndState_Gm::Exit()
{
}

void BigTransEndState_Gm::PlayAnimation()
{
	Grandma* pGrandma = Grandma::GetGrandma();
	Animator* pAni_Gm = pGrandma->GetAnimator();
	/*pGrandma->AddComponent(new PaperBurnScript);

	shared_ptr<Texture> pNoiseTex = GET_SINGLE(Resources)->Load<Texture>(L"BurnNoise", L"..\\Resources\\Texture\\BurnNoise.png");
	pGrandma->GetMeshRenderer()->GetMaterial()->SetTextureAllSubset(1, pNoiseTex);*/

	pAni_Gm->Play(24, false);

}
