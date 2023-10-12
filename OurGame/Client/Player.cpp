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
#include "Ladder.h"
#include "LadderCollider.h"
#include "HeadRoller.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"
#include "FireArrowParticle.h"
#include "SparkParticle.h"
#include "CircleParticle.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "PaperBurnScript.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "SwordScript.h"
#include "PlayerColScript.h"
#include "BowScript.h"
#include "ArrowScript.h"

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
#include "HitStartState.h"
#include "HittingState.h"
#include "HitEndState.h"
#include "FallDownState.h"
#include "DeadState.h"
#include "ClimingDownState.h"
#include "ClimingEndState.h"
#include "ClimingUpState.h"
#include "BowState.h"
#include "Map.h"
#include "FocusingScript.h"

Player* Player::spPlayer;

Player::Player()
	: GameObject(LayerType::Player)
	, mHP(4) // 피통
	, mCost(4) // 마나
	, mSpeed(5.f) // 이동속도
	, mAttackDamage(1.f) // 데미지
	, mAttack_Speed(0.04f) // 공속
	, mbAttackDir(true) //true시 오른쪽공격, false시 왼쪽 공격
	, mDash_Speed(25.f) // 회피시 주는 물리 힘
	, meDirectionEvasion(DirectionEvasion::NONE) // 플레이어 8방향 enum 으로 표시
	
