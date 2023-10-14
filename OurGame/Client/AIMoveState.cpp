#include "pch.h"
#include "AIMoveState.h"
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
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"

/* Event */
#include "SceneChangeEvent.h"

AIMoveState::AIMoveState()
	: State(PlayerState::AIMoveState)
{
}

void AIMoveState::Initialize()
{
	//PLAYER->SetCutScenePos(Vec3(0.f, 0.f, 0.f));
	//PLAYER->StateChange(PlayerState::AIMoveState);
	//PLAYER->StateChange(PlayerState::PauseState);

	//PLAYER->GetGreatSword()->Disable();
	//PLAYER->Disable();
	//
	//PLAYER->Enable();
	//PLAYER->GetGreatSword()->Enable();

}

void AIMoveState::Update()
{

	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	Transform* pTr = pPlayer->GetTransform();
	Vec3 myPos = pTr->GetPosition();
	Vec3 objectPos = pPlayer->GetCutScenePos();
	float mSpeed = pPlayer->GetMoveSpeed();
	
	Vec3 dir = objectPos - myPos;
	dir.Normalize();
	dir.y = 0;

	float distance = (objectPos - myPos).Length(); // 목표좌표와 플레이어의 거리계산

	if (distance < 0.1f) 
	{
		pPlayer->StateChange(PlayerState::IdleState); 
		//컷신 종료할때 여기다가 추가
	}


	{ // 플레이어가 오브젝트로 이동하는 부분
		Vec3 Ve = dir * mSpeed;//이동속도 조절

		pPlayer->GetRigidBody()->SetVelocity(Ve); //그방향으로가는힘
	}



	{ //플레이어가 오브젝트 방향으로 회전하는 부분
		Vec3 Rot = pTr->GetRotation();
		Vec3 rot = Vec3(0, 0, -1);
		double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
		float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

		if (angleDegree < 0.f)
			angleDegree += 360.f;

		pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));
	}



	//MOVE 애니메이션 반복 
	if (pAni->GetFrameRatio() > 0.7f)
		PlayAnimation();

}

void AIMoveState::Enter()
{
	Player* pPlayer = Player::GetPlayer();

	GameObject* pObj = pPlayer->GetGreatSword();
	pObj->Disable();

	Animator* pAni = pPlayer->GetAnimator();
	int MoveToAnim = 67; 
	pAni->Play(MoveToAnim, true);
}

void AIMoveState::Exit()
{
	Player* pPlayer = Player::GetPlayer();

}

void AIMoveState::PlayAnimation()
{
	Animator* pAni = PLAYER->GetAnimator();
	int MoveToAnim = 67;
	pAni->Play(MoveToAnim, true);
}
