#include "pch.h"
#include "LORD_BOSS.h"
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
#include "Cow.h"

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

LORD_BOSS::LORD_BOSS()
{
	mMaxHP = 50.f;
	mHP = mMaxHP; // 피통
	mSpeed = 8.f;
	TurnSpeed = 2.f;
	mMagnScale = 2.f;
	Health = (mHP / mMaxHP) * 100;
	
	mAttackDamage = 1; // 공격력
	

	meBasicState = MonsterBasicState::Idle;
}

LORD_BOSS::~LORD_BOSS()
{
}

void LORD_BOSS::SetBehaviorTree()
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
				if (0 != animIndex) 
				{
					pAnimator->Play(0, true);

					if(PrevState == MonsterBasicState::Backswing_Left //백스윙후 Rot값 회전
						|| PrevState == MonsterBasicState::Backswing_Right)
						pTr->SetRotation(Vec3(-90.f, Rot.y, Rot.z + 180));
				}
				return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pIfCondition = new BehaviorCondition([&](){
					Animator* pAni = GetAnimator();


					if (pAni->GetFrameRatio() > 0.98) {
						return BehaviorResult::Success;
					}
					return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;

					static std::mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
					static std::uniform_int_distribution<int> distribution(0, 7);          // 생성 범위
					static auto generator = std::bind(distribution, engine);

					switch (generator())
					{
					case 0:
						meBasicState = MonsterBasicState::Melee_Chain;
						break;
					case 1:
						meBasicState = MonsterBasicState::Silent_Clap;
						break;
					case 2:
						meBasicState = MonsterBasicState::Snap_Once;
						break;
					case 3:
						meBasicState = MonsterBasicState::Mega_Aoe;
						break;
					case 4:
						meBasicState = MonsterBasicState::Backswing_Left;
						break;
					case 5:
						meBasicState = MonsterBasicState::Backswing_Right;
						break;
					case 6:
						meBasicState = MonsterBasicState::Roll_Start;
						break;
					case 7:
						meBasicState = MonsterBasicState::Laser_Start;
						break;
					default:
						return BehaviorResult::Failure;
						break;
					}
					return BehaviorResult::Success;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeTest = new BehaviorTask([&]()
				{
					//meBasicState = MonsterBasicState::Laser_Start;
					return BehaviorResult::Success;
				});


			pIdleSequence->AddChild(pStateChecker);
			pIdleSequence->AddChild(pRunAnimationTask);
			pIdleSequence->AddChild(pIfCondition);
			pIdleSequence->AddChild(pChangeState);
			pIdleSequence->AddChild(pChangeTest);
		}
		pStateSelector->AddChild(pIdleSequence);

#pragma endregion


#pragma region Attack Melee_Chain Sequence
		Sequence* pMelee_ChainSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Melee_Chain == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (1 != animIndex)
				{
					pAnimator->Play(1, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{
					Animator* pAni = GetAnimator();
					
					if (pAni->GetFrameRatio() > 0.1
						&& pAni->GetFrameRatio() < 0.2)
					{
						TurnSpeed = 4;
						SlowTurnLive();
						mMagnScale = 5;
						PrevFollowLive();
					}


					else if (pAni->GetFrameRatio() > 0.2
						&& pAni->GetFrameRatio() < 0.25
						&& isCrash == true)
					{
						isCrash = false;
						GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.03f, 0.02f);
					}


					else if (pAni->GetFrameRatio() > 0.35
						&& pAni->GetFrameRatio() < 0.45)
					{
						TurnSpeed = 4;
						SlowTurnLive();
						mMagnScale = 5;
						PrevFollowLive();
					}


					else if (pAni->GetFrameRatio() > 0.45
						&& pAni->GetFrameRatio() < 0.50
						&& isCrash == true)
					{
						isCrash = false;
						GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.03f, 0.02f);
					}

					else if (pAni->GetFrameRatio() >= 0.65
						&& pAni->GetFrameRatio() < 0.8)
					{
						TurnSpeed = 4;
						SlowTurnLive();
						mMagnScale = 20;
						PrevFollowLive();
					}


					else if (pAni->GetFrameRatio() > 0.8
						&& pAni->GetFrameRatio() < 0.85
						&& isCrash == true)
					{
						isCrash = false;
						GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.03f, 0.02f);
					}
					else
					{
						PrevFollowSet();
						isCrash = true;
					}

					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.99) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pMelee_ChainSequence->AddChild(pStateChecker);
			pMelee_ChainSequence->AddChild(pRunAnimationTask);
			pMelee_ChainSequence->AddChild(pTask);
			pMelee_ChainSequence->AddChild(pCondition);
			pMelee_ChainSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pMelee_ChainSequence);

