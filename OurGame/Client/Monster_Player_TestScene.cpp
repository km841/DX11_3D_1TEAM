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
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Grandma_Boss, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		// 1층 바닥 - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 0.1f, 37.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");

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

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			//Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow_Fix.fbx");
			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			SetMeshTarget(pPlayer);
		}

		
		

		// 콩벌레
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* p_E_HEADROLLER = Factory::CreateObjectHasPhysical<Monster>(Vec3(0.f, 3.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_HEADROLLER.fbx");
		//	p_E_HEADROLLER->GetTransform()->SetScale(Vec3(50.5f, 50.5f, 50.5f));
		//	p_E_HEADROLLER->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

		//	//SetGizmoTarget(p_E_HEADROLLER);
		//	AddGameObject(p_E_HEADROLLER);
		//	//SetAnimTarget(p_E_HEADROLLER);
		//}

		//// 초록거미
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Dynamic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* p_E_LURKER = Factory::CreateObjectHasPhysical<Monster>(Vec3(1.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_LURKER.fbx");
		//	p_E_LURKER->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
		//	p_E_LURKER->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
		//	p_E_LURKER->GetRigidBody()->ApplyGravity();
		//	//SetGizmoTarget(p_E_LURKER);
		//	AddGameObject(p_E_LURKER);
		//	SetMeshTarget(p_E_LURKER);
		//}
		
	
		//// 마법사
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* p_E_MAGE = Factory::CreateObjectHasPhysical<Monster>(Vec3(-3.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_MAGE.fbx");
		//	p_E_MAGE->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
		//	p_E_MAGE->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

		//	//SetGizmoTarget(p_E_MAGE);
		//	AddGameObject(p_E_MAGE);
		//	//SetAnimTarget(p_E_MAGE);
		//}

		// 중간보스 내루미
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* p_E_GRIMACE_KNIGHT = Factory::CreateObjectHasPhysical<Monster>(Vec3(-5.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
		//	p_E_GRIMACE_KNIGHT->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
		//	p_E_GRIMACE_KNIGHT->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));

		//	//SetGizmoTarget(p_E_GRIMACE_KNIGHT);
		//	AddGameObject(p_E_GRIMACE_KNIGHT);
		//	SetAnimTarget(p_E_GRIMACE_KNIGHT);
		//}

		 //박쥐
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* p_E_BAT_White = Factory::CreateObjectHasPhysical<Monster>(Vec3(-9.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\_E_BAT_White.fbx");
		//	p_E_BAT_White->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
		//	p_E_BAT_White->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
		//	p_E_BAT_White->SetFrustumCheckFlag(false);
		//	//SetGizmoTarget(p_E_BAT_White);
		//	AddGameObject(p_E_BAT_White);
		//	SetMeshTarget(p_E_BAT_White);
		//}

		

		////최종보스 할머니 - _E_Grandma
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Grandma* p_E_Grandma = Factory::CreateObjectHasPhysical<Grandma>(Vec3(-11.f, 0.f, 5.f), info, L"Deferred", LARGE_RESOURCE(L"Monster\\_E_Grandma.fbx"));
		//	p_E_Grandma->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
		//	p_E_Grandma->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
		//	p_E_Grandma->SetFrustumCheckFlag(false);
		//	p_E_Grandma->GetRigidBody()->ApplyGravity();
		//	//SetGizmoTarget(p_E_Grandma);
		//	AddGameObject(p_E_Grandma);
		//	SetMeshTarget(p_E_Grandma);
		//}

		////항아리 미믹 - POT_Mimic_Melee_AVARICE
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* pPOT_Mimic_Melee_AVARICE = Factory::CreateObjectHasPhysical<Monster>(Vec3(-11.f, 0.f, 5.f), info, L"Deferred", L"..\\Resources\\FBX\\Monster\\POT_Mimic_Melee_AVARICE.fbx");
		//	pPOT_Mimic_Melee_AVARICE->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
		//	pPOT_Mimic_Melee_AVARICE->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

		//	//SetGizmoTarget(p_E_Grandma);
		//	AddGameObject(pPOT_Mimic_Melee_AVARICE);
		//	//SetAnimTarget(pPOT_Mimic_Melee_AVARICE);
		//}
	}
	void Monster_Player_TestScene::Exit()
	{
	}
}