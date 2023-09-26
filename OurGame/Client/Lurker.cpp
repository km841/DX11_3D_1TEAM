#include "pch.h"
#include "Lurker.h"
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

Lurker::Lurker()
{
	mHP = 3.f; // 피통
	mSpeed = 2.f; //이동속도
	mAttackDamage = 1; // 공격력
	mAttackRange = 2.5f; // 공격 감지 거리
	mRecogRange = 7.f; //감지거리
}

Lurker::~Lurker()
{
}

void Lurker::SetBehaviorTree()
{
	AI* pAI = AddComponent(new AI);

	// 루트 노드 등록
	Selector* pRootNode = new Selector;
	pAI->SetRootNode(pRootNode);

	Selector* pStateSelector = new Selector;
	{

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
				/*if (3 != animIndex)
					pAnimator->Play(3, true);*/

				return BehaviorResult::Success;
				});

			// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
			BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]()
				{
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();

					float distance = (playerPos - myPos).Length();
					if (distance < mRecogRange)
					{
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});



			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pCheckNearbyPlayer);
			//pIdleSequence->AddChild(new ChangeStateTask(MonsterBasicState::Idle_to_Trace)); //여기 바꿔주는 부분 해줘야됨
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion



	}
	pRootNode->AddChild(pStateSelector);
}

void Lurker::Initialize()
{
	Monster::Initialize();
}

void Lurker::Update()
{
	Monster::Update();
}

void Lurker::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Lurker::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Lurker::Render()
{
	Monster::Render();
}

void Lurker::Destroy()
{
	Monster::Destroy();
}

void Lurker::OnCollisionEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Lurker::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Lurker::OnCollisionExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}




void Lurker::OnTriggerEnter(Collider* _pOtherCollider)
{
	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Lurker::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Lurker::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}
