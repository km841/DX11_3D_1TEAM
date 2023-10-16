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
#include "ArrowScript.h"

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
	DirectionEvasion eDir = pPlayer->GetDirectioninfo();

	GameObject* pArrowObj = pPlayer->GetArrow(); //화살 오브젝트
	ArrowScript* pArrowSc = pArrowObj->GetScript<ArrowScript>();

	AudioSound* pSound = PLAYER->GetAudioSound();

	Vec3 Dir = ConvertDir(eDir);

	
	if (IS_UP(KeyType::Z))
	{
		if (pAni->GetFrameRatio() > 0.9 && isArrowFireCheck == true)
		{
			isArrowFireCheck = false;
			pSound->SetSound(L"ArrowFire", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Player\\ArrowFire.ogg");
			pSound->Play(70);
		}

		pArrowSc->SetArrowAtkCheck(true); //화살 발사 부분 시작
		pArrowSc->BurnReset(); //불화살 초기화 부분
		pArrowSc->SetDirPos(Dir); // 화살 발사 방향 Set
		pPlayer->StateChange(PlayerState::IdleState);
		pArrowSc->SetmSpeed(); // 화살 발사 방향 Set
		
		pPlayer->DamegeCost();
	}

	if (pAni->GetFrameRatio() > 0.9)
	{
		pArrowObj->Enable();
	}
}

void BowState::Enter()
{
	PlayAnimation();

	AudioSound* pSound = PLAYER->GetAudioSound();
	pSound->SetSound(L"ArrowCharge", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Player\\ArrowCharge.ogg");
	pSound->Play(70);

	Player* pPlayer = Player::GetPlayer();
	GameObject* pBowObj = pPlayer->GetBow(); //활 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pBowObj->Enable();

	GameObject* pArrowObj = pPlayer->GetArrow(); //화살 오브젝트
	pArrowObj->Disable();
	ArrowScript* pArrowSc = pArrowObj->GetScript<ArrowScript>();
	pArrowSc->SetArrowAtkCheck(false); //화살 발사 부분 종료

	GameObject* pSwordObj = pPlayer->GetGreatSword(); //칼 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pSwordObj->Disable();
}

void BowState::Exit()
{
	Player* pPlayer = Player::GetPlayer();

	GameObject* pBowObj = pPlayer->GetBow(); //활 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pBowObj->Disable();

	//GameObject* pObj02 = pPlayer->GetArrow(); //화살 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	//pObj02->Disable();

	GameObject* pSwordObj = pPlayer->GetGreatSword(); //칼 오브젝트 가져와서 텍스쳐 그리기 or 투명화 설정하는 부분
	pSwordObj->Enable();

	isArrowFireCheck = true;

}

void BowState::PlayAnimation()
{
	Player* pPlayer = Player::GetPlayer();
	Animator* pAni = pPlayer->GetAnimator();
	RigidBody* pRb = pPlayer->GetRigidBody();

	pAni->Play(0, false);
}
