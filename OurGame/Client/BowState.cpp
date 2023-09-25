#include "pch.h"
#include "BowState.h"
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


BowState::BowState()
	: State(PlayerState::BowState)
{
}

void BowState::Initialize()
{
}

void BowState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	RigidBody* pRb = pPlayer->GetRigidBody();

	if (IS_UP(KeyType::RBUTTON))
	{
		pPlayer->StateChange(PlayerState::IdleState);
	}
}

void BowState::Enter()
{
	PlayAnimation();

	Player* pPlayer = Player::GetPlayer();
	GameObject* pObj01 = pPlayer->GetBow(); //활 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj01->Enable();

	GameObject* pObj02 = pPlayer->GetArrow(); //화살 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj02->Enable();

	GameObject* pObj03 = pPlayer->GetGreatSword(); //칼 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj03->Disable();
}

void BowState::Exit()
{
	Player* pPlayer = Player::GetPlayer();

	GameObject* pObj01 = pPlayer->GetBow(); //활 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj01->Disable();

	GameObject* pObj02 = pPlayer->GetArrow(); //화살 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj02->Disable();

	GameObject* pObj03 = pPlayer->GetGreatSword(); //칼 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj03->Enable();
}

void BowState::PlayAnimation()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	RigidBody* pRb = pPlayer->GetRigidBody();

	pAni->Play(0, false);
}
