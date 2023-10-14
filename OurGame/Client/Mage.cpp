#include "pch.h"
#include "Mage.h"
#include "Engine.h"
#include "AI.h"
#include "ChangeStateTask.h"
#include "random"
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
#include "Mage_ProjectTile.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "AudioSound.h"
#include "AudioSound.h"
#include "Animator.h"

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
#include "MageColScript.h"

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


Mage::Mage()
{
	mMaxHP = 3.f;
	mHP = mMaxHP; // 피통
	mSpeed = 2.f; //이동속도
	mAttackDamage = 1; // 공격력
	mAttackRange = 10.f;
	mRecogRange = 10.f; //감지거리

	meBasicState = MonsterBasicState::Idle;



}

Mage::~Mage()
{
}

void Mage::SetBehaviorTree()
{
	AI* pAI = AddComponent(new AI);

	// 루트 노드 등록
	Selector* pRootNode = new Selector;
	pAI->SetRootNode(pRootNode);

	Selector* pStateSelector = new Selector;
	{
#pragma region Hit Sequence
		Sequence* pHitSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Hit == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (4 != animIndex)
					pAnimator->Play(4, true);

				return BehaviorResult::Success;
				});

			// Hit 발생시 작동하는 스테이터스
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{

					if (mHP <= 0) {
						isDead = true;
						isGODState = true;

						meBasicState = MonsterBasicState::Dead;
						return BehaviorResult::Failure;
					}

					Animator* pAnimator = GetAnimator();
					if (pAnimator->GetFrameRatio() > 0.1)
						return BehaviorResult::Success;

					return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{

					meBasicState = MonsterBasicState::Teleport_Out;
					return BehaviorResult::Success;
				});

			pHitSequence->AddChild(pStateChecker);
			pHitSequence->AddChild(pRunAnimationTask);
			pHitSequence->AddChild(pAttackTask);
			pHitSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pHitSequence);

#pragma endregion

#pragma region Idle Sequence
		Sequence* pIdleSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Idle == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (0 != animIndex)
					pAnimator->Play(0, true);

				return BehaviorResult::Success;
				});

			// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();


					float distance = (playerPos - myPos).Length();
					if (distance < mRecogRange && pAnimator->GetFrameRatio()>0.95)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Teleport_Out)); //여기 다음으로 넘어가는 State 지정해줘야됨
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion

#pragma region Teleport_out Sequence
		Sequence* pTeleport_outSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Teleport_Out == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (2 != animIndex)
					pAnimator->Play(2, true);

				return BehaviorResult::Success;
				});

			// 다음 상태로 넘어가는 조건 
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();

					float distance = (playerPos - myPos).Length();
					if (pAnimator->GetFrameRatio() > 0.95)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pTeleport_outSequence->AddChild(pStateChecker);
			pTeleport_outSequence->AddChild(pRunAnimationTask);
			pTeleport_outSequence->AddChild(pCheckNearbyPlayer);
			pTeleport_outSequence->AddChild(new ChangeStateTask(MonsterBasicState::Teleport_In)); //여기 다음으로 넘어가는 State 지정해줘야됨
		}
		pStateSelector->AddChild(pTeleport_outSequence);

#pragma endregion

#pragma region Teleport_in Sequence
		Sequence* pTeleport_inSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Teleport_In == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (3 != animIndex) {
					Teleport();
					pAnimator->Play(3, true);
				}

				return BehaviorResult::Success;
				});

			// 다음 상태로 넘어가는 조건 
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAnimator = GetAnimator();
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();

					float distance = (playerPos - myPos).Length();
					if (pAnimator->GetFrameRatio() > 0.78)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pTeleport_inSequence->AddChild(pStateChecker);
			pTeleport_inSequence->AddChild(pRunAnimationTask);
			pTeleport_inSequence->AddChild(pCheckNearbyPlayer);
			pTeleport_inSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack01)); //여기 다음으로 넘어가는 State 지정해줘야됨
		}
		pStateSelector->AddChild(pTeleport_inSequence);

#pragma endregion

