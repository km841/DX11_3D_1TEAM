#include "pch.h"
#include "MainOfficeMap.h"
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
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "Elevator.h"
#include "TeleportZone.h"
#include "SoulDoor.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "CinematicCamMove.h"

/* Event */
#include "SceneChangeEvent.h"


namespace yj
{
	MainOfficeMap::MainOfficeMap()
		: Map(MapType::MainOfficeMap)
		,eTarget(nullptr)
		,pBus(nullptr)
	{
	}

	MainOfficeMap::~MainOfficeMap()
	{
	}

	void MainOfficeMap::Initialize()
	{
		Map::Initialize();
		
#pragma endregion
	}

	void MainOfficeMap::Update()
	{
		Map::Update();
	}

	void MainOfficeMap::Start()
	{
		Map::Start();
	}

	void MainOfficeMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void MainOfficeMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void MainOfficeMap::Render()
	{
		Map::Render();
	}

	void MainOfficeMap::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::DecoObject);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Portal);

		gpEngine->SetSwapChainRTVClearColor(Vec4(100.f, 100.f, 100.f, 255.f));
		
		InitObjectAdd();

		GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 1,
			nullptr , std::bind(&MainOfficeMap::InitBusStart, this));
	}
	
	void MainOfficeMap::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);   
	}


	void MainOfficeMap::InitObjectAdd()
	{
		// Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.0f, 0.0f, 0.0f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->AddComponent(new PaperBurnScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			
			PLAYER->SetDontDestroyObject(L"Player");
		}

		{
			/*	CinematicCamMove* pCinematicCam = Factory::CreateObject<CinematicCamMove>(Vec3::Zero, L"Deferred", L"");
				AddGameObject(pCinematicCam);*/
				//원래는 모노비헤이비어로 Script로 붙여야하나 Cam에 붙이는거라 무슨 일이 일어날지를 모르니 잠시만 이런 형식으로

		}

		{
			pBus = Factory::CreateObject<Bus>(Vec3(-17.0f, -8.0f, 33.0f), L"Deferred",
				L"..\\Resources\\FBX\\Map\\MainOfficeMap\\CUTSCENE_Bus.fbx");
			pBus->GetTransform()->SetScale(Vec3(50.0f, 50.0f, 50.0f));

			AddGameObject(pBus);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Mesh;
			physicsInfo.size = Vec3(49.f, 49.f, 49.f);

			Ground* pFrontGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.4f, -5.5f, -0.5f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\uv1.fbx");
			pFrontGround->GetTransform()->SetScale(Vec3(49.0f, 49.0f, 49.0f));

			AddGameObject(pFrontGround);
		}

		{
			Ground* pREFLECTIONS = Factory::CreateObject<Ground>(Vec3(5.5f, -9.0f, -1.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Floor_REFLECTIONS.fbx");
			pREFLECTIONS->GetTransform()->SetScale(Vec3(40, 40, 40));
			pREFLECTIONS->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));
			AddGameObject(pREFLECTIONS);
		}

		{
			Ground* pUpstair = Factory::CreateObject<Ground>(Vec3(9.5f, 3.0f, -5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Upstairs.fbx");
			pUpstair->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));

			AddGameObject(pUpstair);
		}

		{
			/*Ground* pColliders = Factory::CreateObject<Ground>(Vec3(9.5f, 3.0f, -5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Colliders.fbx");
			pColliders->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));*/

			//AddGameObject(pColliders);
		}

		{
			Ground* pStair_Single5 = Factory::CreateObject<Ground>(Vec3(29.5f, 3.5f, 8.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HoD_Stairs_Single.fbx");
			pStair_Single5->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));
			AddGameObject(pStair_Single5);
		}

		{
			Ground* pGrandmaDoorFence = Factory::CreateObject<Ground>(Vec3(61.0f, 12.5f, 23.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\GrandmaDoorsFence.fbx");
			pGrandmaDoorFence->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));
			pGrandmaDoorFence->GetTransform()->SetRotation(Vec3(0.0f, -10.0f, 0.0f));
			AddGameObject(pGrandmaDoorFence);
		}

		{
			Ground* pBusStop = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\stairsIsland.fbx");
			pBusStop->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pBusStop->GetTransform()->SetRotation(Vec3(0.0f, -160.0f, 0.0f));
			pBusStop->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.04f, 0.04f));
			//x65444eedccdew
			AddGameObject(pBusStop);
		}

