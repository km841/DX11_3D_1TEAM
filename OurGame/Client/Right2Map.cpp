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
#include "FireLamp.h"

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

	void Right2Map::Start()
	{
		Map::Start();
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
		/*	PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

			SetGizmoTarget(pPlayer);

			AddGameObject(pPlayer);*/
		}

		// 좌측 벽쪽 2단 선반
		{
			for (int i = 0; i < 4; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-9.9f + i * 8.5f, 2.8f, 16.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

				AddGameObject(pTwoTierShelf);
			}

			// 선반 안쪽 항아리

			for (int i = 0; i < 6; ++i)
			{
				DecoObject* pMansionSpicePot = Factory::CreateObject<DecoObject>(Vec3(-12.4f + i * 2.6f, 3.2f, 16.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\MansionSpicePot.fbx");
				pMansionSpicePot->GetTransform()->SetScale(Vec3(2.3f, 2.3f, 2.3f));
				
				AddGameObject(pMansionSpicePot);
			}

			// 혼자 가로로 삐져나온 선반 (식탁보로 덮혀질 예정)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-5.6f, 2.8f, 10.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
				pTwoTierShelf->GetTransform()->SetRotation(AXIS_Y, 90.f);
				AddGameObject(pTwoTierShelf);

				// 선반 안쪽 서랍들
				{
					{
						DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 3.5f, 12.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
						pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
						pEmptyBox->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
						
						AddGameObject(pEmptyBox);
					}

					{
						DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-5.3f, 3.5f, 10.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
						pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
						pEmptyBox->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

						AddGameObject(pEmptyBox);
					}

					{
						DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 3.5f, 8.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
						pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
						pEmptyBox->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
						
						AddGameObject(pEmptyBox);
					}
				}

				// 깨지는 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-9.3f, 7.3f, 16.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
					AddGameObject(pPotHeal);
				}
			}

			// 식탁보
			{
				DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(21.7f, 8.6f, 6.5f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\tableCloth.fbx");
				pTableCloth->GetTransform()->SetScale(Vec3(15.4f, 10.f, 23.3f));
				pTableCloth->GetTransform()->SetRotation(Vec3(-180.f, 0.f, 180.f));
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

			// 선반 안쪽 서랍들
			{
				{
					DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(5.5f, 3.5f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
					pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
					AddGameObject(pEmptyBox);
				}

				{
					DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(7.6f, 3.5f, -2.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
					pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
					
					AddGameObject(pEmptyBox);
				}

				{
					DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(9.7f, 3.5f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
					pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
					//SetGizmoTarget(pEmptyBox);
					AddGameObject(pEmptyBox);
				}
			}

			// 사다리
			{
				DecoObject* pLadder = Factory::CreateObject<DecoObject>(Vec3(5.f, 2.43f, -1.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Ladder.fbx");
				pLadder->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));

				//SetGizmoTarget(pLadder);

				AddGameObject(pLadder);

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

		// 항아리 삼총사
		{
			// 깨지는 항아리
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(12.8f, 1.18f, 4.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				AddGameObject(pPotHeal);
			}

			// 깨지는 항아리
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(11.6f, 1.18f, 6.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, 115.5f, 0.f));

				//SetGizmoTarget(pPotHeal);
				AddGameObject(pPotHeal);
			}

			// 깨지는 항아리
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(14.f, 1.18f, 6.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, 36.7f, 0.f));
				
				AddGameObject(pPotHeal);
			}
		}



		// 우측 벽에 붙은 선반들
		{
			// 2단 선반 (안쪽, 바깥쪽)
			for (int i = 0; i < 2; ++i)
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(i == 0 ? 13.9f : -8.2f, 2.8f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
				AddGameObject(pTwoTierShelf);
			}

			// 선반 안에 그릇들
			for (int i = 0; i < 2; ++i)
			{
				for (int j = 0; j < 2; ++j)
				{
					if (i == 1 && j == 0)
						continue;

					DecoObject* pPlates = Factory::CreateObject<DecoObject>(Vec3(15.5f + j * -3.5f, 2.8f + i * 0.8f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Plates.fbx");
					pPlates->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					
					AddGameObject(pPlates);
				}

			}

			// 선반 안에 서랍들
			{
				{
					DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-6.f, 3.5f, -16.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
					pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));

					AddGameObject(pEmptyBox);
				}

				{
					DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-8.1f, 3.5f, -15.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
					pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
					//SetGizmoTarget(pEmptyBox);
					AddGameObject(pEmptyBox);
				}

				{
					DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>(Vec3(-10.2f, 3.5f, -16.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\EmptyBox.fbx");
					pEmptyBox->GetTransform()->SetScale(Vec3(3.5f, 3.5f, 3.5f));
					//SetGizmoTarget(pEmptyBox);
					AddGameObject(pEmptyBox);
				}
			}

			// 2단 선반과 이어지는 한 칸짜리 선반 (바깥쪽)
			{
				DecoObject* pTwoTierCornerFoot = Factory::CreateObject<DecoObject>(Vec3(20.1f, 2.88f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierSquareCornerFoot.fbx");
				pTwoTierCornerFoot->GetTransform()->SetScale(Vec3(6.5f, 5.86f, 6.0f));
				pTwoTierCornerFoot->GetTransform()->SetRotation(AXIS_Y, 180.f);

				AddGameObject(pTwoTierCornerFoot);
			}

			// 2단 선반과 이어지는 한 칸짜리 선반 (안쪽)
			{
				DecoObject* pTwoTierCornerFoot = Factory::CreateObject<DecoObject>(Vec3(-14.4f, 2.88f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TwoTierSquareCornerFoot.fbx");
				pTwoTierCornerFoot->GetTransform()->SetScale(Vec3(6.5f, 5.86f, 6.0f));
				AddGameObject(pTwoTierCornerFoot);
			}

			// 깨지는 항아리
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-9.8f, 6.88f, -16.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				AddGameObject(pPotHeal);
			}

			// 화분
			{
				//MansionPlantPot
				DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(20.1f, 8.1f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\MansionPlantPot.fbx");
				pMansionPlantPot->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				
				AddGameObject(pMansionPlantPot);
			}

			// 사다리
			{
				DecoObject* pLadder = Factory::CreateObject<DecoObject>(Vec3(-14.f, 2.63f, -14.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Ladder.fbx");
				pLadder->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));

				AddGameObject(pLadder);
				
			}

			// 바깥쪽 책 쌓여있는 곳
			{
				DecoObject* pBookStack = Factory::CreateObject<DecoObject>(Vec3(23.5f, 3.5f, -15.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\BookStack.fbx");
				pBookStack->GetTransform()->SetScale(Vec3(7.2f, 7.2f, 7.2f));
				pBookStack->GetTransform()->SetRotation(AXIS_Y, 180.f);
				

				AddGameObject(pBookStack);
			}

			// 화롯불
			{

				DecoObject* pLampUpper = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampUpper->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampUpper->GetMeshRenderer()->SetSubsetRenderFlag(0,false);
				AddGameObject(pLampUpper);


				DecoObject* pLampBelow = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampBelow->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampBelow->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
				AddGameObject(pLampBelow);

				yj::FireLamp* pFireLamp = Factory::CreateObject<yj::FireLamp>(Vec3(-5.8f, 7.4f, -16.5f), L"Deferred", L"",false, pLampUpper, pLampBelow);
				AddGameObject(pFireLamp);

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

		// 샹들리에
		{
			DecoObject* pChandelier = Factory::CreateObject<DecoObject>(Vec3(5.f, 37.6f, 8.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ChandelierWithChain.fbx");
			pChandelier->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 13, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 13, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 13, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 14, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 14, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 14, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 15, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 15, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 15, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 16, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 16, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 16, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 17, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 17, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 17, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 18, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 18, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 18, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 19, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 19, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 19, 0);

			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloom(true, 20, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 20, 0);
			pChandelier->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 20, 0);

			//SetGizmoTarget(pChandelier);
			AddGameObject(pChandelier);
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
