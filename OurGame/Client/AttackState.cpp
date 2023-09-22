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
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"

/* Event */
#include "SceneChangeEvent.h"

AttackState::AttackState()
	: State(PlayerState::AttackState)
	, mbTrigger(true) 
{
}

void AttackState::Initialize()
{
}

void AttackState::Update()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	RigidBody* pRb = pPlayer->GetRigidBody();
	
	SwordHeavyEffect* pEffect = pPlayer->GetSwordEffect();
	Transform* pEff_Tr = pEffect->GetTransform();

	GameObject* pAttackCol_Obj = pPlayer->GetAttackCol();
	mbTrigger = pPlayer->GetAttackDir();

#pragma region 공격시 앞으로 튕기는 힘
		//가져와서 튕기는 힘 주기
		DirectionEvasion eDir = pPlayer->GetDirectioninfo();
		Vec3 totalDir = ConvertDir(eDir); // 8가지 방향 체크후 주는 힘 방향 설정
		float DashSpeed = 5.f;

		if (pAni->GetFrameRatio() > 0.02f)
			DashSpeed = 0;

		pRb->SetVelocity(totalDir * DashSpeed);
#pragma endregion

	if (pAni->GetFrameRatio() > 0.01f && pAni->GetFrameRatio() < 0.02f) {

		pAttackCol_Obj->Enable();
	}
	if (pAni->GetFrameRatio() > 0.02f ) {

		pAttackCol_Obj->Disable();
	}


	if (pAni->GetFrameRatio() > 0.07f) {
		
		pPlayer->StateChange(PlayerState::IdleState);

	}
	
	////마우스 좌측 버튼 클릭했을때
	if (IS_DOWN(KeyType::LBUTTON) && pAni->GetFrameRatio() > pPlayer->GetAttackSpeed())
	{
		if (mbTrigger == true) //오른쪽 공격
		{
			mbTrigger = false;
			pPlayer->SetAttackDir(mbTrigger);
			PlayAnimation();
			return;
		}
		if (mbTrigger == false) //왼쪽 공격
		{
			mbTrigger = true;
			pPlayer->SetAttackDir(mbTrigger);
			PlayAnimation();
			return;
		}
	}

	//LCTRL 버튼 눌렀을떄
	if (IS_DOWN(KeyType::LCTRL) && pAni->GetFrameRatio() > pPlayer->GetAttackSpeed())
	{
		if (mbTrigger == true) //오른쪽 공격
		{
			mbTrigger = false;
			pPlayer->SetAttackDir(mbTrigger);
			PlayAnimation();
			return;
		}
		if (mbTrigger == false) //왼쪽 공격
		{
			mbTrigger = true;
			pPlayer->SetAttackDir(mbTrigger);
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
	SwordHeavyEffect* pEffect = pPlayer->GetSwordEffect();
	PlayerSlashScript* pSlashSc = pEffect->GetScript<PlayerSlashScript>();

	mbTrigger = pPlayer->GetAttackDir();

	DirSlash(); // 플레이어 방향 회전 함수

	if (!mbTrigger)
	{
		pAni->Play(69, false);

		pSlashSc->ChangeReverse(false);
		pSlashSc->Attack();
	}
	else
	{
		pAni->Play(70, false);
	
		pSlashSc->ChangeReverse(true);
		pSlashSc->Attack();

	}

	
}

void AttackState::DirSlash()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();

	SwordHeavyEffect* pEffect = pPlayer->GetSwordEffect();
	PlayerSlashScript* pSlashSc = pEffect->GetScript<PlayerSlashScript>();
	OwnerFollowScript* pOFSc = pEffect->GetScript<OwnerFollowScript>();

	Transform* pEff_Tr = pEffect->GetTransform();
	DirectionEvasion eDir = pPlayer->GetDirectioninfo();
	{
		Vec3 Pos = ConvertDir(eDir);
		Pos.Normalize();
		pOFSc->SetOffset(Pos* 1.2f);
	}

	if (eDir == DirectionEvasion::FORWARD)
	{
		pEff_Tr->SetRotation(AXIS_Y, 180);
	}
	if (eDir == DirectionEvasion::BACKWARD)
	{
		pEff_Tr->SetRotation(AXIS_Y, 0);
	}
	if (eDir == DirectionEvasion::LEFT)
	{
		pEff_Tr->SetRotation(AXIS_Y, 90);
	}
	if (eDir == DirectionEvasion::RIGHT)
	{
		pEff_Tr->SetRotation(AXIS_Y, 270);
	}
	if (eDir == DirectionEvasion::TOPLEFT)
	{
		pEff_Tr->SetRotation(AXIS_Y, 135);
	}
	if (eDir == DirectionEvasion::TOPRIGHT)
	{
		pEff_Tr->SetRotation(AXIS_Y, 225);
	}
	if (eDir == DirectionEvasion::BOTTOMLEFT)
	{
		pEff_Tr->SetRotation(AXIS_Y, 45);
	}
	if (eDir == DirectionEvasion::BOTTOMRIGHT)
	{
		pEff_Tr->SetRotation(AXIS_Y, 315);
	}
}
