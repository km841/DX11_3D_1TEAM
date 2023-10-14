#include "pch.h"
#include "HitStartState.h"
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
HitStartState::HitStartState()
	:State(PlayerState::HitStartState)
{
}

void HitStartState::Initialize()
{
}

void HitStartState::Update()
{
	//조건 걸어서 다른 스테이트 넘어가게 해주는 구조 만들기
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	if (pAni->GetFrameRatio() > 0.6)
	{
		pPlayer->StateChange(PlayerState::HitEndState);
	}
	//pPlayer->StateChange(PlayerState::AttackState);
}

void HitStartState::Enter()
{
	PlayAnimation();
	Player* pPlayer = Player::GetPlayer();
	pPlayer->GetDamage();
	pPlayer->SetisDownState(true);
	pPlayer->SetAttackDamage(1.f);
	GameObject* pObj = pPlayer->GetGreatSword(); //칼 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pObj->Disable(); // 칼 오브젝트 안그리기

	GameObject* pArrowObj = pPlayer->GetArrow(); //화살 오브젝트
	pArrowObj->Disable(); //화살 안그리기
	
}

void HitStartState::Exit()
{
}

void HitStartState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(37, false);
}
