#include "pch.h"
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
#include "Cow.h"

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
#include "SparkParticle.h"


/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "CinematicCamMove.h"
#include "PlayerMoveOverMapScript.h"
#include "FocusingScript.h"
#include "OwnerFollowScript.h"
#include "TextBox.h"

/* Event */
#include "SceneChangeEvent.h"
#include "BossMap.h"

namespace hm
{
	BossMap::BossMap()
		:Map(MapType::BossMap)
	{
	}
	BossMap::~BossMap()
	{
	}
	void BossMap::Initialize()
	{
		Map::Initialize();
	}
	void BossMap::Start()
	{
		Map::Start();
		PLAYER->GetTransform()->SetPosition(Vec3(7.33f, 0.f, -3.4f));
		PLAYER->GetTransform()->SetRotation(Vec3(0.f, -45.f, 90.f));

		SetDirLightPosition(Vec3(-31.5f, 27.2f, 33.9f));
		SetDirLightRotation(Vec3(41.7f, 136.54f, 294.54f));

		PLAYER->GetKeyInfo().SetLeftKey(KeyType::RIGHT);
		PLAYER->GetKeyInfo().SetForwardKey(KeyType::DOWN);

		mpMainCamera->GetTransform()->SetPosition(Vec3(-32.24f, 26.3f, 14.f));
		mpMainCamera->GetTransform()->SetRotation(Vec3(47.f, -233.3f, 0.f));

		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{
			case 1:
				PLAYER->GetTransform()->SetPosition(Vec3(-15.f, -2.57f, 0.f));
				break;
			}
		}

		OwnerFollowScript* pFollowScript = spPlayerHolder->GetScript<OwnerFollowScript>();
		pFollowScript->SetOffset(Vec3(-17.4f, 29.f, 14.1f));
		mpMainCamera->GetScript<FocusingScript>()->SetFocusingMode(true);

		ChangeCameraMode();
	}
	void BossMap::Update()
	{
		Map::Update();

		if (IS_DOWN(KeyType::O))
		{
			GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeOut, 0.1f, nullptr, std::bind(&Map::ChangeCameraMode, this));
			GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 0.1f);
		}

		Vec3 pos = MAIN_CAMERA->GetTransform()->GetPosition();
		wstring strPos = {};
		strPos += L"x = " + std::to_wstring(pos.x) + L" ";
		strPos += L"y = " + std::to_wstring(pos.y) + L" ";
		strPos += L"z = " + std::to_wstring(pos.z);

		Vec3 rot = MAIN_CAMERA->GetTransform()->GetRotation();
		wstring strRot = {};
		strRot += L"x = " + std::to_wstring(rot.x) + L" ";
		strRot += L"y = " + std::to_wstring(rot.y) + L" ";
		strRot += L"z = " + std::to_wstring(rot.z);
		FONT->DrawString(strPos, 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);
		FONT->DrawString(strRot, 30.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);

		/*Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
		wstring strPos = {};
		strPos += L"x = " + std::to_wstring(playerPos.x) + L" ";
		strPos += L"y = " + std::to_wstring(playerPos.y) + L" ";
		strPos += L"z = " + std::to_wstring(playerPos.z);
		FONT->DrawString(strPos, 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);*/
	}
	void BossMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}
	void BossMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}
	void BossMap::Render()
	{
		Map::Render();
	}
	void BossMap::Enter()
	{
		// 최종보스
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.0f, 6.f);

			LORD_BOSS_ROLL* pLordOfDoorRoll = Factory::CreateMonster<LORD_BOSS_ROLL>(Vec3(12.3f, -4.f, -8.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\LordOfDoor_Roller.fbx");
			pLordOfDoorRoll->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pLordOfDoorRoll->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 130.f));
			pLordOfDoorRoll->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -2.5f, 0.f));
			pLordOfDoorRoll->GetAnimator()->Play(1, true);
			pLordOfDoorRoll->Disable();

			pLordOfDoor = Factory::CreateMonster<LORD_BOSS>(Vec3(12.3f, -4.f, -8.f), info, L"LordBossDeferred", L"..\\Resources\\FBX\\Monster\\LordOfDoor.fbx");
			pLordOfDoor->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pLordOfDoor->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 130.f));
			pLordOfDoor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -2.5f, 0.f));

			GameObject* pEffect = nullptr;
			{
				pEffect = Factory::CreateObject<GameObject>(Vec3::Zero, L"Forward", L"", false, LayerType::Unknown);
				pEffect->SetDontDestroyObject(L"SparkParticle");
				pEffect->AddComponent(new OwnerFollowScript(pLordOfDoor));

				SparkParticle* pParticle = pEffect->AddComponent(new SparkParticle);
				pParticle->SetAngle(Vec3(-180.f, 0.f, 0.f));
				pParticle->SetParticleRotation(Vec3(0.f, 0.f, 0.f));
				pParticle->SetScatterRadius(5.f);
				pParticle->SetStartColor(Vec3(1.f, 0.f, 0.f));
				pParticle->SetEndColor(Vec3(1.f, 1.f, 0.f));

				AddGameObject(pEffect);
				pEffect->Disable();
			}

			pLordOfDoor->SetSparkParticle(pEffect);

			pLordOfDoor->GetMeshRenderer()->GetMaterial()->SetBloom(true, 4);

			//pLordOfDoor->GetMeshRenderer()->GetMaterial()->SetBloomPower(3.f, 4);

			pLordOfDoor->GetMeshRenderer()->GetMaterial()->SetBloomFilter(Vec4(0.f, 0.f, 1.f, 0.f), 4);
			//pLordOfDoor->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 0.f, 0.f, 0.f), 4);

			AudioSound* pSound = pLordOfDoor->AddComponent(new AudioSound);


			pLordOfDoor->SetObject(pLordOfDoorRoll);
			pLordOfDoorRoll->SetLORD_BOSS(pLordOfDoor);

			AddGameObject(pLordOfDoorRoll);
			AddGameObject(pLordOfDoor);
			//SetMeshTarget(pLordOfDoor);

		}

		//WallObject Zip
		{
			PhysicsInfo Info;
			Info.eActorType = ActorType::Static;
			Info.eGeometryType = GeometryType::Box;
			Info.size = Vec3(28.6f, 9.2f, 0.8f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(7.8f, -4.7f, 15.7f), Info, L"NoDraw", L"");

			AddGameObject(pWall);

		}

		//WallObject Zip
		{
			PhysicsInfo Info;
			Info.eActorType = ActorType::Static;
			Info.eGeometryType = GeometryType::Box;
			Info.size = Vec3(28.6f, 9.2f, 0.8f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-12.5f, -4.7f, -13.2f), Info, L"NoDraw", L"");
			pWall->GetTransform()->SetRotation(Vec3(0.f, 236.f, 0.f));
			AddGameObject(pWall);

		}

		//WallObject Zip
		{
			PhysicsInfo Info;
			Info.eActorType = ActorType::Static;
			Info.eGeometryType = GeometryType::Box;
			Info.size = Vec3(28.6f, 9.2f, 0.8f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-9.3f, -4.7f, 7.2f), Info, L"NoDraw", L"");
			pWall->GetTransform()->SetRotation(Vec3(0.f, 320.f, 0.f));
			AddGameObject(pWall);
		}

		{
			WallObject* pFrontGround = Factory::CreateObject<WallObject>(Vec3(0.4f, -5.3f, -0.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\uv1.fbx");
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
			WallObject* pUpstair = Factory::CreateObject<WallObject>(Vec3(9.5f, 3.0f, -5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Upstairs.fbx");
			pUpstair->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));

			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloom(true, 7);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 7);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloom(true, 31);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 31);


			AddGameObject(pUpstair);
		}

		/*{
			Ground* pBusStop = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\stairsIsland.fbx");
			pBusStop->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pBusStop->GetTransform()->SetRotation(Vec3(0.0f, -160.0f, 0.0f));
			pBusStop->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.04f, 0.04f));
			AddGameObject(pBusStop);
		}*/




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
		/*{
			Ground* pMainDesk = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\MainDesk.fbx");
			pMainDesk->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pMainDesk);

			pMainDesk->GetTransform()->SetPosition(Vec3(13.5f, -7.7f, -9.4f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pMainDesk->GetTransform()->SetScale(Vec3(14.5f, 14.5f, 14.5f));
		}*/
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

