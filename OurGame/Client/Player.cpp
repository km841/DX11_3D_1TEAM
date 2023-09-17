#include "pch.h"
#include "Player.h"
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
#include "SwordHeavyEffect.h"

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
#include "PaperBurnScript.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "SwordScript.h"

/* Event */
#include "SceneChangeEvent.h"
 /*State 모음*/
#include "State.h"
#include "PauseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "MagicAttackState.h"
#include "EvasionState.h"
#include "FallState.h"
#include "HitState.h"
#include "FallDownState.h"
#include "DeadState.h"
#include "ClimingDownState.h"
#include "ClimingEndState.h"
#include "ClimingUpState.h"

Player* Player::spPlayer;

Player::Player()
	: GameObject(LayerType::Player)
	, mHP(4) // 피통
	, mCost(4) // 마나
	, mSpeed(5.f) // 이동속도
	, mAttack(1.f) // 데미지
	, mAttack_Speed(0.04f) // 공속
	, mDash_Speed(25.f) // 회피시 주는 물리 힘
	, meDirectionEvasion(DirectionEvasion::NONE) // 플레이어 8방향 enum 으로 표시
	
{
	AssertEx(spPlayer == nullptr, L"이미 정적 플레이어 존재함");
	spPlayer = this; //정적변수 선언

	mState[int(PlayerState::PauseState)] = new PauseState;
	mState[int(PlayerState::IdleState)] = new IdleState;
	mState[int(PlayerState::MoveState)] = new MoveState;
	mState[int(PlayerState::AttackState)] = new AttackState;
	mState[int(PlayerState::MagicAttackState)] = new MagicAttackState;
	mState[int(PlayerState::EvasionState)] = new EvasionState;
	mState[int(PlayerState::FallState)] = new FallState;
	mState[int(PlayerState::HitState)] = new HitState;
	mState[int(PlayerState::FallDownState)] = new FallDownState;
	mState[int(PlayerState::DeadState)] = new DeadState;
	mState[int(PlayerState::ClimingDownState)] = new ClimingDownState;
	mState[int(PlayerState::ClimingEndState)] = new ClimingEndState;
	mState[int(PlayerState::ClimingUpState)] = new ClimingUpState;

	// Sword_Heavy
	{
		mpSlashEffect = Factory::CreateObject<SwordHeavyEffect>(Vec3(0.f, 8.f, 0.f), L"PlayerSlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbx");
		mpSlashEffect->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
		mpSlashEffect->AddComponent(new PlayerSlashScript);
		auto pFollowScript = mpSlashEffect->AddComponent(new OwnerFollowScript(this));
		pFollowScript->SetOffset(Vec3(0.f, -0.f, -0.f));

		mpSlashEffect->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::Clamp);

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HeavySlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbm\\sword_slash_texture_1.png");
		shared_ptr<Texture> pTexture2 = GET_SINGLE(Resources)->Load<Texture>(L"HeavySlash2", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbm\\sword_slash_texture_2.png");
		mpSlashEffect->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		mpSlashEffect->GetMeshRenderer()->GetMaterial()->SetTexture(1, pTexture2);
		mpSlashEffect->GetRigidBody()->RemoveGravity();
		
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(mpSlashEffect);
	}

	//검 오브젝트
	//검  -> Sc 
	// Sc ( 검오브젝트 , 플레이어 오브젝트 
	// 방향 가져와서 쓰기

	//무기 오브젝트
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(1.f, 0.2f, 0.2f);
		
		pGreatSword = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, -5.f, 0.f), physicsInfo, L"Forward_CullNone", L"..\\Resources\\FBX\\Weapon\\Sword.fbx",false, LayerType::Item);
		pGreatSword->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		pGreatSword->GetTransform()->SetRotation(Vec3(330.f, 100.f, 50.f));

		auto pFollowSc = pGreatSword->AddComponent(new OwnerFollowScript(this));
		
		
		SwordScript* pSwordSc = pGreatSword->AddComponent(new SwordScript);
		//gpEngine->GetTool()->UseGizmo();
		//gpEngine->GetTool()->SetGameObject(pGreatSword);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pGreatSword);
		//SetMeshTarget(pGreatSword);
	}
}

Player::~Player()
{
	for (size_t i = 0; i < PLAYER_STATE_COUNT; i++)
	{
		SAFE_DELETE(mState[i]);
	}
	
}