#pragma region 사무실 책상 리스트
		{
			std::vector<GameObject*> deskList;
			for (int i = 0; i < 9; i++)
			{

				Ground* pDesk = Factory::CreateObject<Ground>(Vec3::Zero, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Desk.fbx");
				AddGameObject(pDesk);
				deskList.push_back(pDesk);
			}
			deskList[0]->GetTransform()->SetPosition(Vec3(-0.5f, -8.0f, 2.0f));
			deskList[0]->GetTransform()->SetRotation(Vec3(-0.0f, -23.0f, 0.0f));
			deskList[0]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[1]->GetTransform()->SetPosition(Vec3(3.0f, -8.0f, -1.5f));
			deskList[1]->GetTransform()->SetRotation(Vec3(-0.0f, -23.0f, 0.0f));
			deskList[1]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[2]->GetTransform()->SetPosition(Vec3(7.0f, -8.0f, -5.0f));
			deskList[2]->GetTransform()->SetRotation(Vec3(-0.0f, -23.0f, 0.0f));
			deskList[2]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[3]->GetTransform()->SetPosition(Vec3(14.0f, -8.0f, 0.5f));
			deskList[3]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			deskList[3]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[4]->GetTransform()->SetPosition(Vec3(12.9f, -8.0f, 4.9f));
			deskList[4]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			deskList[4]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[5]->GetTransform()->SetPosition(Vec3(11.6f, -8.0f, 9.5f));
			deskList[5]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			deskList[5]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[6]->GetTransform()->SetPosition(Vec3(-6.8f, -8.0f, -10.2f));
			deskList[6]->GetTransform()->SetRotation(Vec3(0.0f, -57.0f, 0.0f));
			deskList[6]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[7]->GetTransform()->SetPosition(Vec3(-1.4f, -8.0f, -11.0f));
			deskList[7]->GetTransform()->SetRotation(Vec3(0.0f, -57.0f, 0.0f));
			deskList[7]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[8]->GetTransform()->SetPosition(Vec3(3.59f, -8.0f, -11.4f));
			deskList[8]->GetTransform()->SetRotation(Vec3(0.0f, -65.0f, 0.0f));
			deskList[8]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));
		}
#pragma endregion


#pragma region 사무실 의자 리스트

		std::vector<GameObject*> chairList;

		for (int i = 0; i < 9; i++)
		{
			Ground* pChair = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\ChairBaseMerged.fbx");
			pChair->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pChair->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pChair);
			chairList.push_back(pChair);
		}
		chairList[0]->GetTransform()->SetPosition(Vec3(0.2f, -7.9f, 0.5f));
		chairList[0]->GetTransform()->SetRotation(Vec3(-0.0f, 79.0, 0.0f));
		chairList[0]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[1]->GetTransform()->SetPosition(Vec3(4.5f, -7.9f, -2.7f));
		chairList[1]->GetTransform()->SetRotation(Vec3(0.0f, 36.0, 0.0f));
		chairList[1]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[2]->GetTransform()->SetPosition(Vec3(8.1f, -7.9f, -6.1f));
		chairList[2]->GetTransform()->SetRotation(Vec3(0.0f, 37.0, 0.0f));
		chairList[2]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[3]->GetTransform()->SetPosition(Vec3(13.6f, -7.9f, 1.5f));
		chairList[3]->GetTransform()->SetRotation(Vec3(0.0f, 223.0f, 0.0f));
		chairList[3]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[4]->GetTransform()->SetPosition(Vec3(12.3f, -7.9f, 6.1f));
		chairList[4]->GetTransform()->SetRotation(Vec3(0.0f, 243.0f, 0.0f));
		chairList[4]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[5]->GetTransform()->SetPosition(Vec3(12.3f, -7.9f, 8.5f));
		chairList[5]->GetTransform()->SetRotation(Vec3(0.0f, 52.0f, 0.0f));
		chairList[5]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[6]->GetTransform()->SetPosition(Vec3(5.1f, -7.9f, -11.4f));
		chairList[6]->GetTransform()->SetRotation(Vec3(0.0f, 1.0f, 0.0f));
		chairList[6]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[7]->GetTransform()->SetPosition(Vec3(-2.6f, -7.9f, -11.1f));
		chairList[7]->GetTransform()->SetRotation(Vec3(0.0f, 171.0f, 0.0f));
		chairList[7]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[8]->GetTransform()->SetPosition(Vec3(-5.1f, -7.9f, -10.5f));
		chairList[8]->GetTransform()->SetRotation(Vec3(0.0f, -6.0f, 0.0f));
		chairList[8]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

