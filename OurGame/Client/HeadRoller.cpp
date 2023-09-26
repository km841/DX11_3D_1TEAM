#include "pch.h"
#include "HeadRoller.h"
#include "AI.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Input.h"
#include "ChangeStateCondition.h"

#define IDLE_ANIM_INDEX 0
#define TRACE_ANIM_INDEX 3

namespace hm
{
	HeadRoller::HeadRoller()
	{
		mHP = 3.f; // 피통
		mSpeed = 2.f; //이동속도
		mAttackDamage = 1; // 공격력
		mAttackRange = 2.5f; // 공격 감지 거리
		mRecogRange = 7.f; //감지거리
	}

	HeadRoller::~HeadRoller()
	{
	}

	void HeadRoller::SetBehaviorTree()
	{
		/*
		* 비헤이비어 트리를 사용하는 몬스터는 모두 SetBehaviorTree 함수를 오버라이드해서 구현해야 함
		* 이 함수는 Monster 클래스의 Initialize에서 자동으로 호출됨
		* 이 함수에서 하는 일 : AI 컴포넌트 생성, 비헤이비어 노드 생성
		* 내가 짠 예시 코드에서는 람다 함수를 받을 수 있게끔 해서 간소화했으나 
		* 실제로는 노드를 여러 몬스터가 돌려쓰기 위해 클래스화해서 추가하는게 더 좋음
		* ex) RunAnimationTask의 경우 BehaviorTask를 상속받은 RunBehaviorTask 클래스를 구현한 후 생성자의 인자로 애니메이션의 인덱스나 이름을 받게끔 하여 구현
		*/
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
				BehaviorCondition* pStateChecker= new BehaviorCondition([&]()
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
					if (IDLE_ANIM_INDEX != animIndex)
						pAnimator->Play(IDLE_ANIM_INDEX, true);

					return BehaviorResult::Success;
					});

				// 플레이어 거리 확인(Condition) : 플레이어가 근처에 있는지 확인
				BehaviorCondition* pCheckNearbyPlayer = new BehaviorCondition([&]() 
					{
						Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
						Vec3 myPos = GetTransform()->GetPosition();

						float distance = (playerPos - myPos).Length();
						if (distance < 10.f)
						{
							return BehaviorResult::Success;
						}
						return BehaviorResult::Failure;
					});

				// 상태 변경(Task) : 상태 변경
				BehaviorTask* pChangeState = new BehaviorTask([&]()
					{
						meBasicState = MonsterBasicState::Trace;
						return BehaviorResult::Success;
					});

				pIdleSequence->AddChild(new ChangeStateCondition(MonsterBasicState::Idle));
				pIdleSequence->AddChild(pRunAnimationTask);
				pIdleSequence->AddChild(pCheckNearbyPlayer);
				pIdleSequence->AddChild(pChangeState);
			}
			pStateSelector->AddChild(pIdleSequence);

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
					if (TRACE_ANIM_INDEX != animIndex)
						pAnimator->Play(TRACE_ANIM_INDEX, true);

					return BehaviorResult::Success;
					});

				// 추적 실행(Task) : 플레이어의 방향을 확인하여 추적
				BehaviorTask* pTraceTask = new BehaviorTask([&]() {
					Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
					Vec3 myPos = GetTransform()->GetPosition();
					
					Vec3 dir = playerPos - myPos;
					dir.Normalize();

					// 몬스터의 이동속도가 들어가야 함
					// 방향을 변경해주는 Task도 필요
					GetRigidBody()->SetVelocity(dir * 1.f);

					return BehaviorResult::Success;
					});

				pTraceSequence->AddChild(new ChangeStateCondition(MonsterBasicState::Trace));
				pTraceSequence->AddChild(pRunAnimationTask);
				pTraceSequence->AddChild(pTraceTask);
			}
			pStateSelector->AddChild(pTraceSequence);
#pragma endregion
		}
		pRootNode->AddChild(pStateSelector);
	}

	void HeadRoller::Initialize()
	{
		Monster::Initialize();
	}

	void HeadRoller::Update()
	{
		Monster::Update();
	}

	void HeadRoller::FixedUpdate()
	{
		Monster::FixedUpdate();
	}

	void HeadRoller::FinalUpdate()
	{
		Monster::FinalUpdate();
	}

	void HeadRoller::Render()
	{
		Monster::Render();
	}

	void HeadRoller::Destroy()
	{
		Monster::Destroy();
	}
	void HeadRoller::OnCollisionEnter(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}
	}
	void HeadRoller::OnCollisionStay(Collider* _pOtherCollider)
	{
	}
	void HeadRoller::OnCollisionExit(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			GetRigidBody()->ApplyGravity();
		}
	}
	void HeadRoller::OnTriggerEnter(Collider* _pOtherCollider)
	{
		Player* pPlayer = PLAYER;
		float attackDamage = pPlayer->GetAttackDamage();
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}
	}
	void HeadRoller::OnTriggerStay(Collider* _pOtherCollider)
	{
	}
	void HeadRoller::OnTriggerExit(Collider* _pOtherCollider)
	{
		if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
		{
			GetRigidBody()->ApplyGravity();
		}
	}
}