#pragma endregion

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(70.57f, 0.5f, 70.122f);

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

			WallObject* pOfficeCollider = Factory::CreateObjectHasPhysical<WallObject>(Vec3(0.9f, -4.5f, -0.3f), physicsInfo, L"NoDraw", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\OfficeCollider.fbx");
			pOfficeCollider->DrawShadow(false);
			AddGameObject(pOfficeCollider);
			//SetGizmoTarget(pOfficeCollider);
		}


		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(25.5f, 1.0f, 25.5f);

			WallObject* pBusGround = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-7.2f, -12.1f, 24.0f), physicsInfo, L"Deferred", L"");
			pBusGround->GetTransform()->SetRotation(Vec3(0.0f, 15.0f, 0.0f));
			AddGameObject(pBusGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.31f, 1.0f, 26.39f);

			WallObject* pBridgeGround = Factory::CreateObjectHasPhysical<WallObject>(Vec3(21.95f, -0.22f, -0.03f), physicsInfo, L"Deferred", L"");
			AddGameObject(pBridgeGround);

		}

		// 버스 배치된 다리에서 오피스쪽으로 이동하는 다리 충돌체
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(6.5f, 1.f, 10.15f);

			WallObject* pBusStopToMainDeskCollider = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-15.6f, -11.3f, 11.7f), physicsInfo, L"Deferred", L"");
			pBusStopToMainDeskCollider->GetTransform()->SetRotation(Vec3(25.3f, 14.05f, 2.24f));
			AddGameObject(pBusStopToMainDeskCollider);
		}

		// 상층에서 꼭대기로 이어주는 충돌체
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.9f, 1.f, 6.09f);

			WallObject* pStairToTop = Factory::CreateObjectHasPhysical<WallObject>(Vec3(21.9f, 0.f, -8.5f), physicsInfo, L"Deferred", L"");
			pStairToTop->GetTransform()->SetRotation(Vec3(28.6f, 12.12f, 0.f));
			AddGameObject(pStairToTop);
		}

		// 꼭대기 충돌체
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(12.65f, 1.f, 13.f);

			WallObject* pTop = Factory::CreateObjectHasPhysical<WallObject>(Vec3(21.6f, 1.39f, -17.35f), physicsInfo, L"Deferred", L"");
			AddGameObject(pTop);
		}

		TEXTBOX->SetWriteTexts(18, 24, "BossSpeechEnd");
		TEXTBOX->Apear();
	}
	void BossMap::Exit()
	{
	}
}