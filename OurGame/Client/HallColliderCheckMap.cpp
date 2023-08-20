#include "pch.h"
#include "HallColliderCheckMap.h"
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

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace jh
{
	HallColliderCheckMap::HallColliderCheckMap()
		: Map(MapType::HallColliderCheckMap)
	{
	}

	HallColliderCheckMap::~HallColliderCheckMap()
	{
	}

	void HallColliderCheckMap::Initialize()
	{
		Map::Initialize();
	}

	void HallColliderCheckMap::Update()
	{
		Map::Update();
	}

	void HallColliderCheckMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void HallColliderCheckMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void HallColliderCheckMap::Render()
	{
		Map::Render();
	}

	void HallColliderCheckMap::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		//¹è°æ¸Ê ÇÏ¾á»öÀ¸·Î ¸¸µé¾îÁÖ´Â ÄÚµå
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

#pragma region 1Ãþ
		// 1, 2Ãþ º®
		{
			DecoObject* pFirstFloorWall = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main.fbx");

			pFirstFloorWall->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pFirstFloorWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pFirstFloorWall);
		}
		// 1Ãþ ¹Ù´Ú
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.f, 0.1f, 5.f);

			Ground* pFirstFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.14f, -1.3f, -2.82f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor Lower.fbx");
			
			pFirstFloor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pFirstFloor->GetTransform()->SetScale(Vec3(5.1f, 5.f, 5.1f));

			pFirstFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pFirstFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(154.f, 140.f, 105.f));

			AddGameObject(pFirstFloor);
		}
		// 1Ãþ °è´Ü(¿ÞÂÊ)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pFirstFloorLeftStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-1.15f, -0.75f, 0.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pFirstFloorLeftStairs->GetTransform()->SetRotation(Vec3(-24.2f, 0.f, 0.f));
			pFirstFloorLeftStairs->GetTransform()->SetScale(Vec3(2.6f, 2.4f, 2.65f));
			pFirstFloorLeftStairs->GetTransform()->SetRotationExcludingColliders(Vec3(24.2f, 0.f, 0.f));
			pFirstFloorLeftStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));
			AddGameObject(pFirstFloorLeftStairs);
		}
		// 1Ãþ °è´Ü(¿À¸¥ÂÊ)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pFirstFloorRightStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.94f, -0.75f, 0.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pFirstFloorRightStairs->GetTransform()->SetRotation(Vec3(-24.2f, 0.f, 0.f));
			pFirstFloorRightStairs->GetTransform()->SetScale(Vec3(2.7f, 2.4f, 2.65f));
			pFirstFloorRightStairs->GetTransform()->SetRotationExcludingColliders(Vec3(24.2f, 0.f, 0.f));
			pFirstFloorRightStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));
			AddGameObject(pFirstFloorRightStairs);
		}
#pragma endregion
#pragma region 2Ãþ
		// 2Ãþ º®2
		{
			DecoObject* pSecondFloorWall = Factory::CreateObject<DecoObject>(Vec3(-2.15f, 0.215f, -1.66f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main (1).fbx");

			pSecondFloorWall->GetTransform()->SetScale(Vec3(6.2f, 6.45f, 10.f));
			pSecondFloorWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pSecondFloorWall);
		}
		// 2Ãþ ¹Ù´Ú
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(7.8f, 0.1f, 8.4f);

			Ground* pSecondFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.34f, -0.23f, 3.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor.fbx");

			pSecondFloor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 180.f));
			pSecondFloor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, -0.98f));
			pSecondFloor->GetTransform()->SetScale(Vec3(10.3f, 5.f, 10.3f));

			pSecondFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pSecondFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(154.f, 140.f, 105.f));

			AddGameObject(pSecondFloor);
		}
		// 2Ãþ °è´Ü(¿ÞÂÊ)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pSecondFloorLeftStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-1.f, 0.35f, 6.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pSecondFloorLeftStairs->AddComponent<PlacementScript>();
			pSecondFloorLeftStairs->GetTransform()->SetRotation(Vec3(-24.2f, 0.f, 0.f));
			pSecondFloorLeftStairs->GetTransform()->SetScale(Vec3(2.7f, 2.4f, 2.55f));
			pSecondFloorLeftStairs->GetTransform()->SetRotationExcludingColliders(Vec3(24.2f, 0.f, 0.f));
			pSecondFloorLeftStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));
			AddGameObject(pSecondFloorLeftStairs);
		}
#pragma endregion
#pragma region 3Ãþ
		// 3Ãþ º®
		{
			DecoObject* pThirdFloorWall = Factory::CreateObject<DecoObject>(Vec3(0.4f, 1.7f, 7.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TopFloor.fbx");

			pThirdFloorWall->GetTransform()->SetScale(Vec3(6.1f, 6.f, 6.35f));
			pThirdFloorWall->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pThirdFloorWall);
		}
		// 3Ãþ º®2
		{
			DecoObject* pThirdFloorWall2 = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.15f, 7.11f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TopFloor-detach.fbx");

			pThirdFloorWall2->GetTransform()->SetScale(Vec3(4.35f, 4.3f, 6.35f));
			pThirdFloorWall2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pThirdFloorWall2);
		}
		// 3Ãþ ¹Ù´Ú
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.1f, 0.1f, 6.4f);

			Ground* pThirdFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.4f, 0.85f, 7.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor Upper 2.fbx");
			
			pThirdFloor->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pThirdFloor->GetTransform()->SetScale(Vec3(6.1f, 5.f, 6.4f));

			pThirdFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pThirdFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(154.f, 140.f, 105.f));

			AddGameObject(pThirdFloor);
		}
#pragma endregion

		// Toy
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.2f, 0.2f, 0.2f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 1.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(0.2f, 0.2f, 0.2f));

			AddGameObject(pPlayer);
		}*/
	}

	void HallColliderCheckMap::Exit()
	{
	}
}