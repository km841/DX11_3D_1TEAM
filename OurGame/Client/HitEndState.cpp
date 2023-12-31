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
	if (pAni->GetFrameRatio() > 0.5)
		pPlayer->StateChange(PlayerState::IdleState);
}

void HitEndState::Enter()
{
	PlayAnimation();
}

void HitEndState::Exit()
{
	Player* pPlayer = Player::GetPlayer();
	pPlayer->SetisDownState(false);


	GameObject* pObj = pPlayer->GetGreatSword(); //칼 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj->Enable(); // 칼 투명화 종료
}

void HitEndState::PlayAnimation()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	pAni->Play(39, false);
}