#pragma endregion

#pragma region Attack Silent_Clap Sequence
		Sequence* pSilent_ClapSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Silent_Clap == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (9 != animIndex)
				{
					pAnimator->Play(9, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{



					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.5) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pSilent_ClapSequence->AddChild(pStateChecker);
			pSilent_ClapSequence->AddChild(pRunAnimationTask);
			pSilent_ClapSequence->AddChild(pTask);
			pSilent_ClapSequence->AddChild(pCondition);
			pSilent_ClapSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pSilent_ClapSequence);

#pragma endregion

#pragma region Attack Snap_Once Sequence
		Sequence* pSnap_OnceSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Snap_Once == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (10 != animIndex)
				{
					pAnimator->Play(10, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{



					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.5) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pSnap_OnceSequence->AddChild(pStateChecker);
			pSnap_OnceSequence->AddChild(pRunAnimationTask);
			pSnap_OnceSequence->AddChild(pTask);
			pSnap_OnceSequence->AddChild(pCondition);
			pSnap_OnceSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pSnap_OnceSequence);

#pragma endregion

#pragma region Attack Mega_Aoe Sequence
		Sequence* pMega_AoeSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Mega_Aoe == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (13 != animIndex)
				{
					pAnimator->Play(13, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{



					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.8) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pMega_AoeSequence->AddChild(pStateChecker);
			pMega_AoeSequence->AddChild(pRunAnimationTask);
			pMega_AoeSequence->AddChild(pTask);
			pMega_AoeSequence->AddChild(pCondition);
			pMega_AoeSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pMega_AoeSequence);

#pragma endregion

#pragma region Attack Backswing_Left Sequence
		Sequence* pBackswing_LeftSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Backswing_Left == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (18 != animIndex)
				{
					pAnimator->Play(18, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{



					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.4) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pBackswing_LeftSequence->AddChild(pStateChecker);
			pBackswing_LeftSequence->AddChild(pRunAnimationTask);
			pBackswing_LeftSequence->AddChild(pTask);
			pBackswing_LeftSequence->AddChild(pCondition);
			pBackswing_LeftSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pBackswing_LeftSequence);

#pragma endregion

#pragma region Attack Backswing_Right Sequence
		Sequence* pBackswing_RightSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Backswing_Right == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (19 != animIndex)
				{
					pAnimator->Play(19, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{



					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();
				

				if (pAni->GetFrameRatio() > 0.4) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pBackswing_RightSequence->AddChild(pStateChecker);
			pBackswing_RightSequence->AddChild(pRunAnimationTask);
			pBackswing_RightSequence->AddChild(pTask);
			pBackswing_RightSequence->AddChild(pCondition);
			pBackswing_RightSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pBackswing_RightSequence);

#pragma endregion

#pragma region Attack Roll_Start Sequence
		Sequence* pRoll_StartSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Roll_Start == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (2 != animIndex)
				{
					pAnimator->Play(2, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{


					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.25) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Roll_01;
					return BehaviorResult::Success;
				});


			pRoll_StartSequence->AddChild(pStateChecker);
			pRoll_StartSequence->AddChild(pRunAnimationTask);
			pRoll_StartSequence->AddChild(pTask);
			pRoll_StartSequence->AddChild(pCondition);
			pRoll_StartSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pRoll_StartSequence);

#pragma endregion

#pragma region Attack Roll_01 Sequence
		Sequence* pRoll_01Sequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Roll_01 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = pObject->GetAnimator();
			
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (0 != animIndex)
				{
					Disable();
					pObject->Enable();
					pAnimator->Play(0, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{
					TurnSpeed = 3;
					SlowTurnLive();
					
					Transform* pObjTr = pObject->GetTransform();
					Transform* pTr = GetTransform();
					pObjTr->SetPosition(pTr->GetPosition());
					pObjTr->SetRotation(pTr->GetRotation());

					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = pObject->GetAnimator();

				if (pAni->GetFrameRatio() > 0.98) {
					PrevFollowSet();
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Roll_02;
					return BehaviorResult::Success;
				});


			pRoll_01Sequence->AddChild(pStateChecker);
			pRoll_01Sequence->AddChild(pRunAnimationTask);
			pRoll_01Sequence->AddChild(pTask);
			pRoll_01Sequence->AddChild(pCondition);
			pRoll_01Sequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pRoll_01Sequence);

#pragma endregion

#pragma region Attack Roll_02 Sequence
		Sequence* pRoll_02Sequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Roll_02 == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = pObject->GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (1 != animIndex)
				{
					pAnimator->Play(1, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{
					Transform* pObjTr = pObject->GetTransform();
					Transform* pTr = GetTransform();
					pObjTr->SetPosition(pTr->GetPosition());
					pObjTr->SetRotation(pTr->GetRotation());


					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = pObject->GetAnimator();
				if(pAni->GetFrameRatio() > 0.4)
					pAni->Play(1, true);

				if (isWall == false) {
					mMagnScale = 3.f;
					PrevFollowLive();
				}
				else if (isWall == true)
				{
					Vec3 Ve = PosDir * 3;
					GetRigidBody()->SetVelocity(AXIS_X, -Ve.x);
					GetRigidBody()->SetVelocity(AXIS_Z, -Ve.z);
					if (GetRigidBody()->GetVelocity().y < 0)
					{
						GetRigidBody()->AddVelocity(AXIS_Y, -0.5f);
					}
				}
					

				if (isGround) {
					isGround = false;
					isWall = false;
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Land_Slam;
					return BehaviorResult::Success;
				});


			pRoll_02Sequence->AddChild(pStateChecker);
			pRoll_02Sequence->AddChild(pRunAnimationTask);
			pRoll_02Sequence->AddChild(pTask);
			pRoll_02Sequence->AddChild(pCondition);
			pRoll_02Sequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pRoll_02Sequence);

#pragma endregion

//#pragma region Attack Roll_03 Sequence
//		Sequence* pRoll_03Sequence = new Sequence;
//		{
//			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
//			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
//				{
//					if (MonsterBasicState::Roll_03 == meBasicState)
//						return BehaviorResult::Success;
//					else
//						return BehaviorResult::Failure;
//				});
//
//			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
//			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
//				Animator* pAnimator = pObject->GetAnimator();
//				int animIndex = pAnimator->GetCurrentClipIndex();
//				if (2 != animIndex)
//				{
//					pAnimator->Play(2, true);
//				}
//				return BehaviorResult::Success;
//				});
//
//			// 이동+Col 처리 하는곳
//			BehaviorTask* pTask = new BehaviorTask([&]()
//				{
//					Transform* pObjTr = pObject->GetTransform();
//					Transform* pTr = GetTransform();
//					pObjTr->SetPosition(pTr->GetPosition());
//
//
//					return BehaviorResult::Success;
//				});
//
//			// 특별한 조건 실행할때
//			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
//				Animator* pAni = pObject->GetAnimator();
//
//				if (pAni->GetFrameRatio() > 0.98) {
//					return BehaviorResult::Success;
//				}
//				return BehaviorResult::Failure;
//				});
//
//			// 상태 변경(Task) : 상태 변경 조건
//			BehaviorTask* pChangeState = new BehaviorTask([&]()
//				{
//					PrevState = meBasicState;
//					meBasicState = MonsterBasicState::Roll_End;
//					return BehaviorResult::Success;
//				});
//
//
//			pRoll_03Sequence->AddChild(pStateChecker);
//			pRoll_03Sequence->AddChild(pRunAnimationTask);
//			pRoll_03Sequence->AddChild(pTask);
//			pRoll_03Sequence->AddChild(pCondition);
//			pRoll_03Sequence->AddChild(pChangeState);
//		}
//		pStateSelector->AddChild(pRoll_03Sequence);
//
//#pragma endregion

//#pragma region Attack Roll_End Sequence
//		Sequence* pRoll_EndSequence = new Sequence;
//		{
//			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
//			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
//				{
//					if (MonsterBasicState::Roll_End == meBasicState)
//						return BehaviorResult::Success;
//					else
//						return BehaviorResult::Failure;
//				});
//
//			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
//			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
//				Animator* pAnimator = GetAnimator();
//				int animIndex = pAnimator->GetCurrentClipIndex();
//				if (3 != animIndex)
//				{
//					pObject->Disable();
//					Enable();
//					pAnimator->Play(3, true);
//				}
//				return BehaviorResult::Success;
//				});
//
//			// 이동+Col 처리 하는곳
//			BehaviorTask* pTask = new BehaviorTask([&]()
//				{
//
//
//
//					return BehaviorResult::Success;
//				});
//
//			// 특별한 조건 실행할때
//			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
//				Animator* pAni = GetAnimator();
//
//				if (pAni->GetFrameRatio() > 0.3) {
//					return BehaviorResult::Success;
//				}
//				return BehaviorResult::Failure;
//				});
//
//			// 상태 변경(Task) : 상태 변경 조건
//			BehaviorTask* pChangeState = new BehaviorTask([&]()
//				{
//					PrevState = meBasicState;
//					meBasicState = MonsterBasicState::Fall_Loop;
//					return BehaviorResult::Success;
//				});
//
//
//			pRoll_EndSequence->AddChild(pStateChecker);
//			pRoll_EndSequence->AddChild(pRunAnimationTask);
//			pRoll_EndSequence->AddChild(pTask);
//			pRoll_EndSequence->AddChild(pCondition);
//			pRoll_EndSequence->AddChild(pChangeState);
//		}
//		pStateSelector->AddChild(pRoll_EndSequence);
//
//#pragma endregion

#pragma region Attack Laser_Start Sequence
		Sequence* pLaser_StartSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Laser_Start == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (6 != animIndex)
				{
					GetRigidBody()->RemoveGravity();
					GetRigidBody()->SetVelocity(AXIS_Y, 0.f);

					pAnimator->Play(6, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{

					LaserFollow_Turn();

					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.98) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Laser;
					return BehaviorResult::Success;
				});


			pLaser_StartSequence->AddChild(pStateChecker);
			pLaser_StartSequence->AddChild(pRunAnimationTask);
			pLaser_StartSequence->AddChild(pTask);
			pLaser_StartSequence->AddChild(pCondition);
			pLaser_StartSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pLaser_StartSequence);

#pragma endregion

#pragma region Attack Laser Sequence
		Sequence* pLaserSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Laser == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (7 != animIndex)
				{
					GetRigidBody()->RemoveGravity();
					GetRigidBody()->SetVelocity(AXIS_Y, 0.f);
					CreateCow(Vec3(10.f, -1.f, 0.f));
					CreateCow(Vec3(-15.f, -1.f, 0.f));
					CreateCow(Vec3(0.f, -1.f, 10.f));
					CreateCow(Vec3(0.f, -1.f, -10.f));
					pAnimator->Play(7, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{

					

					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.98) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Laser_End;
					return BehaviorResult::Success;
				});


			pLaserSequence->AddChild(pStateChecker);
			pLaserSequence->AddChild(pRunAnimationTask);
			pLaserSequence->AddChild(pTask);
			pLaserSequence->AddChild(pCondition);
			pLaserSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pLaserSequence);

#pragma endregion

#pragma region Attack Laser_End Sequence
		Sequence* pLaser_EndSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Laser_End == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (8 != animIndex)
				{
					GetRigidBody()->ApplyGravity();
					LaserPrevFollowSet();
					pAnimator->Play(8, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{
					mMagnScale = 3.f;
					LaserPrevFollowLive();
					SlowTurnLive();
					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.45) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Land_Slam;
					return BehaviorResult::Success;
				});


			pLaser_EndSequence->AddChild(pStateChecker);
			pLaser_EndSequence->AddChild(pRunAnimationTask);
			pLaser_EndSequence->AddChild(pTask);
			pLaser_EndSequence->AddChild(pCondition);
			pLaser_EndSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pLaser_EndSequence);

#pragma endregion

#pragma region Fall_Loop Sequence
		Sequence* pFall_LoopSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Fall_Loop == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (4 != animIndex)
				{
					PrevFollowSet();
					pAnimator->Play(4, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{
					TurnSpeed = 3.f;
					SlowTurnLive();
					PrevFollowLive();

					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.2) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Land_Slam;
					return BehaviorResult::Success;
				});


			pFall_LoopSequence->AddChild(pStateChecker);
			pFall_LoopSequence->AddChild(pRunAnimationTask);
			pFall_LoopSequence->AddChild(pTask);
			pFall_LoopSequence->AddChild(pCondition);
			pFall_LoopSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pFall_LoopSequence);

#pragma endregion

#pragma region Land_Slam Sequence
		Sequence* pLand_SlamSequence = new Sequence;
		{
			// 상태 확인(Condition) : 현재 상태가 Idle인지 확인
			BehaviorCondition* pStateChecker = new BehaviorCondition([&]()
				{
					if (MonsterBasicState::Land_Slam == meBasicState)
						return BehaviorResult::Success;
					else
						return BehaviorResult::Failure;
				});

			// 애니메이션 실행(Task) : 상태에 맞는 애니메이션이 실행되지 않았다면 실행
			BehaviorTask* pRunAnimationTask = new BehaviorTask([&]() {
				Animator* pAnimator = GetAnimator();
				int animIndex = pAnimator->GetCurrentClipIndex();
				if (5 != animIndex)
				{
					GetRigidBody()->SetVelocity(AXIS_Y, 0.f);
					pObject->Disable();
					Enable();
					pAnimator->Play(5, true);
				}
				return BehaviorResult::Success;
				});

			// 이동+Col 처리 하는곳
			BehaviorTask* pTask = new BehaviorTask([&]()
				{



					return BehaviorResult::Success;
				});

			// 특별한 조건 실행할때
			BehaviorCondition* pCondition = new BehaviorCondition([&]() {
				Animator* pAni = GetAnimator();

				if (pAni->GetFrameRatio() > 0.3) {
					return BehaviorResult::Success;
				}
				return BehaviorResult::Failure;
				});

			// 상태 변경(Task) : 상태 변경 조건
			BehaviorTask* pChangeState = new BehaviorTask([&]()
				{
					PrevState = meBasicState;
					meBasicState = MonsterBasicState::Idle;
					return BehaviorResult::Success;
				});


			pLand_SlamSequence->AddChild(pStateChecker);
			pLand_SlamSequence->AddChild(pRunAnimationTask);
			pLand_SlamSequence->AddChild(pTask);
			pLand_SlamSequence->AddChild(pCondition);
			pLand_SlamSequence->AddChild(pChangeState);
		}
		pStateSelector->AddChild(pLand_SlamSequence);

#pragma endregion

	}
	pRootNode->AddChild(pStateSelector);
}




void LORD_BOSS::Initialize()
{
	Monster::Initialize();

	Animator* pAnimator = GetAnimator();
	pAnimator->SetLoop(0, true);
}

void LORD_BOSS::Update()
{
	Health = (mHP / mMaxHP) * 100;
	Monster::Update();

	SlowTurnLive();
}

void LORD_BOSS::FixedUpdate()
{
	Monster::FixedUpdate();
}

void LORD_BOSS::FinalUpdate()
{
	Monster::FinalUpdate();
}

void LORD_BOSS::Render()
{
	Monster::Render();
}

void LORD_BOSS::Destroy()
{
	Monster::Destroy();
}

void LORD_BOSS::OnCollisionEnter(Collider* _pOtherCollider)
{
}

void LORD_BOSS::OnCollisionStay(Collider* _pOtherCollider)
{
}

void LORD_BOSS::OnCollisionExit(Collider* _pOtherCollider)
{
}





void LORD_BOSS::OnTriggerEnter(Collider* _pOtherCollider)
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

	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType()
		&& isWall == true)
	{
		isGround = true;
	}

	Player* pPlayer = PLAYER;
	float attackDamage = pPlayer->GetAttackDamage();

	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType()
		|| LayerType::ArrowCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		TakeDamage(attackDamage);
	}

	if (LayerType::WallObject == _pOtherCollider->GetGameObject()->GetLayerType()
		&& meBasicState == MonsterBasicState::Roll_02)
	{
		GetRigidBody()->SetVelocity(AXIS_Y,20.f);
		isWall = true;
	}
}

