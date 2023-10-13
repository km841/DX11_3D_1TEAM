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
#include "SoulDoor.h"
#include "CameraHolder.h"
#include "HpUi.h"
#include "Interface.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Bat.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
#include "Banker.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Mirror.h"
#include "AudioSound.h"
#include "Animator.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "CinematicCamMove.h"
#include "PlayerMoveOverMapScript.h"
#include "FocusingScript.h"
#include "OwnerFollowScript.h"
#include "HeadText.h"

/* Event */
#include "SceneChangeEvent.h"

namespace yj
{
	MainOfficeMap::MainOfficeMap()
		: Map(MapType::MainOfficeMap)
		, eTarget(nullptr)
		, pBus(nullptr)
	{
	}

	MainOfficeMap::~MainOfficeMap()
	{
	}

	void MainOfficeMap::Initialize()
	{
		Map::Initialize();

		PLAYER->GetAudioSound()->SetSound(L"MainOfficeBGM", this, true, "..\\Resources\\Sound\\MainOfficeBGM.mp3");
		PLAYER->GetAudioSound()->Play();
#pragma endregion
	}

	void MainOfficeMap::Update()
	{
		Map::Update();

		if (IS_DOWN(KeyType::O))
		{
			GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeOut, 0.1f, nullptr, std::bind(&Map::ChangeCameraMode, this));
			GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 0.1f);
		}

		if (false == pBus->IsBusArrived())
		{
			PLAYER->Disable();
		}
		else
		{
			PLAYER->Enable();
		}

		Vec3 pos = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetGameObject()->GetTransform()->GetPosition();
		wstring strPos = {};
		strPos += L"x = " + std::to_wstring(pos.x) + L" ";
		strPos += L"y = " + std::to_wstring(pos.y) + L" ";
		strPos += L"z = " + std::to_wstring(pos.z);

		Vec3 rot = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetGameObject()->GetTransform()->GetRotation();
		wstring strRot = {};
		strRot += L"x = " + std::to_wstring(rot.x) + L" ";
		strRot += L"y = " + std::to_wstring(rot.y) + L" ";
		strRot += L"z = " + std::to_wstring(rot.z);
		FONT->DrawString(strPos, 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);
		FONT->DrawString(strRot, 30.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);
	}

	void MainOfficeMap::Start()
	{
		Map::Start();
		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{
			case -1:
				PLAYER->GetTransform()->SetPosition(Vec3(-15.6f, -10.0f, 24.4f));
				break;
			}
		}

		SetDirLightPosition(Vec3(-31.5f, 27.2f, 33.9f));
		SetDirLightRotation(Vec3(41.7f, 136.54f, 294.54f));
		mpMainCamera->GetScript<FocusingScript>()->SetFocusingMode(true);
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

		ChangeCameraMode();
		InitObjectAdd();
		GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 1,
			nullptr, std::bind(&MainOfficeMap::InitBusStart, this));

		HPUI->UiOn();
	}

	void MainOfficeMap::Exit()
	{
		PLAYER->GetAudioSound()->Stop();
	}


	void MainOfficeMap::InitObjectAdd()
	{
		PLAYER->SetDontDestroyObject(L"Player");


		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(10.0f, 10.0f, 10.0f);

			Banker* pBanker = Factory::CreateObjectHasPhysical<Banker>(Vec3(13.9f, -6.3f, -8.6f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Banker.fbx");
			pBanker->GetTransform()->SetScale(Vec3(1.3f, 1.3f, 1.3f));
			pBanker->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 135.f));

			pBanker->GetAnimator()->Play(L"Banker_WriteLoop", true);
			AddGameObject(pBanker);
			//SetMeshTarget(pBanker);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(10.0f, 10.0f, 10.0f);

			Npc* pHallCrow = Factory::CreateObjectHasPhysical<Npc>(Vec3(-5.2f, -8.f, -10.5f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HallCrowWorker.fbx");
			pHallCrow->GetTransform()->SetScale(Vec3(0.7f, 0.7f, 0.7f));
			pHallCrow->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 135.f));

			AddGameObject(pHallCrow);
		}


		{
			/*pBus = Factory::CreateObject<Bus>(Vec3(-17.0f, -8.0f, 33.0f), L"Deferred",
				L"..\\Resources\\FBX\\Map\\MainOfficeMap\\CUTSCENE_Bus.fbx");
			pBus->GetTransform()->SetScale(Vec3(50.0f, 50.0f, 50.0f));*/
			pBus = Factory::CreateObject<Bus>(Vec3(-2.f, -10.0f, 45.0f), L"Deferred",
				L"..\\Resources\\FBX\\Map\\MainOfficeMap\\CUTSCENE_Bus.fbx");
			pBus->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pBus->GetTransform()->SetRotation(Vec3(0.0f, 135.0f, 0.0f));

			pBus->GetMeshRenderer()->SetSubsetRenderFlag(103, false);
			pBus->GetMeshRenderer()->SetSubsetRenderFlag(104, false);

			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 68);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 68);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 73);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 73);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 78);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 78);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 79);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 79);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 81);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 81);

			for (int i = 93; i <= 102; ++i)
			{
				pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, i);
				pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), i);
			}

			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 107);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 0.5f, 1.f), 107);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloom(true, 108);
			pBus->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 0.5f, 1.f), 108);



			AddGameObject(pBus);
		}

		{
			Ground* pFrontGround = Factory::CreateObject<Ground>(Vec3(0.4f, -5.3f, -0.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\uv1.fbx");
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
			GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(4.9f, -8.85f, -12.1f), L"Forward", L"", false, LayerType::Mirror);

			pMirror->GetTransform()->SetScale(Vec3(25.f, 20.f, 20.f));
			pMirror->AddComponent(new Mirror);
			pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pMirror->GetTransform()->SetRotation(Vec3(90.f, 319.4f, 0.f));
			pMirror->GetMirror()->SetAlpha(0.4f);

			AddGameObject(pMirror);
		}

		{
			Ground* pUpstair = Factory::CreateObject<Ground>(Vec3(9.5f, 3.0f, -5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Upstairs.fbx");
			pUpstair->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));

			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloom(true, 7);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 7);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloom(true, 31);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 31);


			AddGameObject(pUpstair);
		}

		//{
		//	Ground* pStair_Single5 = Factory::CreateObject<Ground>(Vec3(29.5f, 3.5f, 8.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HoD_Stairs_Single.fbx");
		//	pStair_Single5->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));
		//	AddGameObject(pStair_Single5);
		//}

		//{
		//	Ground* pGrandmaDoorFence = Factory::CreateObject<Ground>(Vec3(61.0f, 12.5f, 23.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\GrandmaDoorsFence.fbx");
		//	pGrandmaDoorFence->GetTransform()->SetScale(Vec3(60.0f, 60.0f, 60.0f));
		//	pGrandmaDoorFence->GetTransform()->SetRotation(Vec3(0.0f, -10.0f, 0.0f));
		//	AddGameObject(pGrandmaDoorFence);
		//}

		{
			Ground* pBusStop = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\stairsIsland.fbx");
			pBusStop->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pBusStop->GetTransform()->SetRotation(Vec3(0.0f, -160.0f, 0.0f));
			pBusStop->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.04f, 0.04f));
			AddGameObject(pBusStop);
		}

		//{
		//	GameObject* pGameObject = Factory::CreateObject<GameObject>(Vec3(0.f, 0.f, 0.f), L"Forward", L"", false, LayerType::Unknown);
		//	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, GET_SINGLE(Resources)->Load<Texture>(L"Texture3D", L"..\\Resources\\Texture\\TestTexture.png"));
		//	pGameObject->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
		//	pGameObject->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());

		//	AddGameObject(pGameObject);
		//	SetGizmoTarget(pGameObject);
		//}

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
			pSphereLightBase->GetMeshRenderer()->GetMaterial()->SetBloom(true, 3);
			pSphereLightBase->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 3);
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
			pHoD_LampPost->GetMeshRenderer()->GetMaterial()->SetBloom(true, 3);
			pHoD_LampPost->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 3);
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

		//{
		//	DecoObject* pUpperStairContainer = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\UpperStairContainer.fbx");
		//	AddGameObject(pUpperStairContainer);
		//	pUpperStairContainer->GetTransform()->SetPosition(Vec3(60.9f, 2.7f, 22.4f));
		//	pUpperStairContainer->GetTransform()->SetRotation(Vec3(0.0f, -8.0f, 0.0f));
		//	pUpperStairContainer->GetTransform()->SetScale(Vec3(61.0f, 61.0f, 61.0f));
		//	pUpperStairContainer->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(12.0f, 12.0f));
		//	pUpperStairContainer->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(12.0f, 12.0f), 1);

		//}