#pragma region Attack01 Sequence
		Sequence* pAttackSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Attack01 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (1 != animIndex)
					pAnimator->Play(1, true);

				return BehaviorResult::Success;
				});

			//공격 구슬 생성
			BehaviorTask* pAttack_ProjectTileTask = new BehaviorTask([&]() {
				Animator* pAni = GetAnimator();
				AudioSound* pSound = GetAudioSound();

				/*if (pAni->GetFrameRatio() > 0.2) {
					if (true != isTrigger01) {
						isTrigger01 = true;
						CreateProjectTile();
					}
				}*/

				if (pAni->GetFrameRatio() > 0.6) {
					if (true != isTrigger02) {
						isTrigger02 = true;
						CreateProjectTile();
						pSound->SetSound(L"attack", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Mage\\attack.wav");
						pSound->Play(50);
					}
				}

				/*if (pAni->GetFrameRatio() > 0.6) {
					if (true != isTrigger03) {
						isTrigger03 = true;
						CreateProjectTile();
					}
				}*/



				return BehaviorResult::Success;
				});

			// 플레이어 목표 좌표로 몬스터가 이동+회전 하는 실행(Task)
			BehaviorTask* pAttackMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();
				Vec3 scale = GetRigidBody()->GetGeometrySize();

				Vec3 dir = playerPos - myPos;
				Vec3 Num = scale * dir;
				float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));

				dir.Normalize();
				dir.y = 0;
				// 몬스터의 이동속도가 들어가야 함
				// 방향을 변경해주는 Task도 필요
				Vec3 Ve = dir * mSpeed;

				const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);

				for (int i = 0; i < gameObjects.size(); ++i)
				{
					if (gameObjects[i]->GetCollider())
					{
						for (size_t j = 1; j <= 8; j++)
						{
							if (GetCollider()->Raycast(myPos, ConvertDir(static_cast<DirectionEvasion>(j)), gameObjects[i]->GetCollider(), offset + 0.5f))
							{
								if (static_cast<DirectionEvasion>(j) == DirectionEvasion::FORWARD)
								{
									Ve.z = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::BACKWARD)
								{
									Ve.z = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::LEFT)
								{
									Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::RIGHT)
								{
									Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::TOPLEFT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::TOPRIGHT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::BOTTOMLEFT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}
								else if (static_cast<DirectionEvasion>(j) == DirectionEvasion::BOTTOMRIGHT)
								{
									if (Ve.x > Ve.z)
										Ve.z = 0;
									else
										Ve.x = 0;
								}

							}
						}
					}
				}



				//GetRigidBody()->SetVelocity(Ve); //따라오게 만드는 코드

				Transform* pTr = GetTransform();
				Vec3 rot = Vec3(0, 0, -1);
				double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
				float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

				if (angleDegree < 0.f)
					angleDegree += 360.f;

				//몬스터의 고개를 돌리는 코드
				pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));

				return BehaviorResult::Success;
				});

			// 공격 딜레이
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();


					if (pAni->GetFrameRatio() > 0.95) {
						isTrigger01 = false;
						isTrigger02 = false;
						isTrigger03 = false;
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;

				});

			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Trace;
					return BehaviorResult::Success;
				});*/

			pAttackSequence->AddChild(pStateChecker);
			pAttackSequence->AddChild(pRunAnimationTask);
			pAttackSequence->AddChild(pAttack_ProjectTileTask);
			pAttackSequence->AddChild(pAttackMoveTask);
			pAttackSequence->AddChild(pAttackTask);
			pAttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Teleport_Out));
		}
		pStateSelector->AddChild(pAttackSequence);

#pragma endregion

#pragma region Dead Sequence
		Sequence* pDeadSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Attack인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Dead == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (isDead == true)
				{
					isDead = false;
					GetScript<PaperBurnScript>()->SetPaperBurn();
					pAnimator->Play(4, false);
					GameObject* pObj = GetGameObject();
					pObj->DisableCollider();
				}

				return BehaviorResult::Success;
				});

			// 페이퍼번 실행 조건
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Animator* pAni = GetAnimator();
					int animIndex = pAni->GetCurrentClipIndex();



					if (GetScript<PaperBurnScript>()->IsFinished())
					{
						MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
						GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(this));
					}


					return BehaviorResult::Success;

				});

			pDeadSequence->AddChild(pStateChecker);
			pDeadSequence->AddChild(pRunAnimationTask);
			pDeadSequence->AddChild(pAttackTask);

		}
		pStateSelector->AddChild(pDeadSequence);