void LORD_BOSS::OnTriggerStay(Collider* _pOtherCollider)
{
}

void LORD_BOSS::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}

void LORD_BOSS::SlowTurnLive()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Transform* pTr = GetTransform();

	RotDir = playerPos - myPos;
	RotDir.Normalize();
	RotDir.y = 0;

	Vec3 Rot = pTr->GetRotation();
	Vec3 rot = Vec3(0, 0, -1);
	double angleRadian = atan2(RotDir.x, RotDir.z) - atan2(rot.x, rot.z);
	float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

	if (angleDegree < 0.f)
		angleDegree += 360.f;

	int Right = TurnSpeed;
	int Left = -TurnSpeed;
	// 0 -> 360                200
	if (Rot.z + 3 < angleDegree)
		pTr->SetRotation(Vec3(-90.f, 0.f, Rot.z + Right));
	else if (Rot.z - 3 > angleDegree)
		pTr->SetRotation(Vec3(-90.f, 0.f, Rot.z + Left));
	else if (Rot.z == angleDegree)
		pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));

	TurnSpeed = 2.f;
	/*FONT->DrawString(std::to_wstring(Rot.z), 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff0000ff, FONT_ALIGN::LEFT);
	FONT->DrawString(std::to_wstring(angleDegree), 30.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff0000ff, FONT_ALIGN::LEFT);*/
}

