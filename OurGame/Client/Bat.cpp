#include "pch.h"
#include "Bat.h"
#include "AI.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Input.h"
#include "ChangeStateCondition.h"
#include "PaperBurnScript.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "ChangeStateTask.h"
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

/* Manager */
#include "RenderManager.h"

Bat::Bat()
{
	mMaxHP = 3.f;
	mHP = mMaxHP; // 피통
	mSpeed=2.f; //이동속도
	mAttackDamage = 1; // 공격력
	mAttackRange = 3.f; // 공격 감지 거리
	mRecogRange = 8.f; //감지거리

	meBasicState = MonsterBasicState::Idle;
}

Bat::~Bat()
{
}

void Bat::SetBehaviorTree()
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
						meBasicState = MonsterBasicState::Dead;
						return BehaviorResult::Failure;
					}
					
					Animator* pAnimator = GetAnimator();
					if(pAnimator->GetFrameRatio() > 0.3)
						return BehaviorResult::Success;

					return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					SetHitCheck(false);
					meBasicState = MonsterBasicState::Trace;
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
				if (3 != animIndex) {
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, 0.f, 0.f));
					pAnimator->Play(3, true);
				}
				return BehaviorResult::Success;
				});

			// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAnimator = GetAnimator();
					float distance = (playerPos - myPos).Length();
					if (distance < mRecogRange && pAnimator->GetFrameRatio()>0.2)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});

			

			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle_to_Trace));
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion

#pragma region Idle_To_Trace Sequence
		Sequence* pIdle_To_TraceSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle_To_Trace인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Idle_to_Trace == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (4 != animIndex)
					pAnimator->Play(4, false);

				return BehaviorResult::Success;
				});

			//애니메이션 한번 출력후 다음 상태로 넘어가기
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Animator* pAni = GetAnimator();
					
					if (pAni->GetFrameRatio()>0.3)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});

			//// 상태 변경(Task) : 상태 변경
			//BehaviorTask* pChangeState = new BehaviorTask([&]()
			//	{
			//		meBasicState = MonsterBasicState::Trace;
			//		return BehaviorResult::Success;
			//	});

			pIdle_To_TraceSequence->AddChild(pStateChecker);
			pIdle_To_TraceSequence->AddChild(pRunAnimationTask);
			pIdle_To_TraceSequence->AddChild(pCheckNearbyPlayer);
			pIdle_To_TraceSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
		}
		pStateSelector->AddChild(pIdle_To_TraceSequence);

#pragma endregion

#pragma region Trace Sequence
		Sequence* pTraceSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Trace인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Trace == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (2 != animIndex) //L"Move"
				{
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, 0.f, 0.f));
					pAnimator->Play(2, true);
				}

				return BehaviorResult::Success;
				});

			// 플레이어 목표 좌표로 몬스터가 이동+회전 하는 실행(Task)
			BehaviorTask* pTraceMoveTask = new BehaviorTask([&]() {
				Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
				Vec3 myPos = GetTransform()->GetPosition();
				Vec3 myRot = GetTransform()->GetRotation();
				Vec3 scale = GetRigidBody()->GetGeometrySize();

				dir = playerPos - myPos;
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



				GetRigidBody()->SetVelocity(Ve); //따라오게 만드는 코드

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


			// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();	
					float distance = (playerPos - myPos).Length();
					Animator* pAni = GetAnimator();
	

					
					if (distance < mAttackRange && pAni->GetFrameRatio()>0.7f)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});


			// 상태 변경(Task) : 상태 변경
			/*BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					meBasicState = MonsterBasicState::Attack;
					return BehaviorResult::Success;
				});*/

			pTraceSequence->AddChild(pStateChecker);
			pTraceSequence->AddChild(pRunAnimationTask);
			pTraceSequence->AddChild(pTraceMoveTask);
			pTraceSequence->AddChild(pCheckNearbyPlayer);
			pTraceSequence->AddChild(new ChangeStateTask(MonsterBasicState::Attack01));
		}
		pStateSelector->AddChild(pTraceSequence);

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
				if (0 != animIndex)
					pAnimator->Play(0, true);

				return BehaviorResult::Success;
				});

			// 공격 딜레이
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					

					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					Animator* pAni = GetAnimator();

					//이부분 중요
					if(pAni->GetFrameRatio()>0.2)
						GetRigidBody()->SetVelocityExcludingColliders(-dir * 3.f);
					if(pAni->GetFrameRatio()>0.4 && pAni->GetFrameRatio() < 0.6)
						GetRigidBody()->SetVelocity(dir * 4.f);

					const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Ground);
					for (int i = 0; i < gameObjects.size(); ++i)
					{
						if (gameObjects[i]->GetCollider())
						{
							if (GetCollider()->Raycast(myPos, dir, gameObjects[i]->GetCollider(), 0.5f))
							{
								GetRigidBody()->SetVelocity(dir * 0.f);
							}
						}
					}

					if(pAni->GetFrameRatio()>0.8)
						return BehaviorResult::Success;
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
			pAttackSequence->AddChild(pAttackTask);
			pAttackSequence->AddChild(new ChangeStateTask(MonsterBasicState::Trace));
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
				GameObject* pObj = GetGameObject(); //이거 확인도 필요함
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (isDead == true)
				{
					//pObj->GetRigidBody()->SetSimulationShapeFlag(false);
					//pObj->Disable();
					isDead = false;
					GetScript<PaperBurnScript>()->SetPaperBurn();
					pAnimator->Play(4, false);
					//
				}

				//pObj->GetRigidBody()->SetSimulationShapeFlag(false); // 콜라이더 끄기
				//pObj->GetRigidBody()->SetSimulationShapeFlag(true); // 콜라이더 켜기


				return BehaviorResult::Success;
				});

			// 페이퍼번 실행 조건
			BehaviorTask* pAttackTask = new BehaviorTask([&]()
				{
					Animator* pAni= GetAnimator();
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

void Bat::Initialize()
{
	Monster::Initialize();

	GetAnimator()->RenameAnimation(4, L"Hit"); 
	GetAnimator()->SetLoop(4, true); 
	GetAnimator()->SetHasExitFlag(4, true); 

	GetAnimator()->RenameAnimation(2, L"Idle"); 
	GetAnimator()->SetLoop(2, true); 
	GetAnimator()->SetHasExitFlag(2, true); 

	GetAnimator()->RenameAnimation(1, L"Move"); 
	GetAnimator()->SetLoop(1, true); 
	GetAnimator()->SetHasExitFlag(1, true); 

	GetAnimator()->RenameAnimation(0, L"Attack"); //이름변경
	GetAnimator()->SetLoop(0, true); //루프
	GetAnimator()->SetHasExitFlag(0, true); // 기존 애니메이션 다끝나고 실행 f ? t


	
}

void Bat::Update()
{
	Monster::Update();
}

void Bat::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Bat::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Bat::Render()
{
	Monster::Render();
}

void Bat::Destroy()
{
	Monster::Destroy();
}

void Bat::OnCollisionEnter(Collider* _pOtherCollider)
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

void Bat::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Bat::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{

		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Bat::OnTriggerEnter(Collider* _pOtherCollider)
{
	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();
	
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

	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		TakeDamage(attackDamage);
		float hp = mHP;
		meBasicState = MonsterBasicState::Hit;
		SetHitCheck(true);
	}
}

void Bat::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Bat::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{

		// 임시 코드
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}
