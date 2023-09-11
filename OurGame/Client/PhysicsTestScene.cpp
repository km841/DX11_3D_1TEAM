#include "pch.h"
#include "PhysicsTestScene.h"
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

namespace jh
{
	PhysicsTestScene::PhysicsTestScene() :
		Map(MapType::PhysicsTest)
	{
	}

	PhysicsTestScene::~PhysicsTestScene()
	{
	}

	void PhysicsTestScene::Initialize()
	{
		Map::Initialize();
	}

	void PhysicsTestScene::Start()
	{
		Map::Start();
	}

	void PhysicsTestScene::Update()
	{
		Map::Update();
	}

	void PhysicsTestScene::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void PhysicsTestScene::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void PhysicsTestScene::Render()
	{
		Map::Render();
	}

	void PhysicsTestScene::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		//배경맵 하얀색으로 만들어주는 코드
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

#pragma region 벽
		// 벽
		{
			DecoObject* pWall = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\R_RightSecretPassage.fbx");

			pWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pWall->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));

			//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"crWallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\R_RightSecretPassage.fbm\\Wood_PlankBoard_Var1.png");
			//pWall->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			//pWall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.3f, 0.3f));

			AddGameObject(pWall);
		}
#pragma endregion

#pragma region 바닥
		// 바닥
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 1.f, 30.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -5.13f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\Floor.fbx");

			pFloor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pFloor->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));

			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"rspFloorTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\Floor.fbm\\grandmaFloorNewTestWhiteIsh.png");
			pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture, 2);
			pFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f), 1);

			AddGameObject(pFloor);
		}
#pragma endregion