void Player::Initialize()
{
	GameObject::Initialize();
	
	StateChange(PlayerState::IdleState);

	//mActiveState->Initialize();
	
#pragma region "플레이어 애니메이션 이름 변경"
/*애니메이션 이름 변경*/
	//아이들
	GetAnimator()->RenameAnimation(42, L"_Player_Idle01"); //이름변경
	GetAnimator()->SetLoop(42, true); //루프
	GetAnimator()->SetHasExitFlag(42, true); // 기존 애니메이션 다끝나고 실행 f ? t
	GetAnimator()->RenameAnimation(43, L"_Player_Idle02");
	GetAnimator()->SetLoop(43, true); 
	GetAnimator()->SetHasExitFlag(43, true); 

	//이동
	GetAnimator()->RenameAnimation(67, L"_Player_Move");
	GetAnimator()->SetLoop(67, true);
	GetAnimator()->SetHasExitFlag(67, true);

	//회피
	GetAnimator()->RenameAnimation(63, L"_Player_Evasion");
	GetAnimator()->SetLoop(63, true);
	GetAnimator()->SetHasExitFlag(63, true);
	
	//공격
	GetAnimator()->RenameAnimation(69, L"_Player_Attack01");
	GetAnimator()->SetLoop(69, true);
	GetAnimator()->SetHasExitFlag(69, true);
	GetAnimator()->RenameAnimation(70, L"_Player_Attack02");
	GetAnimator()->SetLoop(70, true);
	GetAnimator()->SetHasExitFlag(70, true);

	//낙하
	GetAnimator()->RenameAnimation(7, L"_Player_Fallstart");
	GetAnimator()->SetLoop(7, true);
	GetAnimator()->SetHasExitFlag(7, true);
	GetAnimator()->RenameAnimation(8, L"_Player_Fallend");
	GetAnimator()->SetLoop(8, true);
	GetAnimator()->SetHasExitFlag(8, true);

	//사다리
	GetAnimator()->RenameAnimation(20, L"_Player_ClimingUp");
	GetAnimator()->SetLoop(20, true);
	GetAnimator()->SetHasExitFlag(20, true);
	GetAnimator()->RenameAnimation(21, L"_Player_ClimingDown");
	GetAnimator()->SetLoop(21, true);
	GetAnimator()->SetHasExitFlag(21, true);
	GetAnimator()->RenameAnimation(22, L"_Player_ClimingEnd");
	GetAnimator()->SetLoop(22, true);
	GetAnimator()->SetHasExitFlag(22, true);





#pragma endregion















	//GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	/* 애니메이션의 이름은 FBX에 저장되어 있는 것을 그대로 가져오므로 해당 FBX를 사용하는 클래스의 생성자와 같은 특정 부분에서
			 사용하기 편한 이름으로 일괄적으로 바꿔줄 필요가 있음
	pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

	 반복 여부를 설정하는 함수 (Finished 플래그를 사용할 수 없음)
	pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

	 인덱스 번호로도 사용 가능
	pPotHead->GetAnimator()->SetLoop(9, true);

	 HasExit는 현재 애니메이션 실행중에 다른 애니메이션이 실행되었을 때 바로 넘길건지 여부를 결정 (기본적으로 true)
	 이 값이 false면 애니메이션 플레이 도중 다른 애니메이션 Play가 실행되었을 때 기존 애니메이션이 다 끝나고 실행됨
	pPotHead->GetAnimator()->SetHasExitFlag(9, false);*/

	
}

void Player::Update()
{
	GameObject::Update();
	
	mActiveState->Update();
}

void Player::FixedUpdate()
{
	GameObject::FixedUpdate();
	
	
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
	

}

void Player::Render()
{
	GameObject::Render();


}

void Player::Destroy()
{
	GameObject::Destroy();
	

}

void Player::OnTriggerEnter(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}

	if (LayerType::Monster == pOtherCollider->GetGameObject()->GetLayerType())
	{
		
	}
}

void Player::OnTriggerStay(Collider* pOtherCollider)
{
}

void Player::OnTriggerExit(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}

void Player::StateChange(PlayerState _eState)
{
	if (mActiveState != nullptr) {
		mActiveState->Exit();
	}

	mActiveState = mState[int(_eState)];
	mActiveState->Enter();
}

void Player::SetDirectionChange(DirectionEvasion _eState)
{
	meDirectionEvasion = _eState;
}

Player* Player::GetPlayer()
{
	AssertEx(spPlayer != nullptr, L"플레이어가 Nullptr 이다 _ GetPlayer()~");
	return spPlayer; 
}
