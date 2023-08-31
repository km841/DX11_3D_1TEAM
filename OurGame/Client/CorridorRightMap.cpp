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

namespace jh
{
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
			DecoObject* pWall = Factory::CreateObject<DecoObject>(Vec3(0.00f, 0.00f, 0.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor.fbx");

			pWall->GetTransform()->SetScale(Vec3(65.00f, 65.00f, 65.00f));
			pWall->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"crWallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor.fbm\\grandmaWallPaperTexture.png");
			pWall->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			pWall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.3f, 0.3f));


			AddGameObject(pWall);
		}
		// 숨겨진 벽
		{
			DecoObject* pWallSecret = Factory::CreateObject<DecoObject>(Vec3(2.60f, -2.86f, 26.59f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\SecretWoodDoor.fbx");

			pWallSecret->GetTransform()->SetScale(Vec3(11.57f, 11.31f, 1.30f));
			pWallSecret->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pWallSecret);
		}
		// 문틀
		{
			DecoObject* pDoorFrame = Factory::CreateObject<DecoObject>(Vec3(-3.38f, -5.46f, 19.18f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\doorSideFrame.fbx");

			pDoorFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pDoorFrame->GetTransform()->SetScale(Vec3(7.58f, 7.67f, 4.81f));

			AddGameObject(pDoorFrame);
		}
		// 문틀2
		{
			DecoObject* pDoorFrame2 = Factory::CreateObject<DecoObject>(Vec3(-3.38f, -5.46f, -23.66f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\doorSideFrame.fbx");

			pDoorFrame2->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pDoorFrame2->GetTransform()->SetScale(Vec3(7.58f, 7.67f, 4.81f));

			AddGameObject(pDoorFrame2);
		}
#pragma endregion

#pragma region 벽 장식
		// 커튼
		{
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(2.60f, 0.14f, 25.48f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(11.21f, 15.60f, 13.13f));

			AddGameObject(pCurtainHorizontal);
		}
		// 커튼2
		{
			DecoObject* pCurtainHorizontal2 = Factory::CreateObject<DecoObject>(Vec3(-2.34f, 0.14f, 17.68f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal2->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pCurtainHorizontal2->GetTransform()->SetScale(Vec3(16.47f, 15.60f, 13.13f));

			AddGameObject(pCurtainHorizontal2);
		}
		// 커튼3
		{
			DecoObject* pCurtainHorizontal3 = Factory::CreateObject<DecoObject>(Vec3(-2.34f, 0.14f, -21.97f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal3->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pCurtainHorizontal3->GetTransform()->SetScale(Vec3(18.76f, 15.60f, 13.13f));

			AddGameObject(pCurtainHorizontal3);
		}
		// 그림
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-3.43f, -1.81f, -1.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame.fbx");

			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pPaintingFrame->GetTransform()->SetScale(Vec3(5.39f, 5.95f, 7.44f));

			AddGameObject(pPaintingFrame);
		}
		// 그림2(왼쪽)
		{
			DecoObject* pPaintingFrame2Left = Factory::CreateObject<DecoObject>(Vec3(-3.43f, -5.00f, -5.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame2.fbx");

			pPaintingFrame2Left->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pPaintingFrame2Left->GetTransform()->SetScale(Vec3(2.67f, 2.68f, 1.49f));

			AddGameObject(pPaintingFrame2Left);
		}
		// 그림2(오른쪽)
		{
			DecoObject* pPaintingFrame2Right = Factory::CreateObject<DecoObject>(Vec3(-3.43f, -0.12f, 4.72f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame2.fbx");

			pPaintingFrame2Right->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pPaintingFrame2Right->GetTransform()->SetScale(Vec3(2.67f, 2.68f, 1.49f));

			AddGameObject(pPaintingFrame2Right);
		}
		// 그림3
		{
			DecoObject* pPaintingFrame3 = Factory::CreateObject<DecoObject>(Vec3(-3.43f, -1.03f, -8.52f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame3.fbx");

			pPaintingFrame3->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pPaintingFrame3->GetTransform()->SetScale(Vec3(4.40f, 5.10f, 2.22f));

			AddGameObject(pPaintingFrame3);
		}
		// 그림4
		{
			DecoObject* pPaintingFrame4 = Factory::CreateObject<DecoObject>(Vec3(-3.36f, -4.84f, 2.38f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\paintingFrame4.fbx");

			pPaintingFrame4->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pPaintingFrame4->GetTransform()->SetScale(Vec3(4.84f, 5.26f, 6.65f));

			AddGameObject(pPaintingFrame4);
		}
#pragma endregion

#pragma region 바닥
		// 바닥
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(13.00f, 0.65f, 13.00f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.00f, -9.23f, -2.85f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor-detach.fbx");

			pFloor->GetTransform()->SetScale(Vec3(59.41f, 1.30f, 59.28f));
			pFloor->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pFloor);
		}
		// 바깥쪽 바닥틀
		{
			DecoObject* pFloorRimBig = Factory::CreateObject<DecoObject>(Vec3(2.91f, -9.75f, -3.46f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\wallPanel (3)-Merged (4).fbx");

			pFloorRimBig->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
			pFloorRimBig->GetTransform()->SetScale(Vec3(59.80f, 56.68f, 58.76f));

			AddGameObject(pFloorRimBig);
		}
		// 안쪽 바닥틀
		{
			DecoObject* pFloorRim = Factory::CreateObject<DecoObject>(Vec3(2.91f, -9.36f, 26.70f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

			pFloorRim->GetTransform()->SetScale(Vec3(13.00f, 5.20f, 5.20f));

			AddGameObject(pFloorRim);
		}
		// 안쪽 바닥틀2
		{
			DecoObject* pFloorRim2 = Factory::CreateObject<DecoObject>(Vec3(-3.59f, -9.36f, 27.87f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

			pFloorRim2->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pFloorRim2->GetTransform()->SetScale(Vec3(12.35f, 5.20f, 5.20f));

			AddGameObject(pFloorRim2);
		}
		// 안쪽 바닥틀3
		{
			DecoObject* pFloorRim3 = Factory::CreateObject<DecoObject>(Vec3(-3.59f, -9.36f, -2.16f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

			pFloorRim3->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pFloorRim3->GetTransform()->SetScale(Vec3(37.89f, 5.20f, 5.20f));

			AddGameObject(pFloorRim3);
		}
		// 안쪽 바닥틀4
		{
			DecoObject* pFloorRim4 = Factory::CreateObject<DecoObject>(Vec3(-3.59f, -9.36f, -29.20f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallPanel (14).fbx");

			pFloorRim4->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pFloorRim4->GetTransform()->SetScale(Vec3(6.17f, 5.20f, 5.20f));

			AddGameObject(pFloorRim4);
		}
		// 철창
		{
			DecoObject* pSpikeDoor = Factory::CreateObject<DecoObject>(Vec3(-3.98f, -7.54f, -23.67f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\SpikeDoor.fbx");

			pSpikeDoor->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
			pSpikeDoor->GetTransform()->SetScale(Vec3(6.17f, 6.37f, 6.30f));

			AddGameObject(pSpikeDoor);
		}
#pragma endregion

#pragma region 바닥 소품
		// 화톳불
		{
			DecoObject* pFireLamp = Factory::CreateObject<DecoObject>(Vec3(-2.19f, -7.79f, 12.39f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\GRANDMA_FireLamp.fbx");

			pFireLamp->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
			pFireLamp->GetTransform()->SetScale(Vec3(2.61f, 2.89f, 2.57f));

			AddGameObject(pFireLamp);
		}
		// 항아리 세트(입구 쪽)
		{
			// 항아리(일반)
			{
				DecoObject* pPotGeneric = Factory::CreateObject<DecoObject>(Vec3(7.88f, -7.75f, 19.93f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

				pPotGeneric->GetTransform()->SetScale(Vec3(2.61f, 2.95f, 2.61f));

				AddGameObject(pPotGeneric);
			}
			// 항아리(일반)
			{
				DecoObject* pPotGeneric2 = Factory::CreateObject<DecoObject>(Vec3(7.88f, -7.75f, 12.39f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

				pPotGeneric2->GetTransform()->SetScale(Vec3(2.61f, 2.95f, 2.61f));

				AddGameObject(pPotGeneric2);
			}
			// 항아리(폭발)
			{
				DecoObject* pPotExplode = Factory::CreateObject<DecoObject>(Vec3(7.88f, -7.98f, 16.13f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_Explode_NoLid Variant.fbx");

				pPotExplode->GetTransform()->SetScale(Vec3(2.48f, 2.48f, 2.48f));

				AddGameObject(pPotExplode);
			}
		}
		// 항아리 세트(가운데)
		{
			// 항아리(일반)
			{
				DecoObject* pPotGeneric3 = Factory::CreateObject<DecoObject>(Vec3(-2.06f, -7.75f, 2.18f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

				pPotGeneric3->GetTransform()->SetScale(Vec3(2.61f, 2.95f, 2.61f));

				AddGameObject(pPotGeneric3);
			}
			// 항아리(일반)
			{
				DecoObject* pPotGeneric4 = Factory::CreateObject<DecoObject>(Vec3(-2.06f, -7.75f, -5.36f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

				pPotGeneric4->GetTransform()->SetScale(Vec3(2.61f, 2.95f, 2.61f));

				AddGameObject(pPotGeneric4);
			}
			// 항아리(미믹)
			{
				DecoObject* pPotMimic = Factory::CreateObject<DecoObject>(Vec3(-2.06f, -8.05f, -1.61f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_Mimic_Magic.fbx");

				pPotMimic->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				pPotMimic->GetTransform()->SetScale(Vec3(2.35f, 2.35f, 2.35f));

				SetGizmoTarget(pPotMimic);
				AddGameObject(pPotMimic);
			}
		}
		// 항아리 세트(철창 쪽)
		{
			// 항아리(일반)
			{
				DecoObject* pPotGeneric5 = Factory::CreateObject<DecoObject>(Vec3(7.88f, -7.75f, -17.51f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

				pPotGeneric5->GetTransform()->SetScale(Vec3(2.61f, 2.95f, 2.61f));

				AddGameObject(pPotGeneric5);
			}
			// 항아리(일반)
			{
				DecoObject* pPotGeneric6 = Factory::CreateObject<DecoObject>(Vec3(7.88f, -7.75f, -25.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_HEAL_Generic Variant (3).fbx");

				pPotGeneric6->GetTransform()->SetScale(Vec3(2.61f, 2.95f, 2.61f));

				AddGameObject(pPotGeneric6);
			}
			// 항아리(폭발)
			{
				DecoObject* pPotExplode2 = Factory::CreateObject<DecoObject>(Vec3(7.88f, -7.98f, -21.31f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\POT_Explode_NoLid Variant.fbx");

				pPotExplode2->GetTransform()->SetScale(Vec3(2.48f, 2.48f, 2.48f));

				AddGameObject(pPotExplode2);
			}
		}
#pragma endregion

#pragma region 기둥
		// 바깥쪽 기둥
		{
			DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(8.58f, -3.84f, 26.52f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

			pColumn->GetTransform()->SetScale(Vec3(13.00f, 14.04f, 13.00f));

			AddGameObject(pColumn);
		}
		// 안쪽 기둥
		{
			DecoObject* pColumn2 = Factory::CreateObject<DecoObject>(Vec3(-3.51f, -3.84f, 26.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

			pColumn2->GetTransform()->SetScale(Vec3(13.00f, 14.04f, 13.00f));

			AddGameObject(pColumn2);
		}
		// 안쪽 기둥2
		{
			DecoObject* pColumn3 = Factory::CreateObject<DecoObject>(Vec3(-3.47f, -3.84f, 8.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

			pColumn3->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pColumn3->GetTransform()->SetScale(Vec3(13.00f, 14.04f, 13.00f));

			AddGameObject(pColumn3);
		}
		// 안쪽 기둥3
		{
			DecoObject* pColumn4 = Factory::CreateObject<DecoObject>(Vec3(-3.47f, -3.84f, -11.70f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

			pColumn4->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pColumn4->GetTransform()->SetScale(Vec3(13.00f, 14.04f, 13.00f));

			AddGameObject(pColumn4);
		}
		// 안쪽 기둥4
		{
			DecoObject* pColumn5 = Factory::CreateObject<DecoObject>(Vec3(-3.47f, -3.84f, -31.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\ColumnFull (13).fbx");

			pColumn5->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pColumn5->GetTransform()->SetScale(Vec3(13.00f, 14.04f, 13.00f));

			AddGameObject(pColumn5);
		}
#pragma endregion

#pragma region 천장
		// 천장틀
		{
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(2.65f, 2.82f, 26.66f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(13.36f, 11.57f, 9.75f));

			AddGameObject(pWallRim);
		}
		// 천장틀2
		{
			DecoObject* pWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-3.51f, 2.82f, -2.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\WallRim.fbx");

			pWallRim2->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			pWallRim2->GetTransform()->SetScale(Vec3(59.15f, 11.57f, 9.75f));

			AddGameObject(pWallRim2);
		}
#pragma endregion

		// Toy
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

			AddGameObject(pPlayer);
		}
	}

	void CorridorRightMap::Exit()
	{
	}
}
