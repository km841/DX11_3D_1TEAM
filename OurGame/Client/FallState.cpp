#include "pch.h"
#include "FallState.h"
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
#include "TimerObject.h"

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
FallState::FallState()
	:State(PlayerState::FallState)
{
	mTimerObj[0].SetEndTime(2.f);
	mTimerObj.push_back(TimerObject());
	mTimerObj[1].SetEndTime(2.f);
}

void FallState::Initialize()
{
	
}

void FallState::Update()
{
	//조건 걸어서 다른 스테이트 넘어가게 해주는 구조 만들기
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	RigidBody* pRigid = pPlayer->GetRigidBody();
	bool mbool = pRigid->GetmbAppliedGravity(); // 그래비티 상태 가져오기

	if (pAni->GetFrameRatio() > 0.3f)
		pPlayer->StateChange(PlayerState::IdleState);
	
}

void FallState::Enter()
{
	PlayAnimation();
}

void FallState::Exit()
{
	
}

void FallState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	pAni->Play(7, false);
}
