#include "pch.h"
#include "Right2Map.h"
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
#include "UIText.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	Right2Map::Right2Map()
		: Map(MapType::Right2Map)
	{
	}

	Right2Map::~Right2Map()
	{
	}

	void Right2Map::Initialize()
	{
		Map::Initialize();
	}

	void Right2Map::Update()
	{
		Map::Update();
	}

	void Right2Map::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void Right2Map::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void Right2Map::Render()
	{
		Map::Render();
	}

	void Right2Map::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(50.f, 1.f, 40.f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Right2_Ground.fbx");
			pGround->GetTransform()->SetScale(Vec3(50.f, 1.f, 50.f));

			AddGameObject(pGround);
		}

		// Side
		{
			DecoObject* pSideWall = Factory::CreateObject<DecoObject>(Vec3(1.7f, 7.3f, -0.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Right2_Side.fbx");
			pSideWall->GetTransform()->SetScale(Vec3(46.7f, 50.f, 46.5f));
			

			AddGameObject(pSideWall);
		}

		// Toy
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 5.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			//pPlayer->AddComponent(new TestAnimationScript);
			pPlayer->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

			//UIText* pUIText = pPlayer->AddComponent(new UIText);
			//pUIText->SetText(TEXT("텍스트 컴포넌트 출력 테스트"));
			//pUIText->Shadow(true);
			//pUIText->SetShadowColor(0.0f, 0.0f, 0.0f, 1.0f);
			//pUIText->SetShadowOffset(Vec3(2.f, -2.f, 0.f));
			//pUIText->SetShadowOpacity(1.f);
			//pUIText->SetFont("FreshGothic");
			//pUIText->SetColor(1.f, 1.f, 1.f, 1.f);
			//pUIText->SetOpacity(0.5f);
			//pUIText->AlphaBlend(false);
			//pUIText->SetRenderArea(0.f, 750.f, 300.f, 850.f);
			//pUIText->GetTransform()->SetPosition(Vec3(0.f, 900.f, -20.f));

			AddGameObject(pPlayer);

		}


		// Point Light
		{
			DecoObject* pGameObject = new DecoObject();
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(0.f, 5.f, 0.f));
			pTransform->SetScale(Vec3(10.f, 10.f, 10.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(1.f, 1.f, 1.f));
			pLight->SetAmbient(Vec3(0.f, 0.f, 0.f));
			pLight->SetLightRange(80.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}



		// 벽쪽 2단 선반
		{
			for (int i = 0; i < 4; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-7.9f + i * 8.f, 2.8f, 16.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.f, 8.f, 8.f));

				AddGameObject(pTwoTierShelf);
			}

			// 혼자 가로로 삐져나온 선반 (식탁보로 덮혀질 예정)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-3.9f, 2.8f, 11.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.f, 8.f, 8.f));
				pTwoTierShelf->GetTransform()->SetRotation(AXIS_Y, 90.f);

				AddGameObject(pTwoTierShelf);
			}
		}

		// 벽쪽 3단 선반
		for (int i = 0; i < 2; ++i)
		{
			DecoObject* pThreeTierShelf = Factory::CreateObject<DecoObject>(Vec3(21.6f, 4.4f, 13.6f + i * -12.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ThreeTierShelf.fbx");
			pThreeTierShelf->GetTransform()->SetScale(Vec3(9.f, 8.8f, 10.f));

			AddGameObject(pThreeTierShelf);
		}

		// 3단 선반 이어주는 한칸 짜리 선반
		{
			DecoObject* pThreeTierCornerFoot = Factory::CreateObject<DecoObject>(Vec3(21.6f, 4.4f, 7.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ThreeTierSquareCornerFoot.fbx");
			
			pThreeTierCornerFoot->GetTransform()->SetScale(Vec3(9.f, 8.8f, 9.f));

			AddGameObject(pThreeTierCornerFoot);
		}

		// 가운데쪽 2단 선반 나란히 놓인 것
		{
			for (int i = 0; i < 2; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(7.9f + i * 8.f, 2.8f, -1.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.f, 8.f, 8.f));

				AddGameObject(pTwoTierShelf);
			}
		}

		// 꼭대기 나무판자
		{
			DecoObject* pTopShelf = Factory::CreateObject<DecoObject>(Vec3(16.9f, 5.8f, -1.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TopShelf.fbx");
			pTopShelf->GetTransform()->SetScale(Vec3(8.f, 8.f, 8.f));
			pTopShelf->GetTransform()->SetRotation(AXIS_Z, -1.f);
			pTopShelf->AddComponent(new PlacementScript);
			AddGameObject(pTopShelf);
		}
	}

		void Right2Map::Exit()
		{
			GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
			GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
			GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
			GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
			GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
			GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
		}

	}
