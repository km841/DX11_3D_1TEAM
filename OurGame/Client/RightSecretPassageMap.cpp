#include "pch.h"
#include "RightSecretPassageMap.h"
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
#include "FireLamp.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "TeleportZone.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Bat.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
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
#include "BonFireScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace jh
{
	RightSecretPassageMap::RightSecretPassageMap()
		: Map(MapType::RightSecretPassageMap)
	{
	}

	RightSecretPassageMap::~RightSecretPassageMap()
	{
	}

	void RightSecretPassageMap::Initialize()
	{
		Map::Initialize();
	}

	void RightSecretPassageMap::Start()
	{
		Map::Start();
	}

	void RightSecretPassageMap::Update()
	{
		Map::Update();

		if (IS_DOWN(KeyType::L))
		{
			CreateSpawnMonsterMAP();
		}
	}

	void RightSecretPassageMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void RightSecretPassageMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void RightSecretPassageMap::Render()
	{
		Map::Render();
	}

	void RightSecretPassageMap::Enter()
	{
		

		//배경맵 하얀색으로 만들어주는 코드
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

		InitObjectAdd();
		InitColliderAdd();
		FuncObjectAdd();

		//CreateSpawnMonsterMAP(); //몬스터 만드는 코드
	

	}

	void RightSecretPassageMap::Exit()
	{
	}
	void RightSecretPassageMap::InitObjectAdd()
	{
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
			info.size = Vec3(10.f, 0.5f, 10.f);

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

			//SetGizmoTarget(pCobwebDoor);
			AddGameObject(pCobwebDoor);
		}
#pragma endregion

#pragma region 바닥 소품
		// 항아리(바깥쪽)
		for (int i = 0; i < 3; i++)
		{
			DecoObject* pPotGeneric = Factory::CreateObject<DecoObject>(Vec3(11.25f, -3.05f, 5.42f - (i * 6.9f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric->GetTransform()->SetScale(Vec3(2.87f, 3.1f, 2.87f));

			AddGameObject(pPotGeneric);
		}
		// 항아리(안쪽)
		for (int i = 0; i < 3; i++)
		{
			DecoObject* pPotGeneric2 = Factory::CreateObject<DecoObject>(Vec3(-11.75f, -3.05f, 5.42f - (i * 6.9f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\RightSecretPassageMap\\POT_HEAL_Generic Variant (3).fbx");

			pPotGeneric2->GetTransform()->SetScale(Vec3(2.87f, 3.1f, 2.87f));

			AddGameObject(pPotGeneric2);
		}
	}
	void RightSecretPassageMap::InitColliderAdd()
	{
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(33.15f, 1.0f, 30.6f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-0.2f, -4.3f, 0.2f), physicsInfo, L"Deferred", L"");
			AddGameObject(pGround);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(21.6f, 6.67f, 3.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(5.1f, -1.6f, -13.9f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(4.32f, 6.76f, 3.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-13.0f, -1.6f, -13.9f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);

		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(4.32f, 6.76f, 3.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-13.0f, -1.6f, -13.9f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(13.3f, 6.76f, 3.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-8.0f, -1.6f, 10.3f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(13.3f, 6.76f, 3.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.4f, -1.6f, 10.3f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0f, 5.9f, 22.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(15.1f, -1.7f, -1.8f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);
			//SetGizmoTarget(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0f, 5.9f, 22.15f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-15.1f, -1.7f, -1.8f), physicsInfo, L"Deferred", L"");
			AddGameObject(pWall);
			//SetGizmoTarget(pWall);
		}
	}
	void RightSecretPassageMap::FuncObjectAdd()
	{
		// 화롯불
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.94f, 2.94f, 2.94f);


			DecoObject* pLampUpper = Factory::CreateObject<DecoObject>(Vec3(0.2f, -3.2f, -1.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

			pLampUpper->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pLampUpper->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
			AddGameObject(pLampUpper);


			DecoObject* pLampBelow = Factory::CreateObject<DecoObject>(Vec3(0.2f, -3.2f, -1.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

			pLampBelow->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pLampBelow->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
			AddGameObject(pLampBelow);

			DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(0.2f, -3.2f, -1.5f), L"Fire", L"");
			pBonFire->GetMeshRenderer()->SetMaterial(pBonFire->GetMeshRenderer()->GetMaterial()->Clone());
			pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
			pBonFire->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
			pBonFire->AddComponent(new BonFireScript);
			AddGameObject(pBonFire);

			DecoObject* pLightObject = nullptr;
			{
				pLightObject = new DecoObject;
				Transform* pTransform = pLightObject->AddComponent(new Transform);
				pTransform->SetPosition(Vec3(-5.8f, 7.4f, -16.5f));
				pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
				pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
				Light* pLight = pLightObject->AddComponent(new Light);
				pLight->SetDiffuse(Vec3(0.8f, 0.5f, 0.2f));
				pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
				pLight->SetLightRange(10.f);
				pLight->SetLightType(LightType::PointLight);
				AddGameObject(pLightObject);
			}

			yj::FireLamp* pFireLamp = Factory::CreateObjectHasPhysical<yj::FireLamp>(Vec3(0.2f, -3.1f, -1.5f), physicsInfo, L"Deferred", L"", false, pLampUpper, pLampBelow, pBonFire, pLightObject);
			AddGameObject(pFireLamp);
			//SetGizmoTarget(pFireLamp);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.53, 3.8f, 2.625f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(0.6f, -3.7f, 13.1f), physicsInfo, L"Forward", L"", false, MapType::EntranceHallMap, 3);
			AddGameObject(pTelZone);
			//SetGizmoTarget(pTelZone);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.53, 3.8f, 2.625f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(-8.3f, -3.7f, -14.0f), physicsInfo, L"Forward", L"", false, MapType::EntranceHallMap, 3);
			AddGameObject(pTelZone);
			//SetGizmoTarget(pTelZone);
		}
	}
	void RightSecretPassageMap::CreateSpawnMonsterMAP()
	{
		{//콩벌레
			SpawnDoor<HeadRoller>* pHeadRoller = Factory::SpawnMonster<HeadRoller>(Vec3(-8.f, -1.f, 1.2f), Vec3(0.f, -60.f, 0.f));
			pHeadRoller->GetTransform()->SetRotation(Vec3(0.f, -60.f, 0.f));
			AddGameObject(pHeadRoller);
			//SetGizmoTarget(pHeadRoller);
		}

		{//콩벌레
			SpawnDoor<HeadRoller>* pHeadRoller = Factory::SpawnMonster<HeadRoller>(Vec3(7.7f, -1.f, -5.5f), Vec3(0.f, 130.f, 0.f));
			pHeadRoller->GetTransform()->SetRotation(Vec3(0.f, 130.f, 0.f));
			AddGameObject(pHeadRoller);
		}

		{//마법사
			SpawnDoor<Mage>* pMage = Factory::SpawnMonster<Mage>(Vec3(7.7f, -1.f, 2.5f), Vec3(-90.f, 40.f, 0.f));
			pMage->GetTransform()->SetRotation(Vec3(0.f, 40.f, 0.f));
			AddGameObject(pMage);
		}
	}
}