{
	AssertEx(spPlayer == nullptr, L"이미 정적 플레이어 존재함");
	spPlayer = this; //정적변수 선언

	mKeyInfo.SetForwardKey(KeyType::DOWN);
	mKeyInfo.SetLeftKey(KeyType::RIGHT);

	mState[int(PlayerState::PauseState)] = new PauseState;
	mState[int(PlayerState::IdleState)] = new IdleState;
	mState[int(PlayerState::MoveState)] = new MoveState;
	mState[int(PlayerState::AttackState)] = new AttackState;
	mState[int(PlayerState::MagicAttackState)] = new MagicAttackState;
	mState[int(PlayerState::EvasionState)] = new EvasionState;
	mState[int(PlayerState::FallState)] = new FallState;
	mState[int(PlayerState::HitStartState)] = new HitStartState;
	mState[int(PlayerState::HittingState)] = new HittingState;
	mState[int(PlayerState::HitEndState)] = new HitEndState;
	mState[int(PlayerState::FallDownState)] = new FallDownState;
	mState[int(PlayerState::DeadState)] = new DeadState;
	mState[int(PlayerState::ClimingDownState)] = new ClimingDownState;
	mState[int(PlayerState::ClimingEndState)] = new ClimingEndState;
	mState[int(PlayerState::ClimingUpState)] = new ClimingUpState;
	mState[int(PlayerState::BowState)] = new BowState;


	// Sword_Heavy
	{
		mpSlashEffect = Factory::CreateObject<SwordHeavyEffect>(Vec3(0.f, 8.f, 0.f), L"PlayerSlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbx");
		mpSlashEffect->SetDontDestroyObject(L"PlayerSlashEffect");
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
		mpSlashEffect->DrawShadow(false);
		
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(mpSlashEffect);
	}

	//무기 오브젝트
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(1.f, 0.2f, 0.2f);
		
		pGreatSword = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, -5.f, 0.f), physicsInfo, L"Deferred_CullNone", L"..\\Resources\\FBX\\Weapon\\Sword.fbx",false, LayerType::Item);
		pGreatSword->SetDontDestroyObject(L"PlayerGreatSword");
		pGreatSword->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		pGreatSword->GetTransform()->SetRotation(Vec3(330.f, 100.f, 50.f));

		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloom(true,0);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloom(true,1);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloom(true,2);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.f,0);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.f,1);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.f,2);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloomFilter(Vec4(1.f, 0.f, 0.f, 0.f),0);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloomFilter(Vec4(1.f, 0.f, 0.f, 0.f),1);
		pGreatSword->GetMeshRenderer()->GetMaterial()->SetBloomFilter(Vec4(1.f, 0.f, 0.f, 0.f),2);
		pGreatSword->DrawShadow(false);
		auto pFollowSc = pGreatSword->AddComponent(new OwnerFollowScript(this));
		
		
		pSwordSc = pGreatSword->AddComponent(new SwordScript);
		//gpEngine->GetTool()->UseGizmo();
		//gpEngine->GetTool()->SetGameObject(pGreatSword);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pGreatSword);
		//SetMeshTarget(pGreatSword);
	}

	//검 공격범위 콜라이더 - pAttackCol
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Kinematic;
		physicsInfo.eGeometryType = GeometryType::Mesh;
		physicsInfo.size = Vec3(3.f , 3.f, 3.f);

		pAttackCol = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"NoDraw", L"..\\Resources\\FBX\\Player\\Slash_Heavy_Col.fbx", false, LayerType::PlayerCol);
		pAttackCol->SetDontDestroyObject(L"PlayerAttackCollider");
		pAttackCol->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
		pAttackCol->GetTransform()->SetRotation(Vec3(00.f, 00.f, 0.f));
		pAttackCol->AddComponent(new PlayerColScript);
		pAttackCol->Disable();
		pAttackCol->DrawShadow(false);

		auto pFollowSc2 = pAttackCol->AddComponent(new OwnerFollowScript(this));
		pFollowSc2->SetOffset(Vec3(0.f, 0.f, 0.f));
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pAttackCol);
		
	}

	//활 오브젝트 - Bow
	{

		pBow = Factory::CreateObject<GameObject>(Vec3(0.f, 100.f, 0.f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Weapon\\Bow.fbx", false, LayerType::Item);
		pBow->SetDontDestroyObject(L"PlayerBow");
		pBow->GetTransform()->SetScale(Vec3(2.f, 1.5f, 2.f));
		pBow->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

		pBow->GetMeshRenderer()->GetMaterial()->SetBloom(true, 0);
		pBow->GetMeshRenderer()->GetMaterial()->SetBloomPower(2.f, 0);
		pBow->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 0.f, 0.f, 0.f));
		pBow->GetMeshRenderer()->GetMaterial()->SetBloomFilter(Vec4(1.f, 0.f, 0.f, 0.f), 0);

		pBow->Disable();
		//auto pFollowSc = pBow->AddComponent(new OwnerFollowScript(this));

		pBowSc = pBow->AddComponent(new BowScript);
		//gpEngine->GetTool()->UseGizmo();
		//gpEngine->GetTool()->SetGameObject(pBow);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pBow);
		//SetMeshTarget(pBow);
	}

	//화살 오브젝트 - Arrow
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Dynamic;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.05f, 0.05f, 0.7f);

		pArrow = Factory::CreateObjectHasPhysical<GameObject>(Vec3(3.f, 100.f, 0.f), physicsInfo, L"Deferred_CullNone", L"..\\Resources\\FBX\\Weapon\\Arrow.fbx", false, LayerType::ArrowCol);
		pArrow->SetDontDestroyObject(L"PlayerArrow");
		
		pArrow->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 0.8f));
		pArrow->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

		pArrow->GetMeshRenderer()->GetMaterial()->SetBloom(true, 0);
		pArrow->GetMeshRenderer()->GetMaterial()->SetBloomPower(3.f, 0);
		pArrow->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 0.f, 0.f, 0.f));
		pArrow->GetMeshRenderer()->GetMaterial()->SetBloomFilter(Vec4(1.f, 0.f, 0.f, 0.f), 0);

		pArrow->Disable();
		//auto pFollowSc = pBow->AddComponent(new OwnerFollowScript(this));

		pArrowSc = pArrow->AddComponent(new ArrowScript);

		GameObject* pEffect = nullptr;
		{
			pEffect = Factory::CreateObject<GameObject>(Vec3::Zero, L"Forward", L"", false, LayerType::Unknown);
			pEffect->SetDontDestroyObject(L"SparkParticle");
			pEffect->AddComponent(new OwnerFollowScript(this));
			//FireArrowParticle* pParticle = pEffect->AddComponent(new FireArrowParticle);
			//pParticle->SetStartColor(Vec3(1.f, 0.f, 0.f));
			//pParticle->SetEndColor(Vec3(1.f, 1.f, 0.f));

			SparkParticle* pParticle = pEffect->AddComponent(new SparkParticle);
			pParticle->SetAngle(Vec3(-180.f, 0.f, 0.f));
			pParticle->SetParticleRotation(Vec3(0.f, 0.f, 0.f));
			pParticle->SetScatterRadius(5.f);
			pParticle->SetStartColor(Vec3(1.f, 0.f, 0.f));
			pParticle->SetEndColor(Vec3(1.f, 1.f, 0.f));
		}

		GameObject* pArrowLight = nullptr;
		{
			pArrowLight = new GameObject(LayerType::Unknown);
			pArrowLight->SetDontDestroyObject(L"ArrowLight");

			pArrowLight->AddComponent(new Transform);
			pArrowLight->AddComponent(new OwnerFollowScript(this));
			Light* pLight = pArrowLight->AddComponent(new Light);
			pLight->SetLightRange(5.f);
			pLight->SetDiffuse(Vec3(0.5f, 0.2f, 0.f));
			pLight->SetLightType(LightType::PointLight);
		}
		//pArrowSc->SetParticleObject(pEffect);
		//pArrowSc->SetLightObject(pArrowLight);


		pArrow->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
		pArrow->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
		//gpEngine->GetTool()->UseGizmo();
		//gpEngine->GetTool()->SetGameObject(pArrow);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pEffect);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pArrowLight);
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pArrow);
		//SetMeshTarget(pArrow);
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
	