void LORD_BOSS::SlowTurn()
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

	TurnSpeed = 50.f;
}

void LORD_BOSS::Follow()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Transform* pTr = GetTransform();

	PosDir = playerPos - myPos;
	Vec3 Num = scale * PosDir;
	float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));

	PosDir.Normalize();
	PosDir.y = 0;
	// 몬스터의 이동속도가 들어가야 함
	// 방향을 변경해주는 Task도 필요
	Vec3 Ve = PosDir * mSpeed;

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

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->GetCollider())
		{
			if (GetCollider()->Raycast(myPos, PosDir, gameObjects[i]->GetCollider(), 0.5f))
			{
				GetRigidBody()->SetVelocity(PosDir * 0.f);
			}
		}
	}
}

void LORD_BOSS::PrevFollowSet()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	PosDir = playerPos - myPos;
	PosDir.Normalize();
	PosDir.y = 0;
}

void LORD_BOSS::PrevFollowLive()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Transform* pTr = GetTransform();

	
	Vec3 Num = scale * PosDir;
	float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));

	
	// 몬스터의 이동속도가 들어가야 함
	// 방향을 변경해주는 Task도 필요
	Vec3 Ve = PosDir * (mSpeed*mMagnScale);

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

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->GetCollider())
		{
			if (GetCollider()->Raycast(myPos, PosDir, gameObjects[i]->GetCollider(), 0.5f))
			{
				GetRigidBody()->SetVelocity(PosDir * 0.f);
			}
		}
	}


	mSpeed = 8.f;
	mMagnScale = 2.f;
}