#pragma region 기둥
		// 기둥
		{
			DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(13.85f, -0.4f, 8.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\ColumnOuterCorner.fbx");

			pColumn->GetTransform()->SetScale(Vec3(11.58f, 11.58f, 11.58f));

			AddGameObject(pColumn);
		}
		// 기둥2
		{
			DecoObject* pColumn2 = Factory::CreateObject<DecoObject>(Vec3(-14.55f, -0.4f, 8.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\ColumnOuterCorner.fbx");

			pColumn2->GetTransform()->SetScale(Vec3(11.58f, 11.58f, 11.58f));

			AddGameObject(pColumn2);
		}
		// 기둥3
		{
			DecoObject* pColumn3 = Factory::CreateObject<DecoObject>(Vec3(-14.55f, -0.4f, -11.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\ColumnOuterCorner.fbx");

			pColumn3->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pColumn3->GetTransform()->SetScale(Vec3(11.58f, 11.58f, 11.58f));

			AddGameObject(pColumn3);
		}
#pragma endregion

#pragma region 바닥틀
		// 짧은 바닥틀(바깥쪽)
		{
			DecoObject* pFloorRimOutsideShort = Factory::CreateObject<DecoObject>(Vec3(-12.15f, -5.23f, -12.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\EdgeLeft.fbx");

			pFloorRimOutsideShort->GetTransform()->SetScale(Vec3(2.6f, 2.6f, 2.f));

			AddGameObject(pFloorRimOutsideShort);
		}
		// 긴 바닥틀(바깥쪽)
		{
			DecoObject* pFloorRimOutsideLong = Factory::CreateObject<DecoObject>(Vec3(4.53f, -5.23f, -2.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\EdgeCorner.fbx");

			pFloorRimOutsideLong->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pFloorRimOutsideLong->GetTransform()->SetScale(Vec3(21.3f, 21.f, 20.25f));

			AddGameObject(pFloorRimOutsideLong);
		}
		// 바닥틀(안쪽)
		{
			DecoObject* pFloorRimInside = Factory::CreateObject<DecoObject>(Vec3(8.23f, -4.33f, 8.82f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\WallPanel (2).fbx");

			pFloorRimInside->GetTransform()->SetScale(Vec3(10.5f, 8.4f, 11.f));

			AddGameObject(pFloorRimInside);
		}
		// 바닥틀(안쪽)2
		{
			DecoObject* pFloorRimInside2 = Factory::CreateObject<DecoObject>(Vec3(-7.77f, -4.33f, 8.82f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\WallPanel (2).fbx");

			pFloorRimInside2->GetTransform()->SetScale(Vec3(12.f, 8.4f, 11.f));

			AddGameObject(pFloorRimInside2);
		}
		// 바닥틀(안쪽)3
		{
			DecoObject* pFloorRimInside3 = Factory::CreateObject<DecoObject>(Vec3(-14.57f, -4.33f, -1.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\WallPanel (2).fbx");

			pFloorRimInside3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pFloorRimInside3->GetTransform()->SetScale(Vec3(20.4f, 8.4f, 11.f));

			AddGameObject(pFloorRimInside3);
		}
#pragma endregion

#pragma region 천장틀
		// 천장틀
		{
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-0.35f, 4.57f, 8.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(26.52f, 11.f, 11.f));

			AddGameObject(pWallRim);
		}
		// 천장틀2
		{
			DecoObject* pWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-14.65f, 4.57f, -1.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\WallRim.fbx");

			pWallRim2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pWallRim2->GetTransform()->SetScale(Vec3(21.f, 11.f, 11.f));

			AddGameObject(pWallRim2);
		}
#pragma endregion

#pragma region 문틀+거미줄
		// 문틀
		{
			DecoObject* pDoorFrame = Factory::CreateObject<DecoObject>(Vec3(0.65f, -1.45f, 8.82f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\DoorFrameBig (1).fbx");

			pDoorFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pDoorFrame->GetTransform()->SetScale(Vec3(6.3f, 7.f, 7.7f));

			AddGameObject(pDoorFrame);
		}
		// 거미줄(구석)
		{
			DecoObject* pCobwebCorner = Factory::CreateObject<DecoObject>(Vec3(-13.05f, -2.95f, 7.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\Cobweb1.fbx");

			pCobwebCorner->GetTransform()->SetRotation(Vec3(90.f, -90.f, 0.f));
			pCobwebCorner->GetTransform()->SetScale(Vec3(3.f, 3.32f, 3.33f));

			AddGameObject(pCobwebCorner);
		}
		// 거미줄(문)
		{
			DecoObject* pCobwebDoor = Factory::CreateObject<DecoObject>(Vec3(0.55f, -0.05f, 8.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\Cobweb_Flat.fbx");

			pCobwebDoor->GetTransform()->SetRotation(Vec3(90.f, -90.f, 0.f));
			pCobwebDoor->GetTransform()->SetScale(Vec3(3.f, 8.4f, 9.27f));

			AddGameObject(pCobwebDoor);
		}
#pragma endregion

#pragma region 투명벽
		// 동쪽
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 15.f, 30.f);

			WallObject* pEastWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(15.f, 0.f, 0.f), info, L"Deferred");
			pEastWall->SetName(L"EastWall");

			pEastWall->GetTransform()->SetScale(Vec3(1.f, 15.f, 30.f));

			AddGameObject(pEastWall);
		}
		// 서쪽
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 15.f, 30.f);

			WallObject* pWestWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-15.f, 0.f, 0.f), info, L"Deferred");
			pWestWall->SetName(L"WestWall");

			pWestWall->GetTransform()->SetScale(Vec3(1.f, 15.f, 30.f));

			AddGameObject(pWestWall);
		}
		// 남쪽
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 15.f, 1.f);

			WallObject* pSouthWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(0.f, 0.f, -13.2f), info, L"Deferred");
			pSouthWall->SetName(L"SouthWall");

			pSouthWall->GetTransform()->SetScale(Vec3(30.f, 15.f, 1.f));

			//SetGizmoTarget(pSouthWall);
			AddGameObject(pSouthWall);
		}
		// 북쪽(거미줄 문쪽)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 15.f, 1.f);

			WallObject* pNorthWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(0.f, 0.f, 9.5f), info, L"Deferred");
			pNorthWall->SetName(L"NorthWall");

			pNorthWall->GetTransform()->SetScale(Vec3(30.f, 15.f, 1.f));

			AddGameObject(pNorthWall);
		}
#pragma endregion

		// Toy
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

			pPlayer->GetRigidBody()->ApplyGravity();			
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

			AddGameObject(pPlayer);
		}
	}

	void PhysicsTestScene::Exit()
	{
	}
}