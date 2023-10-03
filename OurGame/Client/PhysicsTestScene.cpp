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
#include "Timer.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "ObstacleObject.h"
#include "Npc.h"
#include "Monster.h"
#include "BreakablePot.h"
#include "BreakablePotCell.h"

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
#include "TestRigidBodyScript.h"
#include "PaperBurnScript.h"

/* Event */
#include "SceneChangeEvent.h"

/* Utility */
#include "ContactCallback.h"

namespace jh
{
	PhysicsTestScene::PhysicsTestScene() :
		Map(MapType::PhysicsTest),
		mpCharacterController(nullptr),
		mFilterData(nullptr),
		mFilterCallback(nullptr),
		mCCTFilterCallback(nullptr)
	{
	}

	PhysicsTestScene::~PhysicsTestScene()
	{
		//mpCharacterController->release();
	}

	void PhysicsTestScene::Initialize()
	{
		Map::Initialize();
	}

	void PhysicsTestScene::Start()
	{
		Map::Start();

		SetDirLightRotation(Vec3(40.f, 0.f, 0.f));
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
		//mFilterCallback = gpEngine->GetPhysics()->GetCallback();
		//const PxControllerFilters filter(mFilterData, mFilterCallback, mCCTFilterCallback);
		//
		//PxVec3 disp = PLAYER->GetRigidBody()->GetVelocity();
		//disp.y = -9.8f;
		//const PxU32 flags = mpCharacterController->move(disp * DELTA_TIME, 0.f, DELTA_TIME, filter);

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
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Obstacle);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Obstacle, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::PotCell);

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

		//1층 계단 - Stairs
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.f, 0.1f, 14.f);

			Ground* pStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-12.f, -5.2f, 0.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

			pStairs->GetTransform()->SetScale(Vec3(15.f, 15.f, 15.f));
			pStairs->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
			pStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 1.f));
			pStairs->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));
			AddGameObject(pStairs);
		}

		// Toy
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Character;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(1.5f, 0.4f, 1.5f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->AddComponent(new PaperBurnScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));
			pPlayer->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.6f, 0.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

			mpCharacterController = pPlayer->GetRigidBody()->GetCharacterController();

			AddGameObject(pPlayer);
		}*/

		// CharacterController
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Character;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(1.5f, 0.4f, 1.5f);

			CctPlayer* pCctPlayer = Factory::CreateObjectHasPhysical<CctPlayer>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred");

			AddGameObject(pCctPlayer);
		}*/

		// AddForce 테스트용 Dynamic 오브젝트
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 3.1f, 2.f);

			ObstacleObject* testPot = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-5.f, -0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\POT_HEAL_Generic Variant (3).fbx");

			testPot->GetTransform()->SetScale(Vec3(2.87f, 3.1f, 2.87f));

			testPot->AddComponent(new TestRigidBodyScript);

			AddGameObject(testPot);
		}*/

