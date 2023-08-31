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
	// 문틀2
	{
		DecoObject* pDoorFrame2 = Factory::CreateObject<DecoObject>(Vec3(-2.6f, -4.2f, -18.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\doorSideFrame.fbx");

		pDoorFrame2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pDoorFrame2->GetTransform()->SetScale(Vec3(5.83f, 5.9f, 3.7f));

		AddGameObject(pDoorFrame2);
	}
#pragma endregion

#pragma region 벽 장식
	// 커튼
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(2.f, 0.11f, 19.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\CurtainHorizontal.fbx");

		pCurtainHorizontal->GetTransform()->SetScale(Vec3(8.62f, 12.f, 10.1f));

		AddGameObject(pCurtainHorizontal);
	}
	// 커튼2
	{
		DecoObject* pCurtainHorizontal2 = Factory::CreateObject<DecoObject>(Vec3(-1.8f, 0.11f, 13.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\CurtainHorizontal.fbx");

		pCurtainHorizontal2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pCurtainHorizontal2->GetTransform()->SetScale(Vec3(12.67f, 12.f, 10.1f));

		AddGameObject(pCurtainHorizontal2);
	}
	// 커튼3
	{
		DecoObject* pCurtainHorizontal3 = Factory::CreateObject<DecoObject>(Vec3(-1.8f, 0.11f, -16.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\CurtainHorizontal.fbx");

		pCurtainHorizontal3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pCurtainHorizontal3->GetTransform()->SetScale(Vec3(14.43f, 12.f, 10.1f));

		AddGameObject(pCurtainHorizontal3);
	}
	// 그림
	{
		DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-2.64f, -1.39f, -1.27f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame.fbx");

		pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pPaintingFrame->GetTransform()->SetScale(Vec3(4.147f, 4.576f, 5.72f));

		AddGameObject(pPaintingFrame);
	}
	// 그림2(왼쪽)
	{
		DecoObject* pPaintingFrame2Left = Factory::CreateObject<DecoObject>(Vec3(-2.64f, -3.85f, -4.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame2.fbx");

		pPaintingFrame2Left->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pPaintingFrame2Left->GetTransform()->SetScale(Vec3(2.053f, 2.059f, 1.144f));

		AddGameObject(pPaintingFrame2Left);
	}
	// 그림2(오른쪽)
	{
		DecoObject* pPaintingFrame2Right = Factory::CreateObject<DecoObject>(Vec3(-2.64f, -0.09f, 3.63f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame2.fbx");

		pPaintingFrame2Right->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pPaintingFrame2Right->GetTransform()->SetScale(Vec3(2.053f, 2.059f, 1.144f));

		AddGameObject(pPaintingFrame2Right);
	}
	// 그림3
	{
		DecoObject* pPaintingFrame3 = Factory::CreateObject<DecoObject>(Vec3(-2.635f, -0.79f, -6.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame3.fbx");

		pPaintingFrame3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pPaintingFrame3->GetTransform()->SetScale(Vec3(3.3874f, 3.924f, 1.704f));

		AddGameObject(pPaintingFrame3);
	}
	// 그림4
	{
		DecoObject* pPaintingFrame4 = Factory::CreateObject<DecoObject>(Vec3(-2.585f, -3.72f, 1.83f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame4.fbx");

		pPaintingFrame4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pPaintingFrame4->GetTransform()->SetScale(Vec3(3.726f, 4.0425f, 5.112f));

		AddGameObject(pPaintingFrame4);
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

		AddGameObject(pFloorRim3);
	}
	// 안쪽 바닥틀4
	{
		DecoObject* pFloorRim4 = Factory::CreateObject<DecoObject>(Vec3(-2.76f, -7.2f, -22.46f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

		pFloorRim4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pFloorRim4->GetTransform()->SetScale(Vec3(4.75f, 4.f, 4.f));

		AddGameObject(pFloorRim4);
	}
	// 철창
	{
		DecoObject* pSpikeDoor = Factory::CreateObject<DecoObject>(Vec3(-3.06f, -5.8f, -18.21f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\SpikeDoor.fbx");

		pSpikeDoor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pSpikeDoor->GetTransform()->SetScale(Vec3(4.75f, 4.9f, 4.85f));

		AddGameObject(pSpikeDoor);
	}
#pragma endregion

#pragma region 바닥 소품
	// 화톳불
	{
		DecoObject* pFireLamp = Factory::CreateObject<DecoObject>(Vec3(-1.685f, -5.99f, 9.53f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\GRANDMA_FireLamp.fbx");

		pFireLamp->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pFireLamp->GetTransform()->SetScale(Vec3(2.01f, 2.22f, 1.98f));

		AddGameObject(pFireLamp);
	}
	// 항아리 세트(입구 쪽)
	{
		// 항아리(일반)
		{
			DecoObject* pPotGeneric = Factory::CreateObject<DecoObject>(Vec3(6.065f, -5.96f, 15.33f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric->GetTransform()->SetScale(Vec3(2.01f, 2.27f, 2.01f));

			AddGameObject(pPotGeneric);
		}
		// 항아리(일반)
		{
			DecoObject* pPotGeneric2 = Factory::CreateObject<DecoObject>(Vec3(6.065f, -5.96f, 9.53f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric2->GetTransform()->SetScale(Vec3(2.01f, 2.27f, 2.01f));

			AddGameObject(pPotGeneric2);
		}
		// 항아리(폭발)
		{
			DecoObject* pPotExplode = Factory::CreateObject<DecoObject>(Vec3(6.065f, -6.14f, 12.41f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_Explode_NoLid Variant.fbx");

			pPotExplode->GetTransform()->SetScale(Vec3(1.91f, 1.91f, 1.91f));

			AddGameObject(pPotExplode);
		}
	}
	// 항아리 세트(가운데)
	{
		// 항아리(일반)
		{
			DecoObject* pPotGeneric3 = Factory::CreateObject<DecoObject>(Vec3(-1.585f, -5.96f, 1.68f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric3->GetTransform()->SetScale(Vec3(2.01f, 2.27f, 2.01f));

			AddGameObject(pPotGeneric3);
		}
		// 항아리(일반)
		{
			DecoObject* pPotGeneric4 = Factory::CreateObject<DecoObject>(Vec3(-1.585f, -5.96f, -4.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric4->GetTransform()->SetScale(Vec3(2.01f, 2.27f, 2.01f));

			AddGameObject(pPotGeneric4);
		}
		// 항아리(미믹)
		{
			DecoObject* pPotMimic = Factory::CreateObject<DecoObject>(Vec3(-1.585f, -6.19f, -1.24f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_Mimic_Magic.fbx");

			pPotMimic->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pPotMimic->GetTransform()->SetScale(Vec3(1.81f, 1.81f, 1.81f));

			SetGizmoTarget(pPotMimic);
			AddGameObject(pPotMimic);
		}
	}
	// 항아리 세트(철창 쪽)
	{
		// 항아리(일반)
		{
			DecoObject* pPotGeneric5 = Factory::CreateObject<DecoObject>(Vec3(6.065f, -5.96f, -13.47f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric5->GetTransform()->SetScale(Vec3(2.01f, 2.27f, 2.01f));

			AddGameObject(pPotGeneric5);
		}
		// 항아리(일반)
		{
			DecoObject* pPotGeneric6 = Factory::CreateObject<DecoObject>(Vec3(6.065f, -5.96f, -19.27f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric6->GetTransform()->SetScale(Vec3(2.01f, 2.27f, 2.01f));

			AddGameObject(pPotGeneric6);
		}
		// 항아리(폭발)
		{
			DecoObject* pPotExplode2 = Factory::CreateObject<DecoObject>(Vec3(6.065f, -6.14f, -16.39f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_Explode_NoLid Variant.fbx");

			pPotExplode2->GetTransform()->SetScale(Vec3(1.91f, 1.91f, 1.91f));

			AddGameObject(pPotExplode2);
		}
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
		DecoObject* pColumn4 = Factory::CreateObject<DecoObject>(Vec3(-2.67f, -2.95f, -9.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pColumn4->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		AddGameObject(pColumn4);
	}
	// 안쪽 기둥4
	{
		DecoObject* pColumn5 = Factory::CreateObject<DecoObject>(Vec3(-2.67f, -2.95f, -24.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

		pColumn5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pColumn5->GetTransform()->SetScale(Vec3(10.f, 10.8f, 10.f));

		AddGameObject(pColumn5);
	}
#pragma endregion

#pragma region 천장
	// 천장틀
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(2.04f, 2.17f, 20.51f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallRim.fbx");

		pWallRim->GetTransform()->SetScale(Vec3(10.275f, 8.9f, 7.5f));

		AddGameObject(pWallRim);
	}
	// 천장틀2
	{
		DecoObject* pWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-2.7f, 2.17f, -2.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallRim.fbx");

		pWallRim2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		pWallRim2->GetTransform()->SetScale(Vec3(45.5f, 8.9f, 7.5f));

		AddGameObject(pWallRim2);
	}
#pragma endregion

	// Toy
	/*{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Dynamic;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.2f, 0.2f, 0.2f);

		Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
		pPlayer->AddComponent(new PlayerMoveScript);
		pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		AddGameObject(pPlayer);
	}*/
}

void CorridorRightMap::Exit()
{
}
