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
	if (pAni->GetFrameRatio() > 0.03f ) {

		pAttackCol_Obj->Disable();
	}

	

	if (pAni->GetFrameRatio() > 0.1f) {
		pPlayer->SetBigAttackCountReset();
		pPlayer->StateChange(PlayerState::IdleState);
	}
	
	////마우스 좌측 버튼 클릭했을때
	if (IS_DOWN(KeyType::LBUTTON) && pAni->GetFrameRatio() > pPlayer->GetAttackSpeed() && isKeydown == true)
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
	if (IS_DOWN(KeyType::LCTRL) && pAni->GetFrameRatio() > pPlayer->GetAttackSpeed() && isKeydown == true)
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
	GameObject* pAttackCol_Obj = PLAYER->GetAttackCol();
	pAttackCol_Obj->Disable();

	Player* pPlayer = Player::GetPlayer();
	SwordHeavyEffect* pEffect = pPlayer->GetSwordEffect();
	pEffect->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f)); //이펙트 크기 초기화
	isKeydown = true; //연속 공격 작동하게 만들기
	pPlayer->SetAttackDamage(1.f); //어택 데미지 다시 1로 만들기
}

void AttackState::PlayAnimation()
{
	//애니메이션 출력
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	SwordHeavyEffect* pEffect = pPlayer->GetSwordEffect();
	PlayerSlashScript* pSlashSc = pEffect->GetScript<PlayerSlashScript>();
	int BigCount = pPlayer->GetBigAttackCount();

	mbTrigger = pPlayer->GetAttackDir();
	DirSlash(); // 플레이어 방향 회전 함수
	pPlayer->SetBigAttackCount();
	if (BigCount >= 2) //큰 검기 나가는 조건
	{
		pEffect->GetTransform()->SetScale(Vec3(5.f, 3.f, 5.f));
		pPlayer->SetBigAttackCountReset();
		pPlayer->SetAttackDamage(2.f);
		isKeydown = false;
	}

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
