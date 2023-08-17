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

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"

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

/* Event */
#include "SceneChangeEvent.h"


namespace yj
{
	MainOfficeMap::MainOfficeMap()
		: Map(MapType::MainOfficeMap)
	{
	}

	MainOfficeMap::~MainOfficeMap()
	{
	}

	void MainOfficeMap::Initialize()
	{
		Map::Initialize();
	}

	void MainOfficeMap::Update()
	{
		Map::Update();
		/*if (mTarget != nullptr)
		{
			if (IS_UP(KeyType::LEFT))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::UP))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::DOWN))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::RIGHT))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::Z))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::X))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y -= 0.1f, target_pos.z);
				mTarget->GetTransform()->SetPosition(fixed_pos);

			}
			if (IS_UP(KeyType::E))
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 10.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::Q))
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::R))
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::T))
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::O))
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::P))
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::ENTER))
			{
				Vec3 a = mTarget->GetTransform()->GetPosition();
				Vec3 b = mTarget->GetTransform()->GetRotation();
				Vec3 c = mTarget->GetTransform()->GetScale();
				int d = 0;


			}
		}*/
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
		gpEngine->SetSwapChainRTVClearColor(Vec4(100.f, 100.f, 100.f, 255.f));
		{
			DecoObject* pBus = Factory::CreateObject<DecoObject>(Vec3(-17.0f, -8.0f, 33.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\CUTSCENE_Bus.fbx");
			pBus->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

			AddGameObject(pBus);
		}

		{
			Ground* pFrontGround = Factory::CreateObject<Ground>(Vec3(0.0f, -10.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\uv1.fbx");
			pFrontGround->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

			AddGameObject(pFrontGround);
		}

		{
			Ground* pREFLECTIONS = Factory::CreateObject<Ground>(Vec3(5.5f, -9.0f, -1.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Floor_REFLECTIONS.fbx");
			pREFLECTIONS->GetTransform()->SetScale(Vec3(40, 40, 40));

			AddGameObject(pREFLECTIONS);
		}

		{
			Ground* pUpstair = Factory::CreateObject<Ground>(Vec3(9.5f, 3.0f, -5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Upstairs.fbx");
			pUpstair->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));

			AddGameObject(pUpstair);
		}

		{
			/*Ground* pUv3 = Factory::CreateObject<Ground>(Vec3(-39.5f, 5.5f, -8.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\uv3.fbx");
			pUv3->GetTransform()->SetScale(Vec3(130.0f, 130.0f, 130.0f));
			AddGameObject(pUv3);*/
		}

		{
			Ground* pStair_Single5 = Factory::CreateObject<Ground>(Vec3(29.5f, 3.5f, 8.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HoD_Stairs_Single.fbx");
			pStair_Single5->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));
			AddGameObject(pStair_Single5);
		}
		{
			Ground* pStairIsland = Factory::CreateObject<Ground>(Vec3(54.0f, -4.0f, 22.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\StairsIslandContainer.fbx");
			pStairIsland->GetTransform()->SetRotation(Vec3(0.0f, 70.0f, 0.0f));
			pStairIsland->GetTransform()->SetScale(Vec3(50.0f, 50.0f, 50.0f));
			AddGameObject(pStairIsland);
		}
		{
			Ground* pGrandmaDoorFence = Factory::CreateObject<Ground>(Vec3(61.0f, 12.5f, 23.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\GrandmaDoorsFence.fbx");
			pGrandmaDoorFence->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));
			pGrandmaDoorFence->GetTransform()->SetRotation(Vec3(0.0f, -10.0f, 0.0f));
			AddGameObject(pGrandmaDoorFence);
		}

		{
			Ground* pFloatingDoors = Factory::CreateObject<Ground>(Vec3(83.0f, -5.0f, -24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\FloatingDoors.fbx");
			pFloatingDoors->GetTransform()->SetScale(Vec3(150.0f, 150.0f, 150.0f));
			pFloatingDoors->GetTransform()->SetRotation(Vec3(0.0f, 140.0f, 0.0f));
			AddGameObject(pFloatingDoors);
		}

		{
			Ground* pBusStop = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\stairsIsland.fbx");
			pBusStop->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pBusStop->GetTransform()->SetRotation(Vec3(0.0f, -160.0f, 0.0f));
			AddGameObject(pBusStop);
		}

#pragma region "사무실 책상 리스트"


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

#pragma region "사무실 의자 리스트"

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

		{
			Ground* pMainDesk = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\MainDesk.fbx");
			pMainDesk->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pMainDesk);

			pMainDesk->GetTransform()->SetPosition(Vec3(13.5f, -7.7f, -9.4f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pMainDesk->GetTransform()->SetScale(Vec3(14.5f, 14.5f, 14.5f));


		}

		{
			Ground* pTowerDetail = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\TowerDetail.fbx");
			pTowerDetail->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pTowerDetail->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pTowerDetail);

			pTowerDetail->GetTransform()->SetPosition(Vec3(15.8f, -2.9f, -11.6));
			pTowerDetail->GetTransform()->SetRotation(Vec3(0.0f, -45.0f, 0.0f));
			pTowerDetail->GetTransform()->SetScale(Vec3(11.5f, 11.5f, 11.5f));
		}


	}



	void MainOfficeMap::Exit()
	{

	}
}