#pragma region 플레이어 애니메이션 이름 변경
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

	//활모션
	GetAnimator()->RenameAnimation(0, L"_Player_Bow");
	GetAnimator()->SetLoop(0, true);
	GetAnimator()->SetHasExitFlag(0, true);




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
	
	pSwordSc->SetPlayerState(mActiveState->GetStateEnum());
	pBowSc->SetPlayerState(mActiveState->GetStateEnum());
	pArrowSc->SetPlayerState(mActiveState->GetStateEnum());
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

void Player::OnCollisionEnter(Collider* _pOtherCollider)
{
	
	
}

void Player::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Player::OnCollisionExit(Collider* _pOtherCollider)
{
}


void Player::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// 임시 코드
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}

	if (LayerType::MonsterCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::Monster_ProjectTile == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		mActiveState->Exit();
		StateChange(PlayerState::HitStartState);
	}

	if (LayerType::Monster == _pOtherCollider->GetGameObject()->GetLayerType()
		&& static_cast<Monster*>(_pOtherCollider->GetGameObject())->GetAttackCheck() == true)
	{
		mActiveState->Exit();
		StateChange(PlayerState::HitStartState);
	}

	if (LayerType::Monster == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (_pOtherCollider->GetGameObject()->GetName() == L"HeadRoller" &&
			static_cast<HeadRoller*>(_pOtherCollider->GetGameObject())->GetisRoll() == true) {
			mActiveState->Exit();
			StateChange(PlayerState::HitStartState);
		}

	}


	if (LayerType::Ladder == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		lastLadderName = _pOtherCollider->GetGameObject()->GetName();
		ToMovePos = static_cast<LadderCollider*>(_pOtherCollider->GetGameObject())->GetPlayerToMovePos(); //사다리 올라갈때 필요한 위치값
		ToDownPos = static_cast<LadderCollider*>(_pOtherCollider->GetGameObject())->GetPlayerToDownPos(); // 사다리 내려갈때 필요한 위치값
		ToRotPos = static_cast<LadderCollider*>(_pOtherCollider->GetGameObject())->GetDir();
		isClimb = true;
		
		int a = 0;
	
	}

	

}

void Player::OnTriggerStay(Collider* _pOtherCollider)
{
	
	if (LayerType::Monster == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (_pOtherCollider->GetGameObject()->GetName() == L"HeadRoller" &&
			static_cast<HeadRoller*>(_pOtherCollider->GetGameObject())->GetisRollStay() == true) {
			mActiveState->Exit();
			StateChange(PlayerState::HitStartState);
			static_cast<HeadRoller*>(_pOtherCollider->GetGameObject())->SetisRollStay(false);
		}

	}

}

void Player::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}

	if (LayerType::Ladder == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		 isClimb = false;
	}

	if (LayerType::MonsterCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		int a = 0;
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
	//AssertEx(spPlayer != nullptr, L"플레이어가 Nullptr 이다 _ GetPlayer()~");
	return spPlayer; 
}
