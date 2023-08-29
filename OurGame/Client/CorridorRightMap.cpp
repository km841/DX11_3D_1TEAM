#include "pch.h"
#include "CorridorRightMap.h"
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

/* Event */
#include "SceneChangeEvent.h"

CorridorRightMap::CorridorRightMap()
	: Map(MapType::CorridorRightMap)
{
}

CorridorRightMap::~CorridorRightMap()
{
}

void CorridorRightMap::Initialize()
{
	Map::Initialize();
}

void CorridorRightMap::Update()
{
	Map::Update();
}

void CorridorRightMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void CorridorRightMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void CorridorRightMap::Render()
{
	Map::Render();
}

void CorridorRightMap::Enter()
{
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

	//배경맵 하얀색으로 만들어주는 코드
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

#pragma region 벽
	// 벽
	{
		DecoObject* pWall = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor.fbx");

		pWall->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
		pWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"crWallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor.fbm\\grandmaWallPaperTexture.png");
		pWall->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		pWall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.3f, 0.3f));

		//텍스처 무시하고 단색으로 채우는 코드
		//pWall->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
		//pWall->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));

		AddGameObject(pWall);
	}
	// 숨겨진 벽
	{
		DecoObject* pWallSecret = Factory::CreateObject<DecoObject>(Vec3(2.f, -2.2f, 20.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\SecretWoodDoor.fbx");

		pWallSecret->GetTransform()->SetScale(Vec3(8.9f, 8.7f, 1.f));
		pWallSecret->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

		AddGameObject(pWallSecret);
	}
	// 문틀
	{
		DecoObject* pDoorFrame = Factory::CreateObject<DecoObject>(Vec3(-2.6f, -4.2f, 14.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\doorSideFrame.fbx");

		pDoorFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pDoorFrame->GetTransform()->SetScale(Vec3(5.83f, 5.9f, 3.7f));

		AddGameObject(pDoorFrame);
	}
#pragma endregion

#pragma region 바닥
	// 바닥
	{
		PhysicsInfo info;
		info.eActorType = ActorType::Static;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(10.f, 0.5f, 10.f);

		Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -7.1f, -2.19f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor-detach.fbx");

		pFloor->GetTransform()->SetScale(Vec3(45.7f, 1.f, 45.6f));
		pFloor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

		AddGameObject(pFloor);
	}
	// 바깥쪽 바닥틀
	{
		DecoObject* pFloorRimBig = Factory::CreateObject<DecoObject>(Vec3(2.24f, -7.5f, -2.66f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\wallPanel (3)-Merged (4).fbx");

		pFloorRimBig->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pFloorRimBig->GetTransform()->SetScale(Vec3(46.f, 43.6f, 45.2f));

		AddGameObject(pFloorRimBig);
	}
	// 안쪽 바닥틀
	{
		DecoObject* pFloorRim = Factory::CreateObject<DecoObject>(Vec3(2.24f, -7.2f, 20.54f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

		pFloorRim->GetTransform()->SetScale(Vec3(10.f, 4.f, 4.f));

		AddGameObject(pFloorRim);
	}
	// 안쪽 바닥틀2
	{
		DecoObject* pFloorRim2 = Factory::CreateObject<DecoObject>(Vec3(-2.76f, -7.2f, 21.44f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

		pFloorRim2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pFloorRim2->GetTransform()->SetScale(Vec3(9.5f, 4.f, 4.f));

		AddGameObject(pFloorRim2);
	}
	// 안쪽 바닥틀3
	{
		DecoObject* pFloorRim3 = Factory::CreateObject<DecoObject>(Vec3(-2.76f, -7.2f, -1.66f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

		pFloorRim3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pFloorRim3->GetTransform()->SetScale(Vec3(29.15f, 4.f, 4.f));

		//SetGizmoTarget(pFloorRim3);
		AddGameObject(pFloorRim3);
	}
#pragma endregion

#pragma region 기둥
	// 바깥쪽 기둥
	{
		DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(6.6f, -2.95f, 20.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		AddGameObject(pColumn);
	}
	// 안쪽 기둥
	{
		DecoObject* pColumn2 = Factory::CreateObject<DecoObject>(Vec3(-2.7f, -2.95f, 20.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn2->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		AddGameObject(pColumn2);
	}
	// 안쪽 기둥2
	{
		DecoObject* pColumn3 = Factory::CreateObject<DecoObject>(Vec3(-2.67f, -2.95f, 6.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pColumn3->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		AddGameObject(pColumn3);
	}
	// 안쪽 기둥3
	{
		DecoObject* pColumn4 = Factory::CreateObject<DecoObject>(Vec3(-2.67f, -2.95f, -8.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pColumn4->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		AddGameObject(pColumn4);
	}
	// 안쪽 기둥4
	{
		DecoObject* pColumn5 = Factory::CreateObject<DecoObject>(Vec3(-2.67f, -2.95f, -24.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pColumn5->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		SetGizmoTarget(pColumn5);
		AddGameObject(pColumn5);
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
		pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		AddGameObject(pPlayer);
	}*/
}

void CorridorRightMap::Exit()
{
}