bool LORD_BOSS::LookRay()
{
	//현모님이 봐주심
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = pObject->GetTransform()->GetPosition();

	//Dir = playerPos - myPos;
	//Dir.Normalize();
	//Dir.y = 0;

	const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(LayerType::Player);

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->GetCollider())
		{
			if (pObject->GetCollider()->Raycast(myPos, PosDir, gameObjects[i]->GetCollider(), 5.f))
			{
				return true;
			}
		}
	}
	return false;
}

void LORD_BOSS::LaserFollow_Turn()
{
	Vec3 myPos = GetTransform()->GetPosition();
	Transform* pTr = GetTransform();

	PosDir = LaserPos - myPos; //목표 위치

	if (PosDir.Length() < 1) {
		GetRigidBody()->SetVelocity(Vec3::Zero);
		return;
	}
	PosDir.Normalize();
	Vec3 Rot = pTr->GetRotation();
	float TargetRot = LaserRot.z;
	//Vec3 rot = Vec3(0, 0, -1);
	//double angleRadian = atan2(PosDir.x, PosDir.z) - atan2(rot.x, rot.z);
	//float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

	if (TargetRot < 0.f)
		TargetRot += 360.f;

	int Right = TurnSpeed;
	int Left = -TurnSpeed;
	if (Rot.z + 3 < TargetRot)
		pTr->SetRotation(Vec3(-90.f, 0.f, Rot.z + Right));
	else if (Rot.z - 3 > TargetRot)
		pTr->SetRotation(Vec3(-90.f, 0.f, Rot.z + Left));
	else if (Rot.z == TargetRot)
		pTr->SetRotation(Vec3(-90.f, 0.f, TargetRot));

	Vec3 Ve = PosDir * (mSpeed * mMagnScale);
	GetRigidBody()->SetVelocity(Ve);

	TurnSpeed = 6.f;
}