#pragma endregion


#pragma region "laterWallList"


		std::vector<GameObject*>laterWallList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pLateralWall = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\LateralWall.fbx");
			pLateralWall->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pLateralWall->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pLateralWall);
			laterWallList.push_back(pLateralWall);
		}
		laterWallList[0]->GetTransform()->SetPosition(Vec3(11.7f, -4.3f, -15.5f));
		laterWallList[0]->GetTransform()->SetRotation(Vec3(0.0f, 4.0f, 0.0f));

		laterWallList[1]->GetTransform()->SetPosition(Vec3(21.0f, -4.4f, -6.8f));
		laterWallList[1]->GetTransform()->SetRotation(Vec3(0.0f, -86.0f, 0.0f));
#pragma endregion


#pragma region "WallSlots"



		std::vector<GameObject*>wallSlotList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pWallSlots = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\WallSlots.fbx");
			pWallSlots->GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));
			pWallSlots->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pWallSlots);
			wallSlotList.push_back(pWallSlots);
		}
		wallSlotList[0]->GetTransform()->SetPosition(Vec3(0.3f, -4.6f, -15.9f));
		wallSlotList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		wallSlotList[0]->GetTransform()->SetScale(Vec3(14.0f, 14.0f, 14.0f));

		wallSlotList[1]->GetTransform()->SetPosition(Vec3(21.4f, -4.6f, 4.6f));
		wallSlotList[1]->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		wallSlotList[1]->GetTransform()->SetScale(Vec3(14.0f, 14.0f, 14.0f));



#pragma endregion


#pragma region "WallColumns"

		std::vector<GameObject*>mWallColumnList;

		for (int i = 0; i < 4; i++)
		{
			Ground* pWallColumn = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\WallColumn.fbx");
			pWallColumn->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pWallColumn->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pWallColumn);
			mWallColumnList.push_back(pWallColumn);
		}
		mWallColumnList[0]->GetTransform()->SetPosition(Vec3(-7.3f, -4.8f, -17.8f));
		mWallColumnList[0]->GetTransform()->SetRotation(Vec3(0.0f, -273.0f, 0.0f));
		mWallColumnList[0]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

		mWallColumnList[1]->GetTransform()->SetPosition(Vec3(23.3f, -4.4f, -1.7f));
		mWallColumnList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mWallColumnList[1]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

		mWallColumnList[2]->GetTransform()->SetPosition(Vec3(23.0f, -4.4f, 12.1f));
		mWallColumnList[2]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mWallColumnList[2]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

		mWallColumnList[3]->GetTransform()->SetPosition(Vec3(6.7f, -4.8f, -17.3f));
		mWallColumnList[3]->GetTransform()->SetRotation(Vec3(0.0f, 272.0f, 0.0f));
		mWallColumnList[3]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

#pragma endregion


#pragma region "mPostSlotsList"
		std::vector<GameObject*>mPostSlotsList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pPostSlots = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PostSlots.fbx");
			pPostSlots->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pPostSlots->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pPostSlots);
			mPostSlotsList.push_back(pPostSlots);
		}

		mPostSlotsList[0]->GetTransform()->SetPosition(Vec3(-1.6f, -4.0f, -15.1f));
		mPostSlotsList[0]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
		mPostSlotsList[0]->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));

		mPostSlotsList[1]->GetTransform()->SetPosition(Vec3(20.8f, -4.0f, 6.3f));
		mPostSlotsList[1]->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		mPostSlotsList[1]->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));
#pragma endregion


