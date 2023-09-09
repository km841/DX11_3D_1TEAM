#include "pch.h"
#include "PauseState.h"
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
PauseState::PauseState()
	:State(PlayerState::PauseState)
{
}

void PauseState::Initialize()
{
}

void PauseState::Update()
{
	//조건 걸어서 다른 스테이트 넘어가게 해주는 구조 만들기
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();


	//pPlayer->StateChange(PlayerState::AttackState);
}

void PauseState::Enter()
{
	PlayAnimation();
}

void PauseState::Exit()
{
}

void PauseState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	//pAni->Play(4, true);
}
