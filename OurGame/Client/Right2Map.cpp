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
#include "UI.h"

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
#include "RotateKeyScript.h"

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

		// Banker
		{
			DecoObject* pBanker = Factory::CreateObject<DecoObject>(Vec3(0.f, 10.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Banker.fbx");
			pBanker->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
			pBanker->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));
			pBanker->AddComponent(new TestAnimationScript);
			pBanker->AddComponent(new PlacementScript);

			AddGameObject(pBanker);
		}

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
		//{
		//	DecoObject* pGameObject = new DecoObject();
		//	Transform* pTransform = pGameObject->AddComponent(new Transform);
		//	pTransform->SetPosition(Vec3(0.f, 5.f, 0.f));
		//	pTransform->SetScale(Vec3(10.f, 10.f, 10.f));
		//	Light* pLight = pGameObject->AddComponent(new Light);
		//	pLight->SetDiffuse(Vec3(1.f, 1.f, 1.f));
		//	pLight->SetAmbient(Vec3(0.f, 0.f, 0.f));
		//	pLight->SetLightRange(80.f);
		//	pLight->SetLightType(LightType::PointLight);
		//	AddGameObject(pGameObject);
		//}



		// 벽쪽 2단 선반
		{
			for (int i = 0; i < 4; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-9.9f + i * 8.5f, 2.8f, 16.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

				AddGameObject(pTwoTierShelf);
			}

			// 혼자 가로로 삐져나온 선반 (식탁보로 덮혀질 예정)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-5.6f, 2.8f, 10.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
				pTwoTierShelf->GetTransform()->SetRotation(AXIS_Y, 90.f);
				AddGameObject(pTwoTierShelf);
			}

			// 식탁보
			{
				DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(21.7f, 8.6f, 6.5f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\tableCloth.fbx");
				pTableCloth->GetTransform()->SetScale(Vec3(15.4f, 10.f, 23.3f));
				pTableCloth->GetTransform()->SetRotation(Vec3(-180.f, 0.f, 180.f));
				//pTableCloth->AddComponent(new PlacementScript);
				//pKey->AddComponent(new RotateKeyScript);
				pTableCloth->GetMeshRenderer()->GetMaterial()->SetBloom(true);
				pTableCloth->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 0.3f, 1.f));
				AddGameObject(pTableCloth);
			}
		}

		// 벽쪽 3단 선반
		for (int i = 0; i < 2; ++i)
		{
			DecoObject* pThreeTierShelf = Factory::CreateObject<DecoObject>(Vec3(21.6f, 4.4f, 13.1f + i * -12.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ThreeTierShelf.fbx");
			pThreeTierShelf->GetTransform()->SetScale(Vec3(9.5f, 9.3f, 10.5f));

			AddGameObject(pThreeTierShelf);
		}

		// 3단 선반 이어주는 한칸 짜리 선반
		{
			DecoObject* pThreeTierCornerFoot = Factory::CreateObject<DecoObject>(Vec3(21.6f, 4.4f, 6.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ThreeTierSquareCornerFoot.fbx");

			pThreeTierCornerFoot->GetTransform()->SetScale(Vec3(9.5f, 9.3f, 9.5f));

			AddGameObject(pThreeTierCornerFoot);
		}

		// 가운데쪽 2단 선반 나란히 놓인 것
		{
			for (int i = 0; i < 2; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(7.6f + i * 8.f, 2.8f, -2.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

				AddGameObject(pTwoTierShelf);
			}
		}

		// 식탁보
		{
			DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(-5.6f, 5.3f, 11.9f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\tableCloth.fbx");
			pTableCloth->GetTransform()->SetScale(Vec3(13.4f, 10.f, 12.4f));
			pTableCloth->GetTransform()->SetRotation(Vec3(-180.f, 0.f, 180.f));
			
			//pKey->AddComponent(new RotateKeyScript);
			AddGameObject(pTableCloth);
		}

		// 꼭대기 나무판자
		{
			DecoObject* pTopShelf = Factory::CreateObject<DecoObject>(Vec3(17.f, 6.1f, -2.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TopShelf.fbx");
			pTopShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
			pTopShelf->GetTransform()->SetRotation(AXIS_Z, -1.f);

			AddGameObject(pTopShelf);
		}

		// 바닥 러그
		{
			DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 0.f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Rug_Mark.fbx");
			pBottomRug->GetTransform()->SetScale(Vec3(15.f, 8.f, 18.f));

			AddGameObject(pBottomRug);
		}

		// 의자
		{
			DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(16.2f, 3.5f, 7.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Chair.fbx");


			pChair->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
			pChair->GetTransform()->SetRotation(Vec3(0.f, 18.f, 0.f));
			AddGameObject(pChair);
		}

		// 우측 벽에 붙은 선반들
		{
			// 2단 선반
			for (int i = 0; i < 2; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(i == 0 ? 13.9f : -8.2f, 2.8f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
				AddGameObject(pTwoTierShelf);
			}

			// 2단 선반과 이어지는 한 칸짜리 선반
			{
				DecoObject* pTwoTierCornerFoot = Factory::CreateObject<DecoObject>(Vec3(20.1f, 2.7f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierSquareCornerFoot.fbx");
				pTwoTierCornerFoot->GetTransform()->SetScale(Vec3(6.5f, 6.3f, 6.0f));
				pTwoTierCornerFoot->GetTransform()->SetRotation(AXIS_Y, 180.f);


				AddGameObject(pTwoTierCornerFoot);
			}

			// 화롯불
			{
				DecoObject* pFirelamp = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pFirelamp->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				AddGameObject(pFirelamp);
			}

			// 화롯불
			{
				DecoObject* pFirelamp = Factory::CreateObject<DecoObject>(Vec3(11.1f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pFirelamp->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);

				AddGameObject(pFirelamp);
			}
		}

		// 가운데 있는 2단 선반
		{
			DecoObject* pTwoTierFootAbs = Factory::CreateObject<DecoObject>(Vec3(-5.9f, 2.8f, -2.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierSquareFootAbsolute.fbx");


			pTwoTierFootAbs->GetTransform()->SetScale(Vec3(6.5f, 6.3f, 6.2f));
			//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);

			AddGameObject(pTwoTierFootAbs);

			// 화롯불
			{
				DecoObject* pFirelamp = Factory::CreateObject<DecoObject>(Vec3(-5.9f, 7.4f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pFirelamp->GetMeshRenderer()->GetMaterial()->SetBloom(true);
				pFirelamp->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f);
				pFirelamp->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				AddGameObject(pFirelamp);
			}
		}

		// 기둥들
		{
			// 우측 벽 기둥 1
			{
				DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(-21.f, 7.9f, -17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ColumnFull.fbx");
				pColumn->GetTransform()->SetScale(Vec3(10.f, 16.f, 10.f));
				//pColumn->AddComponent(new PlacementScript);

				AddGameObject(pColumn);
			}

			// 우측 벽 기둥 2
			{
				DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(-3.1f, 7.9f, -17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ColumnFull.fbx");
				pColumn->GetTransform()->SetScale(Vec3(10.f, 16.f, 10.f));
				//pColumn->AddComponent(new PlacementScript);

				AddGameObject(pColumn);
			}

			// 벽난로 벽
			{
				DecoObject* pFireplaceWall = Factory::CreateObject<DecoObject>(Vec3(2.9f, 7.9f, -18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\fireplaceWall.fbx");
				pFireplaceWall->GetTransform()->SetScale(Vec3(10.f, 16.f, 15.6f));
				pFireplaceWall->GetTransform()->SetRotation(AXIS_Y, -90.f);

				AddGameObject(pFireplaceWall);
			}

			// 우측 벽 기둥 3
			{
				DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(8.9f, 7.9f, -17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ColumnFull.fbx");
				pColumn->GetTransform()->SetScale(Vec3(10.f, 16.f, 10.f));
				//pColumn->AddComponent(new PlacementScript);

				AddGameObject(pColumn);
			}

			// 우측 벽 기둥 4
			{
				DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(24.5f, 7.9f, -17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ColumnFull.fbx");
				pColumn->GetTransform()->SetScale(Vec3(10.f, 16.f, 10.f));
				//pColumn->AddComponent(new PlacementScript);

				AddGameObject(pColumn);
			}

			// 좌측 벽 기둥
			{
				DecoObject* pColumn = Factory::CreateObject<DecoObject>(Vec3(24.5f, 7.9f, 18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ColumnFull.fbx");
				pColumn->GetTransform()->SetScale(Vec3(10.f, 16.f, 10.f));

				AddGameObject(pColumn);
			}
		}

		// 상부 마감 Rim
		{
			// 정면 긴 Rim
			{
				DecoObject* pRim = Factory::CreateObject<DecoObject>(Vec3(24.8f, 15.5f, -0.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\WallRim.fbx");
				pRim->GetTransform()->SetScale(Vec3(32.f, 32.f, 35.f));
				//pRim->AddComponent(new PlacementScript);
				AddGameObject(pRim);
			}

			// 우측 바깥쪽 Rim
			{
				DecoObject* pRim = Factory::CreateObject<DecoObject>(Vec3(16.7f, 15.5f, -18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\WallRim.fbx");
				pRim->GetTransform()->SetScale(Vec3(32.f, 32.f, 14.f));
				pRim->GetTransform()->SetRotation(AXIS_Y, 90.f);
				//pRim->AddComponent(new PlacementScript);
				AddGameObject(pRim);
			}

			// 우측 안쪽 Rim
			{
				DecoObject* pRim = Factory::CreateObject<DecoObject>(Vec3(-12.f, 15.5f, -18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\WallRim.fbx");
				pRim->GetTransform()->SetScale(Vec3(32.f, 32.f, 16.6f));
				pRim->GetTransform()->SetRotation(AXIS_Y, 90.f);
				//pRim->AddComponent(new PlacementScript);
				AddGameObject(pRim);
			}
		}

		// 키 베이스
		{
			DecoObject* pKeyShrine = Factory::CreateObject<DecoObject>(Vec3(16.1f, 0.3f, -9.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\keyShrineBase.fbx");
			pKeyShrine->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
			//pKeyShrine->AddComponent(new PlacementScript);
			AddGameObject(pKeyShrine);
		}

		// 키
		{
			DecoObject* pKey = Factory::CreateObject<DecoObject>(Vec3(16.1f, 2.2f, -9.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\grandmaKey.fbx");
			pKey->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			//pKey->AddComponent(new PlacementScript);
			//pKey->AddComponent(new RotateKeyScript);

			pKey->GetMeshRenderer()->GetMaterial()->SetBloom(true);
			AddGameObject(pKey);
		}



		// Bloom Texture
		//{
		//	UI* pUI = Factory::CreateObject<UI>(Vec3(-500.f, 200.f, 0.f), L"Forward", L"");
		//	pUI->GetRigidBody()->RemoveGravity();
		//	pUI->GetTransform()->SetScale(Vec3(300.f, 300.f, 1.f));
		//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"BlurTempTex");

		//	pUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		//	AddGameObject(pUI);
		//}
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