#pragma endregion

	}
	pRootNode->AddChild(pStateSelector);
}

void Mage::Initialize()
{
	Monster::Initialize();

	GetAnimator()->RenameAnimation(0, L"Idle");
	GetAnimator()->SetLoop(0, true);
	GetAnimator()->SetHasExitFlag(0, true);

	GetAnimator()->RenameAnimation(1, L"attack");
	GetAnimator()->SetLoop(1, true);
	GetAnimator()->SetHasExitFlag(1, true);

	GetAnimator()->RenameAnimation(2, L"Teleport_out");
	GetAnimator()->SetLoop(2, true);
	GetAnimator()->SetHasExitFlag(2, true);

	GetAnimator()->RenameAnimation(3, L"Teleport_in");
	GetAnimator()->SetLoop(3, true);
	GetAnimator()->SetHasExitFlag(3, true);

	GetAnimator()->RenameAnimation(4, L"Death");
	GetAnimator()->SetLoop(4, true);
	GetAnimator()->SetHasExitFlag(4, true);

	GetAnimator()->RenameAnimation(5, L"attack_three");
	GetAnimator()->SetLoop(5, true);
	GetAnimator()->SetHasExitFlag(5, true);

	GetAnimator()->RenameAnimation(6, L"Turn_repeat");
	GetAnimator()->SetLoop(6, true);
	GetAnimator()->SetHasExitFlag(6, true);


}

void Mage::Update()
{
	Monster::Update();
}

void Mage::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Mage::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Mage::Render()
{
	Monster::Render();
}

void Mage::Destroy()
{
	Monster::Destroy();
}

void Mage::OnCollisionEnter(Collider* _pOtherCollider)
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
}

void Mage::OnCollisionStay(Collider* _pOtherCollider)
{

}

void Mage::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Mage::OnTriggerEnter(Collider* _pOtherCollider)
{
	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();


	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (isGODState == false) {
			TakeDamage(attackDamage);
			HitSound();
			float hp = mHP;
			meBasicState = MonsterBasicState::Hit;
		}
	}

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
}

void Mage::OnTriggerStay(Collider* _pOtherCollider)
{

}

void Mage::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Mage::CreateProjectTile()
{
	PhysicsInfo physicsInfo;
	physicsInfo.eActorType = ActorType::Kinematic;
	physicsInfo.eGeometryType = GeometryType::Box;
	physicsInfo.size = Vec3(0.3f, 3.3f, 0.3f);

	Mage_ProjectTile* pProjectTile = Factory::CreateObjectHasPhysical<Mage_ProjectTile>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred_CullNone", L"..\\Resources\\FBX\\Monster\\_DROP_SOUL50.fbx");
	pProjectTile->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
	pProjectTile->GetTransform()->SetPosition(GetTransform()->GetPosition());
	pProjectTile->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloom(true, 0);
	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloomPower(3.f, 0);
	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(0.f, 1.f, 0.f, 1.f));

	pProjectTile->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
	pProjectTile->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

	pProjectTile->Initialize();

	GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pProjectTile);
}

void Mage::Teleport()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Transform* pTr = GetTransform();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	static std::mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	static std::uniform_int_distribution<int> distribution(-5, 5);          // 생성 범위
	static auto generator = std::bind(distribution, engine);

	int Count = 0;
	while (true)
	{
		float randX = generator() * 1.5;
		float randZ = generator() * 1.5;

		Vec3 randPos = Vec3(playerPos.x + randX, myPos.y, playerPos.z + randZ);

		float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));
		bool bEscape = false;

		Count++;

		for (size_t j = 1; j <= 8; j++)
		{
			if (IsRaysCollide(randPos, ConvertDir(static_cast<DirectionEvasion>(j)), LayerType::Ground, offset + 0.1f))
			{
				bEscape = true;
			}

			if (IsRaysCollide(randPos, ConvertDir(static_cast<DirectionEvasion>(j)), LayerType::WallObject, offset + 0.1f))
			{
				bEscape = true;
			}
		}

		if (false == bEscape) {
			pTr->SetPosition(randPos);
			break;
		}

		if (Count >= 100) {
			pTr->SetPosition(playerPos + Vec3(3.f, 0.f, 3.f));
			break;
		}
	}

}