void LORD_BOSS::LaserPrevFollowSet()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	PosDir = playerPos - myPos;
	PosDir.y += 3;
	PosDir.Normalize();
}

void LORD_BOSS::LaserPrevFollowLive()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Transform* pTr = GetTransform();


	Vec3 Num = scale * PosDir;
	float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));


	// 몬스터의 이동속도가 들어가야 함
	// 방향을 변경해주는 Task도 필요
	Vec3 Ve = PosDir * (mSpeed * mMagnScale);

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

	for (int i = 0; i < gameObjects.size(); ++i)
	{
		if (gameObjects[i]->GetCollider())
		{
			if (GetCollider()->Raycast(myPos, PosDir, gameObjects[i]->GetCollider(), 0.5f))
			{
				GetRigidBody()->SetVelocity(PosDir * 0.f);
			}
		}
	}


	mSpeed = 8.f;
	mMagnScale = 2.f;
}

void LORD_BOSS::CreateCow(Vec3 _pos)
{
	// 보스가 소환하는 소
	{
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(1.5f, 1.0f, 2.f);

		Cow* pBullKnocker = Factory::CreateMonster<Cow>(Vec3(_pos), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\BullKnocker.fbx");
		pBullKnocker->GetMeshRenderer()->SetMaterial(pBullKnocker->GetMeshRenderer()->GetMaterial()->Clone());

		pBullKnocker->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		pBullKnocker->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
		pBullKnocker->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -1.f, 0.f));
		pBullKnocker->GetAnimator()->SetPlaySpeed(0, 4.f);
		pBullKnocker->GetAnimator()->SetPlaySpeed(1, 3.f);
		pBullKnocker->GetAnimator()->SetPlaySpeed(2, 2.f);
		//pBullKnocker->GetAnimator()->Play(0,true);
		//SetGizmoTarget(p_E_HEADROLLER);
		pBullKnocker->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pBullKnocker);

		//SetMeshTarget(pBullKnocker);
	}
}