#pragma region "pPostCageDial"
		std::vector<GameObject*>mPostCageDialList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pPostCageDial = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PostCageDial.fbx");
			pPostCageDial->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pPostCageDial->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pPostCageDial);
			mPostCageDialList.push_back(pPostCageDial);
		}

		mPostCageDialList[0]->GetTransform()->SetPosition(Vec3(-1.0f, -3.9f, -14.8f));
		mPostCageDialList[0]->GetTransform()->SetRotation(Vec3(0.0f, 87.0f, 0.0f));
		mPostCageDialList[0]->GetTransform()->SetScale(Vec3(7.0f, 8.5f, 8.5f));

		mPostCageDialList[1]->GetTransform()->SetPosition(Vec3(20.4f, -4.0f, 6.78f));
		mPostCageDialList[1]->GetTransform()->SetRotation(Vec3(0.0f, -3.0f, 0.0f));
		mPostCageDialList[1]->GetTransform()->SetScale(Vec3(7.0f, 8.5f, 8.5f));
#pragma endregion


#pragma region "pMainDesk"
		{
			Ground* pMainDesk = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\MainDesk.fbx");
			pMainDesk->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pMainDesk);

			pMainDesk->GetTransform()->SetPosition(Vec3(13.5f, -7.7f, -9.4f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pMainDesk->GetTransform()->SetScale(Vec3(14.5f, 14.5f, 14.5f));
		}
#pragma endregion


#pragma region "pTowerDetail"
		{
			Ground* pTowerDetail = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\TowerDetail.fbx");
			pTowerDetail->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pTowerDetail->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pTowerDetail);
			pTowerDetail->GetTransform()->SetPosition(Vec3(15.8f, -2.9f, -11.6));
			pTowerDetail->GetTransform()->SetRotation(Vec3(0.0f, -225.0f, 0.0f));
			pTowerDetail->GetTransform()->SetScale(Vec3(11.5f, 11.5f, 11.5f));
		}
#pragma endregion


#pragma region "Elevator"

		Elevator* elevator = Factory::CreateObject<Elevator>(Vec3(0, 0, 0), L"Deferred", L"");
		AddGameObject(elevator);
		eTarget = elevator;
#pragma endregion

#pragma region "mPlantBase"


		std::vector<GameObject*> mPlantBaseList;
		for (int i = 0; i < 3; i++)
		{
			Ground* pPlantBase = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PlantBase.fbx");
			pPlantBase->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pPlantBase->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pPlantBase);

			pPlantBase->GetTransform()->SetPosition(Vec3(-2.8f, -7.8f, -5.0f));
			pPlantBase->GetTransform()->SetRotation(Vec3(0.0f, 33.0f, 0.0f));
			pPlantBase->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
			mPlantBaseList.push_back(pPlantBase);
		}

		mPlantBaseList[0]->GetTransform()->SetPosition(Vec3(-3.0f, -7.8f, 4.7f));
		mPlantBaseList[0]->GetTransform()->SetRotation(Vec3(0.0f, 33.0f, 0.0f));
		mPlantBaseList[0]->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

		mPlantBaseList[1]->GetTransform()->SetPosition(Vec3(-21.6f, -7.8f, -7.5f));
		mPlantBaseList[1]->GetTransform()->SetRotation(Vec3(0.0f, -49.0f, 0.0f));
		mPlantBaseList[1]->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

		mPlantBaseList[2]->GetTransform()->SetPosition(Vec3(-1.0f, -11.4f, 19.2f));
		mPlantBaseList[2]->GetTransform()->SetRotation(Vec3(0.0f, -178.0f, 0.0f));
		mPlantBaseList[2]->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
#pragma endregion

