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
	
	SwordHeavyEffect* pEffect = pPlayer->GetSwordEffect();
	Transform* pEff_Tr = pEffect->GetTransform();
	DirectionEvasion eDir = pPlayer->GetDirectioninfo();
	//Vec3 Pos = ConvertDir(eDir);
	//float Flo = atan2(Pos.z, Pos.x);

	//pEff_Tr->SetRotation(AXIS_Y, Flo * 180.f / XM_PI);
	//pEff_Tr->SetRotation(Vec3(0.f, Flo * 180.f / XM_PI, 0.f));
	
	if (pAni->GetFrameRatio() > 0.1f) {
		pPlayer->StateChange(PlayerState::IdleState);
	}
	

	if (IS_DOWN(KeyType::LBUTTON) && pAni->GetFrameRatio() > pPlayer->GetAttackSpeed())
	{
	

		if (mbTrigger == true)
		{
			mbTrigger = false;
			PlayAnimation();
			return;
		}
		if (mbTrigger == false)
		{
			mbTrigger = true;
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


	DirSlash();

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
