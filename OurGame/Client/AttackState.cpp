#include "pch.h"
#include "AttackState.h"
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

AttackState::AttackState()
	: State(PlayerState::AttackState)
	, mTrigger(true)
{
}

void AttackState::Initialize()
{
}

void AttackState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	if (pAni->GetFrameRatio() > 0.1f) {
		pPlayer->StateChange(PlayerState::IdleState);
	}


	if (IS_DOWN(KeyType::LBUTTON) && pAni->GetFrameRatio() > 0.03f)
	{
		if (mTrigger == true)
		{
			mTrigger = false;
			PlayAnimation();
			return;
		}
		if (mTrigger == false)
		{
			mTrigger = true;
			PlayAnimation();
			return;
		}
	}

}

void AttackState::Enter()
{
	PlayAnimation();
	
}

void AttackState::Exit()
{
}

void AttackState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	if(!mTrigger)
		pAni->Play(69, false);
	else
		pAni->Play(70, false);

	
}