#pragma region TypeMachine


		std::vector<GameObject*> mTypeMachineList;
		for (int i = 0; i < 4; i++)
		{
			Ground* pTypeMachineMerged = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\TypeMachineMerged.fbx");
			pTypeMachineMerged->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pTypeMachineMerged->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pTypeMachineMerged);
			mTypeMachineList.push_back(pTypeMachineMerged);
		}
		mTypeMachineList[0]->GetTransform()->SetPosition(Vec3(11.5f, -6.8f, 9.3f));
		mTypeMachineList[0]->GetTransform()->SetRotation(Vec3(0.0f, 187.0f, 0.0f));
		mTypeMachineList[0]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

		mTypeMachineList[1]->GetTransform()->SetPosition(Vec3(12.6f, -6.8f, 4.8f));
		mTypeMachineList[1]->GetTransform()->SetRotation(Vec3(0.0f, 37.0f, 0.0f));
		mTypeMachineList[1]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

		mTypeMachineList[2]->GetTransform()->SetPosition(Vec3(14.1f, -6.8f, 0.5f));
		mTypeMachineList[2]->GetTransform()->SetRotation(Vec3(0.0f, 37.0f, 0.0f));
		mTypeMachineList[2]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

		mTypeMachineList[3]->GetTransform()->SetPosition(Vec3(14.1f, -6.8f, 0.5f));
		mTypeMachineList[3]->GetTransform()->SetRotation(Vec3(0.0f, 37.0f, 0.0f));
		mTypeMachineList[3]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
#pragma endregion

#pragma region SphereLight


		std::vector<GameObject*> mSphereLightList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pSphereLightBase = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\SphereLightBase.fbx");

			AddGameObject(pSphereLightBase);
			mSphereLightList.push_back(pSphereLightBase);
		}

		mSphereLightList[0]->GetTransform()->SetPosition(Vec3(6.6f, -1.6f, -15.4f));
		mSphereLightList[0]->GetTransform()->SetRotation(Vec3(0.0f, -20.0f, 0.0f));
		mSphereLightList[0]->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));


		mSphereLightList[1]->GetTransform()->SetPosition(Vec3(21.0f, -1.6f, -1.5f));
		mSphereLightList[1]->GetTransform()->SetRotation(Vec3(0.0f, -20.0f, 0.0f));
		mSphereLightList[1]->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));
#pragma endregion

#pragma region PostBoard


		{
			DecoObject* pPostBoard = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PostBoard.fbx");
			AddGameObject(pPostBoard);
			pPostBoard->GetTransform()->SetPosition(Vec3(20.2f, -3.8f, -6.8f));
			pPostBoard->GetTransform()->SetRotation(Vec3(0.0f, -3.0f, 0.0f));
			pPostBoard->GetTransform()->SetScale(Vec3(5.5f, 5.5f, 5.5f));

		}
#pragma endregion

#pragma region HoD_LampPost


		{
			DecoObject* pHoD_LampPost = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HoD_LampPost.fbx");
			AddGameObject(pHoD_LampPost);
			pHoD_LampPost->GetTransform()->SetPosition(Vec3(-3.1f, -8.5f, 14.8f));
			pHoD_LampPost->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pHoD_LampPost->GetTransform()->SetScale(Vec3(8.0f, 8.0f, 8.0f));
		}