#pragma endregion

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(48.57f, 0.5f, 39.122f);

			Ground* pHallCollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(9.2f, -9.12f, -6.7f), physicsInfo, L"Deferred", L"");
			pHallCollider->GetTransform()->SetRotation(Vec3(0.f, -332.9f, 0.f));
			pHallCollider->DrawShadow(false);
			AddGameObject(pHallCollider);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Mesh;
			physicsInfo.size = Vec3(49.0f, 49.0f, 49.0f);

			Ground* pOfficeCollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.9f, -4.5f, -0.3f), physicsInfo, L"NoDraw", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\OfficeCollider.fbx");
			pOfficeCollider->DrawShadow(false);
			AddGameObject(pOfficeCollider);
		}



#pragma region SoulDoor
		{
			DecoObject* pDoor = Factory::CreateObject<DecoObject>(Vec3(19.1f, 6.7f, -12.8f), L"Deferred", LARGE_RESOURCE(L"ShortcutDoor\\ShortcutDoor_Fix.fbx"));

			pDoor->GetTransform()->SetPosition(Vec3(19.1f, 7.7f, -12.8f));
			pDoor->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pDoor->GetTransform()->SetScale(Vec3(7.82f, 7.82f, 7.82f));

			DecoObject* pBackUv = Factory::CreateObject<DecoObject>(Vec3(19.8f, 4.8f, -15.2f), L"Deferred", LARGE_RESOURCE(L"DoorBackGlow\\DoorBackGlow.fbx"));
			pBackUv->GetTransform()->SetPosition(Vec3(19.8f, 4.7f, -15.2f));
			pBackUv->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pBackUv->GetTransform()->SetScale(Vec3(5.48f, 5.48f, 5.48f));

			PhysicsInfo mEntrancePInfo;
			mEntrancePInfo.eActorType = ActorType::Kinematic;
			mEntrancePInfo.eGeometryType = GeometryType::Box;
			mEntrancePInfo.size = Vec3(3.33f, 5.7f, 2.65f);

			DecoObject* pEntranceColObj = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(19.1f, 4.9f, -15.2f), mEntrancePInfo, L"Deferred", L"");

			SoulDoor* pSoulDoor = Factory::CreateObject<SoulDoor>(Vec3(0, 0, 0), L"Deferred", L"", false, pDoor, pBackUv, pEntranceColObj, MapType::EntranceHallMap, 1);

			AddGameObject(pDoor);
			AddGameObject(pBackUv);
			AddGameObject(pEntranceColObj);
			AddGameObject(pSoulDoor);
		}
