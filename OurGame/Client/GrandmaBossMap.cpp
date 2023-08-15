#include "pch.h"
#include "GrandmaBossMap.h"
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
#include "Monster.h"

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
#include "PlayerSlashScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	GrandmaBossMap::GrandmaBossMap()
		: Map(MapType::GrandmaBossMap)
	{
	}

	GrandmaBossMap::~GrandmaBossMap()
	{
	}

	void GrandmaBossMap::Initialize()
	{
		Map::Initialize();
	}

	void GrandmaBossMap::Update()
	{
		Map::Update();
	}

	void GrandmaBossMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void GrandmaBossMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void GrandmaBossMap::Render()
	{
		Map::Render();
	}

	void GrandmaBossMap::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));
		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(25.f, 1.f, 25.f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossMap\\GrandmaBossGround.fbx");
			//pGround->GetMeshRenderer()->GetMaterial()->SetInt(3, 1);
			
			pGround->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pGround->GetTransform()->SetPositionExcludingColliders(Vec3(-12.f, -18.5f, 0.f));

			AddGameObject(pGround);
		}

		// Monster
		{
			Monster* pMonster = Factory::CreateObject<Monster>(Vec3(0.f, 3.f, -20.f), L"PaperBurn", L"..\\Resources\\FBX\\Monster\\Mage.fbx");
			pMonster->AddComponent(new PaperBurnScript);

			shared_ptr<Texture> pNoiseTex = GET_SINGLE(Resources)->Load<Texture>(L"BurnNoise", L"..\\Resources\\Texture\\BurnNoise.png");
			pMonster->GetMeshRenderer()->GetMaterial()->SetTextureAllSubset(1, pNoiseTex);

			pMonster->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
			pMonster->GetTransform()->SetRotation(AXIS_Y, 180.f);

			AddGameObject(pMonster);
		}

		// Sword_Heavy
		{
			DecoObject* pSlashTest = Factory::CreateObject<DecoObject>(Vec3(0.f, 3.f, 0.f), L"PlayerSlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbx");
			pSlashTest->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pSlashTest->GetMeshRenderer()->GetMaterial()->SetInt(3, 1);
			pSlashTest->AddComponent(new PlayerSlashScript);

			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HeavySlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbm\\sword_slash_texture_1.png");
			pSlashTest->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			pSlashTest->GetRigidBody()->RemoveGravity();
			AddGameObject(pSlashTest);
		}

		// Toy
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

			AddGameObject(pPlayer);
		}

		// Table
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(5.f, 10.f, 20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossMap\\GrandmaBossTable.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(-90.f, 20.f, 0.f));
			AddGameObject(pDecoObject);
		}

		// Start
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(30.f, 0.5f, 30.f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, 0.f, -30.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossMap\\GrandmaBossStart_Btm.fbx");

			pGround->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
			pGround->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pGround->GetTransform()->SetRotationExcludingColliders(Vec3(-90.f, 0.f, 0.f));
			pGround->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.5f, 0.f));

			AddGameObject(pGround);
		}

		// Wall
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 12; ++x)
			{
				DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossMap\\GrandmaBossWall1.fbx");
				pDecoObject->GetRigidBody()->RemoveGravity();

				float radian = (225.f + (x * 16.f)) * XM_PI / 180.f;
				float radius = 13.f;

				pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
				pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 50.f + x * 16.f, 0.f));

				pDecoObject->GetTransform()->SetPosition(
					Vec3(radius * cosf(radian) + radius * sinf(radian),
						-10.f + y * 10.f,
						(radius * cosf(radian) - radius * sinf(radian)) + 10.f));
				AddGameObject(pDecoObject);
			}
		}


		// Left Rocks
		{
			// Left Collider
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(13.f, 5.f, 17.f);

				WallObject* pWallObject = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.f, 2.5f, -36.f), info, L"Forward", L"");
				AddGameObject(pWallObject);
			}

			// GrayRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType1");
				pRock->GetTransform()->SetPosition(Vec3(-3.f, 1.f, -29.5f));
				AddGameObject(pRock);
			}

			// GrayRockType2
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType2");
				pRock->GetTransform()->SetPosition(Vec3(-3.f, 1.f, -31.f));
				AddGameObject(pRock);
			}

			// GrayRockType3
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType3");
				pRock->GetTransform()->SetPosition(Vec3(-3.f, 1.f, -32.5f));
				AddGameObject(pRock);
			}

			// GrayRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType3");
				pRock->GetTransform()->SetPosition(Vec3(-4.5f, 1.f, -29.5f));
				AddGameObject(pRock);
			}

			// GrayRockType2
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType2");
				pRock->GetTransform()->SetPosition(Vec3(-6.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(AXIS_Y, 90.f);
				AddGameObject(pRock);
			}

			// BlackRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType1");
				pRock->GetTransform()->SetPosition(Vec3(-5.f, 1.f, -31.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType2
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType2");
				pRock->GetTransform()->SetPosition(Vec3(-7.f, 1.f, -30.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType4
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType4");
				pRock->GetTransform()->SetPosition(Vec3(-9.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType3
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType3");
				pRock->GetTransform()->SetPosition(Vec3(-11.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType1");
				pRock->GetTransform()->SetPosition(Vec3(-13.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}
		}

		// Right Rocks
		{
			// Right Collider
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(13.f, 5.f, 17.f);

				WallObject* pWallObject = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-9.f, 2.5f, -36.f), info, L"Forward", L"");
				AddGameObject(pWallObject);
			}

			// GrayRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType1");
				pRock->GetTransform()->SetPosition(Vec3(3.f, 1.f, -29.5f));
				AddGameObject(pRock);
			}

			// GrayRockType2
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType2");
				pRock->GetTransform()->SetPosition(Vec3(3.f, 1.f, -31.f));
				AddGameObject(pRock);
			}

			// GrayRockType3
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType3");
				pRock->GetTransform()->SetPosition(Vec3(3.f, 1.f, -32.5f));
				AddGameObject(pRock);
			}

			// GrayRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType3");
				pRock->GetTransform()->SetPosition(Vec3(4.5f, 1.f, -29.5f));
				AddGameObject(pRock);
			}

			// GrayRockType2
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"GrayRockType2");
				pRock->GetTransform()->SetPosition(Vec3(6.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(AXIS_Y, 90.f);
				AddGameObject(pRock);
			}

			// BlackRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType1");
				pRock->GetTransform()->SetPosition(Vec3(5.f, 1.f, -31.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType2
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType2");
				pRock->GetTransform()->SetPosition(Vec3(7.f, 1.f, -30.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType4
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType4");
				pRock->GetTransform()->SetPosition(Vec3(9.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType3
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType3");
				pRock->GetTransform()->SetPosition(Vec3(11.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}

			// BlackRockType1
			{
				DecoObject* pRock = GET_SINGLE(PrefabManager)->GetPrefab<DecoObject>(L"BlackRockType1");
				pRock->GetTransform()->SetPosition(Vec3(13.f, 1.f, -29.5f));
				pRock->GetTransform()->SetRotation(Vec3(90.f, 0.f, 180.f));

				AddGameObject(pRock);
			}
		}

		// Bannister
		for (int i = 0; i < 2; ++i)
		{
			WallObject* pBannister = GET_SINGLE(PrefabManager)->GetPrefab<WallObject>(L"Bannister");
			pBannister->GetTransform()->SetPosition(Vec3(i % 2 ? -14.8f : 14.8f, 2.3f, -21.5f));

			AddGameObject(pBannister);
		}

		// Shortcut Door
		//{
		//	DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 5.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\ShortcutDoor.fbx");
		//	pDecoObject->GetRigidBody()->RemoveGravity();

		//	pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
		//	pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		//	AddGameObject(pDecoObject);
		//}

		// Light
		for (int i = 0; i < 2; ++i)
		{
			DecoObject* pGameObject = new DecoObject();
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(i ? -10.f : 18.f, 10.f, -15.f));
			pTransform->SetScale(Vec3(10.f, 10.f, 10.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(1.f, 1.f, 0.f));
			pLight->SetAmbient(Vec3(0.f, 0.f, 0.f));
			pLight->SetLightRange(12.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}
	}

	void GrandmaBossMap::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
	}
}

