#include "pch.h"
#include "Monster_Player_TestScene.h"
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

/* Event */
#include "SceneChangeEvent.h"


namespace hm {

	Monster_Player_TestScene::Monster_Player_TestScene()
		: Map(MapType::Monster_Player_Test)
	{
	}
	Monster_Player_TestScene::~Monster_Player_TestScene()
	{
	}
	void Monster_Player_TestScene::Initialize()
	{
		Map::Initialize();
	}
	void Monster_Player_TestScene::Start()
	{
		Map::Start();
	}
	void Monster_Player_TestScene::Update()
	{
		Map::Update();
	}
	void Monster_Player_TestScene::FixedUpdate()
	{
		Map::FixedUpdate();
	}
	void Monster_Player_TestScene::FinalUpdate()
	{
		Map::FinalUpdate();
	}
	void Monster_Player_TestScene::Render()
	{
		Map::Render();
	}
	void Monster_Player_TestScene::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		// 1층 바닥 - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 0.1f, 37.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");

			pFloor->GetTransform()->SetScale(Vec3(37.f, 37.f, 37.f));
			pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));

			AddGameObject(pFloor);
		}

		// Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			//pPlayer->AddComponent(new TestAnimationScript);
			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			
		}

		// PotHead
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Npc* pPotHead = Factory::CreateObjectHasPhysical<Npc>(Vec3(5.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Npc\\Npc_PotHead.fbx");
			pPotHead->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			pPotHead->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			// 애니메이션의 이름은 FBX에 저장되어 있는 것을 그대로 가져오므로 해당 FBX를 사용하는 클래스의 생성자와 같은 특정 부분에서
			// 사용하기 편한 이름으로 일괄적으로 바꿔줄 필요가 있음
			pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

			// 반복 여부를 설정하는 함수 (Finished 플래그를 사용할 수 없음)
			pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

			// 인덱스 번호로도 사용 가능
			pPotHead->GetAnimator()->SetLoop(9, true);

			// HasExit는 현재 애니메이션 실행중에 다른 애니메이션이 실행되었을 때 바로 넘길건지 여부를 결정 (기본적으로 true)
			// 이 값이 false면 애니메이션 플레이 도중 다른 애니메이션 Play가 실행되었을 때 기존 애니메이션이 다 끝나고 실행됨
			pPotHead->GetAnimator()->SetHasExitFlag(9, false);

			// 애니메이션 실행하는 방법은 2D와 비슷하게 애니메이션 이름, 반복할건지 여부를 넣어주면 됨
			pPotHead->GetAnimator()->Play(L"PotHead_Idle", true);

			AddGameObject(pPotHead);
			//SetAnimTarget(pPotHead);
		}

		// 콩벌레
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_HEADROLLER = Factory::CreateObjectHasPhysical<Monster>(Vec3(3.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_HEADROLLER.fbx");
			p_E_HEADROLLER->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_HEADROLLER->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_HEADROLLER);
			AddGameObject(p_E_HEADROLLER);
			//SetAnimTarget(p_E_HEADROLLER);
		}

		// 초록거미
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_LURKER = Factory::CreateObjectHasPhysical<Monster>(Vec3(1.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_LURKER.fbx");
			p_E_LURKER->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_LURKER->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_LURKER);
			AddGameObject(p_E_LURKER);
			//SetAnimTarget(p_E_LURKER);
		}
		
		// 중간보스 나이트
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_KNIGHT = Factory::CreateObjectHasPhysical<Monster>(Vec3(-1.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_KNIGHT.fbx");
			p_E_KNIGHT->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_KNIGHT->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_KNIGHT);
			AddGameObject(p_E_KNIGHT);
			//SetAnimTarget(p_E_KNIGHT);
		}

		// 마법사
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_MAGE = Factory::CreateObjectHasPhysical<Monster>(Vec3(-3.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_MAGE.fbx");
			p_E_MAGE->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_MAGE->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_MAGE);
			AddGameObject(p_E_MAGE);
			//SetAnimTarget(p_E_MAGE);
		}

		// 중간보스 내루미
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_GRIMACE_KNIGHT = Factory::CreateObjectHasPhysical<Monster>(Vec3(-5.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
			p_E_GRIMACE_KNIGHT->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_GRIMACE_KNIGHT->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_GRIMACE_KNIGHT);
			AddGameObject(p_E_GRIMACE_KNIGHT);
			//SetAnimTarget(p_E_GRIMACE_KNIGHT);
		}

		// 박쥐
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_BAT_White = Factory::CreateObjectHasPhysical<Monster>(Vec3(-9.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_BAT_White.fbx");
			p_E_BAT_White->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_BAT_White->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_BAT_White);
			AddGameObject(p_E_BAT_White);
			//SetAnimTarget(p_E_BAT_White);
		}

		// 항아리 미믹
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* pPOT_Mimic_Melee = Factory::CreateObjectHasPhysical<Monster>(Vec3(-11.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\POT_Mimic_Melee.fbx");
			pPOT_Mimic_Melee->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			pPOT_Mimic_Melee->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(pPOT_Mimic_Melee);
			AddGameObject(pPOT_Mimic_Melee);
			//SetAnimTarget(pPOT_Mimic_Melee);
		}

		//최종보스 할머니 - _E_Grandma
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.f, 2.f);

			Monster* p_E_Grandma = Factory::CreateObjectHasPhysical<Monster>(Vec3(-11.f, 0.f, 5.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_Grandma.fbx");
			p_E_Grandma->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			p_E_Grandma->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			//SetGizmoTarget(p_E_Grandma);
			AddGameObject(p_E_Grandma);
			//SetAnimTarget(p_E_Grandma);
		}


	}
	void Monster_Player_TestScene::Exit()
	{
	}
}