#pragma endregion


		std::vector<GameObject*> mSideRallingBusStopStairList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pSideRallingBusStopStair = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\SideRallingBusStopStair.fbx");
			AddGameObject(pSideRallingBusStopStair);

			mSideRallingBusStopStairList.push_back(pSideRallingBusStopStair);
		}

		mSideRallingBusStopStairList[0]->GetTransform()->SetPosition(Vec3(-17.4f, -9.5f, 11.5f));
		mSideRallingBusStopStairList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mSideRallingBusStopStairList[0]->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));

		mSideRallingBusStopStairList[1]->GetTransform()->SetPosition(Vec3(-12.3f, -9.5f, 10.0f));
		mSideRallingBusStopStairList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mSideRallingBusStopStairList[1]->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));


		{
			DecoObject* pRoundElevator = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\RoundElevator.fbx");
			AddGameObject(pRoundElevator);
			pRoundElevator->GetTransform()->SetPosition(Vec3(-20.9f, 3.8f, -17.2f));
			pRoundElevator->GetTransform()->SetRotation(Vec3::Zero);
			pRoundElevator->GetTransform()->SetScale(Vec3(32.5f, 32.5f, 32.5f));
		}

		{
			DecoObject* pRailing11 = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Railing11.fbx");
			AddGameObject(pRailing11);
			pRailing11->GetTransform()->SetPosition(Vec3(14.3f, -3.3f, 14.7f));
			pRailing11->GetTransform()->SetRotation(Vec3::Zero);
			pRailing11->GetTransform()->SetScale(Vec3(12.5f, 12.5f, 12.5f));
		}

		{
			DecoObject* pRailing10 = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Railing10.fbx");
			AddGameObject(pRailing10);
			pRailing10->GetTransform()->SetPosition(Vec3(15.9f, -3.3f, 16.6f));
			pRailing10->GetTransform()->SetRotation(Vec3::Zero);
			pRailing10->GetTransform()->SetScale(Vec3(17.5f, 17.5f, 17.5f));
		}
		{
			DecoObject* pGraveyardPlane = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\GraveyardPlane.fbx");
			AddGameObject(pGraveyardPlane);
			pGraveyardPlane->GetTransform()->SetPosition(Vec3(22.6f, -5.6f, -2.9f));
			pGraveyardPlane->GetTransform()->SetRotation(Vec3(0.0f, -10.0f, 0.0f));
			pGraveyardPlane->GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));

		}

		{
			DecoObject* pUpperStairContainer = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\UpperStairContainer.fbx");
			AddGameObject(pUpperStairContainer);
			pUpperStairContainer->GetTransform()->SetPosition(Vec3(60.9f, 2.7f, 22.4f));
			pUpperStairContainer->GetTransform()->SetRotation(Vec3(0.0f, -8.0f, 0.0f));
			pUpperStairContainer->GetTransform()->SetScale(Vec3(61.0f, 61.0f, 61.0f));
			pUpperStairContainer->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(12.0f, 12.0f));
			pUpperStairContainer->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(12.0f, 12.0f), 1);

		}


		//5개 정도?
		{
			/*DecoObject* pShortcutDoorStatic = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\ShortcutDoorStatic.fbx");
			AddGameObject(pShortcutDoorStatic);
			pShortcutDoorStatic->GetTransform()->SetPosition(Vec3(62.5f, -5.6f, 23.0f));
			pShortcutDoorStatic->GetTransform()->SetRotation(Vec3(0.0f, 102.0f, 0.0f));
			pShortcutDoorStatic->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));*/
		}


#pragma endregion

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(37.08f, 0.5f, 30.1f);

			Ground* pHallCollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(5.6f, -9.2f, -1.8f), physicsInfo, L"Deferred", L"");
			AddGameObject(pHallCollider);
			SetGizmoTarget(pHallCollider);
		}

#pragma region SoulDoor
		{
			//LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
		
			DecoObject* pDoor = Factory::CreateObject<DecoObject>(Vec3(19.1f, 6.7f, -12.8f), L"Deferred", LARGE_RESOURCE(L"ShortcutDoor\\ShortcutDoor_Fix.fbx"));
			
			pDoor->GetTransform()->SetPosition(Vec3(19.1f, 7.7f, -12.8f));
			pDoor->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pDoor->GetTransform()->SetScale(Vec3(7.82f, 7.82f, 7.82f));

			DecoObject* pBackUv = Factory::CreateObject<DecoObject>(Vec3(19.8f, 4.8f, -15.2f), L"Deferred", LARGE_RESOURCE(L"DoorBackGlow\\DoorBackGlow.fbx"));
			pBackUv->GetTransform()->SetPosition(Vec3(19.8f, 4.7f, -15.2f));
			pBackUv->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pBackUv->GetTransform()->SetScale(Vec3(5.48f, 5.48f, 5.48f));

			PhysicsInfo mEntrancePInfo;
			mEntrancePInfo.eActorType = ActorType::Static;
			mEntrancePInfo.eGeometryType = GeometryType::Box;
			mEntrancePInfo.size = Vec3(3.33f, 5.7f, 2.65f);

			DecoObject* pEntranceColObj = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(19.1f, 4.9f, -15.2f), mEntrancePInfo, L"Deferred", L"");

			SoulDoor* pSoulDoor = Factory::CreateObject<SoulDoor>(Vec3(0, 0, 0), L"Deferred", L"", false , pDoor, pBackUv, pEntranceColObj,MapType::EntranceHallMap);
			
			AddGameObject(pDoor);
			AddGameObject(pBackUv);
			AddGameObject(pEntranceColObj);
			AddGameObject(pSoulDoor);
		}
#pragma endregion

	}
	void MainOfficeMap::InitBusStart()
	{
		pBus->BusActive();
		int b = 0;
	}
}