#pragma region 항아리 조각
		std::vector<BreakablePotCell*> vpPotCells = {};

		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Dynamic;
		physicsInfo.eGeometryType = GeometryType::Convex;
		//physicsInfo.massProperties.staticFriction = 1.f;
		physicsInfo.massProperties.dynamicFriction = 0.f;
		physicsInfo.massProperties.restitution = 0.f;

		// 항아리 조각 1
		{
			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.6f, -5.4f, -0.8f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell1.fbx");

			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.6f, -2.2f, -0.8f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 3
		{
			physicsInfo.size = Vec3(1.11f, 1.11f, 1.11f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(4.57f, -4.25f, 0.13f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell3.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.11f, 1.11f, 1.11f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(-0.43f, -1.05f, 0.13f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 4
		{
			physicsInfo.size = Vec3(1.276f, 1.276f, 1.276f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(4.81f, -3.43f, -0.11f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell4.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.276f, 1.276f, 1.276f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(-0.19f, -0.23f, -0.11f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 6
		{
			physicsInfo.size = Vec3(0.99f, 0.99f, 0.99f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(4.766f, -2.755f, 0.18f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell6.fbx");

			potCell->GetTransform()->SetScale(Vec3(0.99f, 0.99f, 0.99f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(-0.234f, 0.445f, 0.18f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 7
		{
			physicsInfo.size = Vec3(1.3f, 1.3f, 1.3f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.63f, -3.86f, -0.05f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell7.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.3f, 1.3f, 1.3f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.63f, -0.66f, -0.05f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 8
		{
			physicsInfo.size = Vec3(1.22f, 1.22f, 1.22f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(4.85f, -3.35f, 0.34f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell8.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.22f, 1.22f, 1.22f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(-0.15f, -0.15f, 0.34f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 9
		{
			physicsInfo.size = Vec3(0.8f, 0.8f, 0.8f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.34f, -4.308f, 0.35f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell9.fbx");

			potCell->GetTransform()->SetScale(Vec3(0.8f, 0.8f, 0.8f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.34f, -1.108f, 0.35f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 10
		{
			physicsInfo.size = Vec3(0.87f, 0.87f, 0.87f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(4.81f, -2.72f, -0.4f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell10.fbx");

			potCell->GetTransform()->SetScale(Vec3(0.87f, 0.87f, 0.87f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(-0.19f, 0.48f, -0.4f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 11
		{
			physicsInfo.size = Vec3(1.326f, 1.326f, 1.326f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.36f, -2.89f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell11.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.326f, 1.326f, 1.326f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.36f, 0.31f, 0.f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 12
		{
			physicsInfo.size = Vec3(1.179f, 1.179f, 1.179f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.01f, -4.226f, 0.596f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell12.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.179f, 1.179f, 1.179f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.01f, -1.026f, 0.596f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 16
		{
			physicsInfo.size = Vec3(0.96f, 0.96f, 0.96f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.08f, -3.68f, -0.565f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell16.fbx");

			potCell->GetTransform()->SetScale(Vec3(0.96f, 0.96f, 0.96f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.08f, -0.48f, -0.565f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 17
		{
			physicsInfo.size = Vec3(1.26f, 1.26f, 1.26f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.f, -3.89f, 0.605f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell17.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.26f, 1.26f, 1.26f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(0.f, -0.69f, 0.605f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 조각 18
		{
			physicsInfo.size = Vec3(1.37f, 1.37f, 1.37f);

			BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(4.835f, -4.08f, -0.485f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell18.fbx");

			potCell->GetTransform()->SetScale(Vec3(1.37f, 1.37f, 1.37f));
			potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potCell->SetRelativePos(Vec3(-0.165f, -0.88f, -0.485f));

			AddGameObject(potCell);
			vpPotCells.push_back(potCell);
		}
		// 항아리 뚜껑
		{
			physicsInfo.size = Vec3(1.33f, 1.33f, 1.33f);

			BreakablePotCell* potTap = Factory::CreateObjectHasPhysical<BreakablePotCell>(Vec3(5.025f, -2.15f, -0.015f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Tap.fbx");

			potTap->GetTransform()->SetScale(Vec3(1.33f, 1.33f, 1.33f));
			potTap->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
			potTap->SetRelativePos(Vec3(0.025f, 1.05f, -0.015f));

			AddGameObject(potTap);
			vpPotCells.push_back(potTap);
		}
		// 원본 항아리(깨지기 전 모습)
		//Vec3(-0.3f, 1.1f, 0.4f);
		DecoObject* pBasePot = Factory::CreateObject<DecoObject>(Vec3(5.f, -3.2f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Pots\\OrgPot.fbx");

		pBasePot->GetTransform()->SetScale(Vec3(3.15f, 2.85f, 3.15f));

		AddGameObject(pBasePot);

		PhysicsInfo basePhysicsInfo;
		basePhysicsInfo.eActorType = ActorType::Kinematic;
		basePhysicsInfo.eGeometryType = GeometryType::Box;
		basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

		BreakablePot* pBreakPot = Factory::CreateObjectHasPhysical<BreakablePot>(Vec3(5.f, -3.2f, 0.f), basePhysicsInfo, L"Deferred", L"", false, pBasePot, vpPotCells);

		AddGameObject(pBreakPot);

#pragma endregion
	}

	void PhysicsTestScene::Exit()
	{
	}

	void PhysicsTestScene::CreateCharacterController()
	{
		PxCapsuleControllerDesc desc;
		desc.climbingMode = PxCapsuleClimbingMode::eEASY;
		desc.height = 10.f;
		desc.radius = 1.5f;
		desc.stepOffset = 0.5f;
		//desc.material = 
		desc.behaviorCallback = gpEngine->GetPhysics()->GetCallback();
		desc.reportCallback = gpEngine->GetPhysics()->GetCallback();

		//PxBoxControllerDesc desc;
		//desc.halfHeight = 2.f;
		//desc.halfForwardExtent = 1.f;
		//desc.halfSideExtent = 1.f;
		//desc.

		if (true == desc.isValid())
			int a = 0;

		mpCharacterController = static_cast<PxCapsuleController*>(gpEngine->GetPhysics()->GetControllerManager()->createController(desc));
	}
}