#pragma endregion

		{
			GameObject* pEnterTextBox = Factory::CreateObject<GameObject>(Vec3::One, L"Forward", L"", false, LayerType::Unknown);
			pEnterTextBox->GetMeshRenderer()->GetMaterial()->SetTexture(0,GET_SINGLE(Resources)->Load<Texture>(L"Texture3D", L"..\\Resources\\Texture\\PopUpEnter.png"));
			pEnterTextBox->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());

			HeadText* pEnterTextScript = pEnterTextBox->AddComponent<HeadText>();
			AddGameObject(pEnterTextBox);
			/*pEnterTextScript->SetDectetorPos(Vec3(10.0f, 10.0f, 10.0f));*/
			SetGizmoTarget(pEnterTextBox);


		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(25.5f, 1.0f, 25.5f);

			Ground* pBusGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-7.2f, -12.1f, 24.0f), physicsInfo, L"Deferred", L"");
			pBusGround->GetTransform()->SetRotation(Vec3(0.0f, 15.0f, 0.0f));
			AddGameObject(pBusGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.31f, 1.0f, 26.39f);

			Ground* pBridgeGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(21.95f, -0.22f, -0.03f), physicsInfo, L"Deferred", L"");
			AddGameObject(pBridgeGround);

		}

		// 버스 배치된 다리에서 오피스쪽으로 이동하는 다리 충돌체
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(6.5f, 1.f, 10.15f);

			Ground* pBusStopToMainDeskCollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(-15.6f, -11.3f, 11.7f), physicsInfo, L"Deferred", L"");
			pBusStopToMainDeskCollider->GetTransform()->SetRotation(Vec3(25.3f, 14.05f, 2.24f));
			AddGameObject(pBusStopToMainDeskCollider);
		}

		// 상층에서 꼭대기로 이어주는 충돌체
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.9f, 1.f, 6.09f);

			Ground* pStairToTop = Factory::CreateObjectHasPhysical<Ground>(Vec3(21.9f, 0.f, -8.5f), physicsInfo, L"Deferred", L"");
			pStairToTop->GetTransform()->SetRotation(Vec3(28.6f, 12.12f, 0.f));
			AddGameObject(pStairToTop);
		}

		// 꼭대기 충돌체
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(12.65f, 1.f, 13.f);

			Ground* pTop = Factory::CreateObjectHasPhysical<Ground>(Vec3(21.6f, 1.39f, -17.35f), physicsInfo, L"Deferred", L"");
			AddGameObject(pTop);
		}
	}


	void MainOfficeMap::InitBusStart()
	{
		pBus->BusActive();
		int b = 0;
	}
}