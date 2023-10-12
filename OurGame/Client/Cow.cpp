#include "pch.h"
#include "Cow.h"
#include "AI.h"

#include "ChangeStateCondition.h"
#include "ChangeStateTask.h"

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
#include "RenderManager.h"
#include "Timer.h"

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
#include "Grimace_ProjectTile.h"
#include "LORD_BOSS_ROLL.h"

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
#include "PlayerColScript.h"
#include "BowScript.h"
#include "ArrowScript.h"
#include "MonsterColScript.h"
Cow::Cow()
{
	mMaxHP = 50.f;
	mHP = mMaxHP; // 피통
	mSpeed = 40.f;
	TurnSpeed = 10.f;
	mAttackDamage = 1; // 공격력


	meBasicState = MonsterBasicState::Idle;
}

Cow::~Cow()
{
}

void Cow::SetBehaviorTree()
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
				Transform* pTr = GetTransform();
				Vec3 Rot = pTr->GetRotation();
				if (2 != animIndex)
				{
					pAnimator->Play(2, true);
				}
				return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pIfCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();
				Transform* pTr = GetTransform();
				Vec3 Pos = pTr->GetPosition();
				Pos.x = 0;
				Pos.z = 0;
				
				SlowTurnLive();

				

				if (pAni->GetFrameRatio() > 0.95) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					
					meBasicState = MonsterBasicState::Attack01;

					return BehaviorResult::Success;
				});

			

			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pIfCondition);
			pIdleSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion

#pragma region Attack Sequence
		Sequence* pAttackSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
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
				{
					PrevFollowSet();
					pAnimator->Play(0, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{
					//이부분 중요
					//GetRigidBody()->AddVelocity(AXIS_Y, -0.5f);
					GetRigidBody()->SetVelocityExcludingColliders(-PosDir * 9.5f);
					PrevFollowLive();
					//GetRigidBody()->SetVelocity(PosDir * 6.8f);

					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.95) {
					pAni->Play(0, true);
					GetRigidBody()->SetVelocityExcludingColliders(Vec3::Zero);
					GetTransform()->SetRelativePosition(Vec3(0.f, -1.f, 0.f));
					Count++;
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					if (Count == 10)
					{
						MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
						GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(this));
					}
					return BehaviorResult::Success;
				});


			pAttackSequence->AddChild(pStateChecker);
			pAttackSequence->AddChild(pRunAnimationTask);
			pAttackSequence->AddChild(pTask);
			pAttackSequence->AddChild(pCondition);
			pAttackSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pAttackSequence);

#pragma endregion
	}
	pRootNode->AddChild(pStateSelector);
}

void Cow::Initialize()
{
	Monster::Initialize();

	Animator* pAnimator = GetAnimator();
	pAnimator->SetLoop(0, true);
}

void Cow::Update()
{
	Monster::Update();
}

void Cow::FixedUpdate()
{
	Monster::FixedUpdate();
}

void Cow::FinalUpdate()
{
	Monster::FinalUpdate();
}

void Cow::Render()
{
	Monster::Render();
}

void Cow::Destroy()
{
	Monster::Destroy();
}

void Cow::OnCollisionEnter(Collider* _pOtherCollider)
{
}

void Cow::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Cow::OnCollisionExit(Collider* _pOtherCollider)
{
}

void Cow::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void Cow::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Cow::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void Cow::SlowTurnLive()
{
	//현모님이 봐주심
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Transform* pTr = GetTransform();

	RotDir = playerPos - myPos;
	RotDir.Normalize();
	RotDir.y = 0;

	Vec3 look = pTr->GetRight();
	look.Normalize();

	float check = RotDir.Dot(look);

	// 각도 계산 후 도 단위로 변경
	float angle = (acosf(check) - XM_PIDIV2) * 180.f / XM_PI;

	Vec3 Rot = pTr->GetRotation();

	int Right = TurnSpeed;
	int Left = -TurnSpeed;
	// 0 -> 360                200

	if (fabs(angle) < 3.f)
		return;

	if (check > 0.f)
		pTr->SetRotation(Vec3(-90.f, 0.f, Rot.z + Left * DELTA_TIME));
	else if (check < 0.f)
		pTr->SetRotation(Vec3(-90.f, 0.f, Rot.z + Right * DELTA_TIME));

	TurnSpeed = 250.f;

	
}

void Cow::PrevFollowSet()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	PosDir = playerPos - myPos;
	PosDir.Normalize();
	PosDir.y = 0;
}

void Cow::PrevFollowLive()
{
	Vec3 Ve = PosDir * (mSpeed);
	GetRigidBody()->SetVelocity(AXIS_X, Ve.x); //따라오게 만드는 코드
	GetRigidBody()->SetVelocity(AXIS_Z, Ve.z); //따라오게 만드는 코드
	
}
