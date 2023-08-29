#include "pch.h"
#include "HallColliderCheckMap.h"
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
#include "WallObject.h"

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
#include "PlacementScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace jh
{
	HallColliderCheckMap::HallColliderCheckMap()
		: Map(MapType::HallColliderCheckMap)
	{
	}

	HallColliderCheckMap::~HallColliderCheckMap()
	{
	}

	void HallColliderCheckMap::Initialize()
	{
		Map::Initialize();
	}

	void HallColliderCheckMap::Update()
	{
		Map::Update();
	}

	void HallColliderCheckMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void HallColliderCheckMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void HallColliderCheckMap::Render()
	{
		Map::Render();
	}

	void HallColliderCheckMap::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

		//배경맵 하얀색으로 만들어주는 코드
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(100.f, 1.f, 100.f);
			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, 4.f, 0.f), physicsInfo, L"Deferred", L"");
			pGround->GetTransform()->SetScale(Vec3(50.f, 1.f, 50.f));

			AddGameObject(pGround);
		}

		// Toy
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			//pPlayer->AddComponent(new TestAnimationScript);
			//pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

			AddGameObject(pPlayer);
		}

#pragma region 1층
		// 1층 벽
		{
			// 1, 2층 벽
			{
				DecoObject* pTotalFrame = Factory::CreateObject<DecoObject>(Vec3(2.8f, 15.3f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MapFrame.fbx", true);

				pTotalFrame->GetTransform()->SetScale(Vec3(130.f, 130.f, 130.f));
				pTotalFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				pTotalFrame->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pTotalFrame->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));



				AddGameObject(pTotalFrame);
			}

			// 숨은통로
			{
				DecoObject* pSecretPassage = Factory::CreateObject<DecoObject>(Vec3(-13.f, 5.94f, -37.85f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main-detach (1).fbx");
				
				pSecretPassage->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pSecretPassage->GetTransform()->SetScale(Vec3(22.75f, 22.75f, 22.75f));

				AddGameObject(pSecretPassage);
			}

			// 기둥
			{
				DecoObject* pFirstFloorWallColumn = Factory::CreateObject<DecoObject>(Vec3(-13.f, 6.1f, -61.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn->GetTransform()->SetScale(Vec3(23.85f, 23.85f, 23.85f));
				
				AddGameObject(pFirstFloorWallColumn);
			}
			// 기둥2
			{
				DecoObject* pFirstFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(-13.f, 6.1f, -45.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn2->GetTransform()->SetScale(Vec3(23.85f, 23.85f, 23.85f));
				AddGameObject(pFirstFloorWallColumn2);
			}

			// 기둥3
			{
				DecoObject* pFirstFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(-16.8f, 6.1f, -45.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn3->GetTransform()->SetScale(Vec3(23.85f, 23.85f, 23.85f));
				AddGameObject(pFirstFloorWallColumn3);
			}

			// 기둥4
			{
				DecoObject* pFirstFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(-13.f, 6.1f, -30.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn4->GetTransform()->SetScale(Vec3(23.85f, 23.85f, 23.85f));
				AddGameObject(pFirstFloorWallColumn4);
			}

			// 기둥5
			{
				DecoObject* pFirstFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-16.8f, 6.1f, -30.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn5->GetTransform()->SetScale(Vec3(23.85f, 23.85f, 23.85f));
				
				AddGameObject(pFirstFloorWallColumn5);
			}

			//			// 천장틀
			//			{
			//				DecoObject* pFirstFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-1.6f, 1.37f, -3.97f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pFirstFloorWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallRim->GetTransform()->SetScale(Vec3(1.7f, 1.4f, 1.4f));
			//
			//				AddGameObject(pFirstFloorWallRim);
			//			}
			//			// 천장틀2
			//			{
			//				DecoObject* pFirstFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-1.8f, 1.37f, -3.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pFirstFloorWallRim2->GetTransform()->SetScale(Vec3(0.5f, 1.4f, 1.4f));
			//
			//				AddGameObject(pFirstFloorWallRim2);
			//			}
			//			// 천장틀3
			//			{
			//				DecoObject* pFirstFloorWallRim3 = Factory::CreateObject<DecoObject>(Vec3(-2.05f, 1.37f, -2.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pFirstFloorWallRim3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallRim3->GetTransform()->SetScale(Vec3(1.7f, 1.4f, 1.4f));
			//
			//				AddGameObject(pFirstFloorWallRim3);
			//			}
			//			// 천장틀4
			//			{
			//				DecoObject* pFirstFloorWallRim4 = Factory::CreateObject<DecoObject>(Vec3(-1.8f, 1.37f, -1.16f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pFirstFloorWallRim4->GetTransform()->SetScale(Vec3(0.5f, 1.4f, 1.4f));
			//
			//				AddGameObject(pFirstFloorWallRim4);
			//			}
			//			// 천장틀5(1, 2층 사이)
			//			{
			//				DecoObject* pFirstFloorWallRim5 = Factory::CreateObject<DecoObject>(Vec3(-1.62f, 1.37f, 0.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pFirstFloorWallRim5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallRim5->GetTransform()->SetScale(Vec3(2.3f, 1.4f, 1.4f));
			//
			//				AddGameObject(pFirstFloorWallRim5);
			//			}
			//			// 벽 패널
			//			{
			//				DecoObject* pFirstFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-1.55f, -0.975f, -4.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallPanel->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel);
			//			}
			//			// 벽 패널2
			//			{
			//				DecoObject* pFirstFloorWallPanel2 = Factory::CreateObject<DecoObject>(Vec3(-1.55f, -0.975f, -3.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallPanel2->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel2);
			//			}
			//			// 벽 패널3
			//			{
			//				DecoObject* pFirstFloorWallPanel3 = Factory::CreateObject<DecoObject>(Vec3(-2.04f, -0.975f, -2.83f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallPanel3->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel3);
			//			}
			//			// 벽 패널4
			//			{
			//				DecoObject* pFirstFloorWallPanel4 = Factory::CreateObject<DecoObject>(Vec3(-2.04f, -0.975f, -1.34f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallPanel4->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel4);
			//			}
			//			// 벽 패널5
			//			{
			//				DecoObject* pFirstFloorWallPanel5 = Factory::CreateObject<DecoObject>(Vec3(-2.04f, -0.808f, -2.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (12).fbx");
			//
			//				pFirstFloorWallPanel5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorWallPanel5->GetTransform()->SetScale(Vec3(0.5f, 0.46f, 0.25f));
			//
			//				AddGameObject(pFirstFloorWallPanel5);
			//			}
			//			// 벽 패널6
			//			{
			//				DecoObject* pFirstFloorWallPanel6 = Factory::CreateObject<DecoObject>(Vec3(-2.15f, -0.975f, -1.24f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel6->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel6);
			//			}
			//			// 철창
			//			{
			//				DecoObject* pSpikeDoor = Factory::CreateObject<DecoObject>(Vec3(-2.07f, -1.17f, -2.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\SpikeDoor.fbx");
			//
			//				pSpikeDoor->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
			//				pSpikeDoor->GetTransform()->SetScale(Vec3(1.f, 0.9f, 0.8f));
			//
			//				AddGameObject(pSpikeDoor);
			//			}
			//			// 벽 패널7
			//			{
			//				DecoObject* pFirstFloorWallPanel7 = Factory::CreateObject<DecoObject>(Vec3(-0.3f, -1.275f, -1.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel7->GetTransform()->SetScale(Vec3(0.7f, 1.4f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel7);
			//			}
			//			// 벽 패널7
			//			{
			//				DecoObject* pFirstFloorWallPanel8 = Factory::CreateObject<DecoObject>(Vec3(1.f, -1.275f, -1.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pFirstFloorWallPanel8->GetTransform()->SetScale(Vec3(0.7f, 1.4f, 1.f));
			//
			//				AddGameObject(pFirstFloorWallPanel8);
			//			}
			//			// 가운데 문틀
			//			{
			//				DecoObject* pFirstFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(0.35f, -0.775f, -1.075f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");
			//
			//				pFirstFloorDoorFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			//				pFirstFloorDoorFrame->GetTransform()->SetScale(Vec3(0.9f, 0.95f, 1.1f));
			//
			//				AddGameObject(pFirstFloorDoorFrame);
			//			}
			//			// 가운데 문
			//			{
			//				DecoObject* pFirstFloorDoor = Factory::CreateObject<DecoObject>(Vec3(0.35f, -0.775f, -1.075f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");
			//
			//				pFirstFloorDoor->GetTransform()->SetScale(Vec3(0.89f, 0.9f, 1.f));
			//
			//				AddGameObject(pFirstFloorDoor);
			//			}
			//			// 커튼(수평)
			//			{
			//				DecoObject* pFirstFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-1.44f, 1.075f, -3.955f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");
			//
			//				pFirstFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(1.8f, 1.8f, 1.f));
			//
			//				AddGameObject(pFirstFloorCurtainHorizontal);
			//			}
			//			// 커튼(수직)
			//			{
			//				DecoObject* pFirstFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-1.55f, 0.235f, -3.955f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");
			//
			//				pFirstFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorCurtainVertical->GetTransform()->SetScale(Vec3(1.8f, 1.8f, 1.f));
			//
			//				AddGameObject(pFirstFloorCurtainVertical);
			//			}
			//			// 커튼(수평)2
			//			{
			//				DecoObject* pFirstFloorCurtainHorizontal2 = Factory::CreateObject<DecoObject>(Vec3(-1.9f, 1.075f, -2.055f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");
			//
			//				pFirstFloorCurtainHorizontal2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorCurtainHorizontal2->GetTransform()->SetScale(Vec3(1.8f, 1.8f, 1.f));
			//
			//				AddGameObject(pFirstFloorCurtainHorizontal2);
			//			}
			//			// 커튼(수직)2
			//			{
			//				DecoObject* pFirstFloorCurtainVertical2 = Factory::CreateObject<DecoObject>(Vec3(-2.01f, 0.255f, -2.055f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");
			//
			//				pFirstFloorCurtainVertical2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pFirstFloorCurtainVertical2->GetTransform()->SetScale(Vec3(1.368f, 1.168f, 0.76f));
			//
			//				AddGameObject(pFirstFloorCurtainVertical2);
			//			}
		}
		//		// 1층 바닥
		//		{
		//			// 바닥틀
		//			{
		//				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(-0.77f, -1.3f, -4.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (2).fbx");
		//
		//				pFirstFloorPanel->GetTransform()->SetScale(Vec3(1.6f, 1.6f, 1.9f));
		//
		//				AddGameObject(pFirstFloorPanel);
		//			}
		//			// 바닥틀2
		//			{
		//				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(1.55f, -1.29f, -2.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3)-Merged.fbx");
		//
		//				pFirstFloorPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		//				pFirstFloorPanel->GetTransform()->SetScale(Vec3(3.9f, 3.5f, 4.2f));
		//
		//				AddGameObject(pFirstFloorPanel);
		//			}
		// 계단틀
		{
			DecoObject* pFirstFloorRightStairsPanel = Factory::CreateObject<DecoObject>(Vec3(19.05f, -0.85f, -19.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3).fbx");

			pFirstFloorRightStairsPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pFirstFloorRightStairsPanel->GetTransform()->SetScale(Vec3(19.f, 19.f, 19.f));
			SetGizmoTarget(pFirstFloorRightStairsPanel);
			AddGameObject(pFirstFloorRightStairsPanel);
		}
		// 1층 계단(왼쪽)
		{

			Ground* pFirstFloorLeftStairs = Factory::CreateObject<Ground>(Vec3(-9.94f, -0.6f, -19.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pFirstFloorLeftStairs->GetTransform()->SetScale(Vec3(23.f, 21.8f, 23.f));

			AddGameObject(pFirstFloorLeftStairs);
		}

		// 1층 계단(오른쪽)
		{

			Ground* pFirstFloorRightStairs = Factory::CreateObject<Ground>(Vec3(16.1f, -0.6f, -19.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pFirstFloorRightStairs->GetTransform()->SetScale(Vec3(23.f, 21.8f, 23.f));


			AddGameObject(pFirstFloorRightStairs);
		}

		// 1층 기둥(왼쪽 계단)
		{
			DecoObject* pFirstFloorLeftColumn = Factory::CreateObject<DecoObject>(Vec3(-6.f, 1.6f, -29.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pFirstFloorLeftColumn->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pFirstFloorLeftColumn->GetTransform()->SetScale(Vec3(23.85f, 14.3f, 23.85f));
			//SetGizmoTarget(pFirstFloorLeftColumn);
			AddGameObject(pFirstFloorLeftColumn);
		}
		// 1층 기둥(오른쪽 계단)
		{
			DecoObject* pFirstFloorRightColumn = Factory::CreateObject<DecoObject>(Vec3(12.2f, 1.6f, -29.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pFirstFloorRightColumn->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pFirstFloorRightColumn->GetTransform()->SetScale(Vec3(23.85f, 14.3f, 23.85f));

			

			AddGameObject(pFirstFloorRightColumn);
		}
		//#pragma endregion
		//#pragma region 2층
		{
			// 기둥1
			{
				DecoObject* pSecondFloorWallColumn1 = Factory::CreateObject<DecoObject>(Vec3(-6.f, 6.5f, -9.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn1->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn1->GetTransform()->SetScale(Vec3(23.85f, 4.5f, 23.85f));

				
				AddGameObject(pSecondFloorWallColumn1);
			}
			// 기둥2
			{
				DecoObject* pSecondFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(12.2f, 6.5f, -9.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn2->GetTransform()->SetScale(Vec3(23.85f, 4.5f, 23.85f));

				AddGameObject(pSecondFloorWallColumn2);
			}
			// 기둥3(~3층까지)
			{
				DecoObject* pSecondFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(-22.8f, 21.1f, 20.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn3->GetTransform()->SetScale(Vec3(23.85f, 33.7f, 23.85f));
				
				AddGameObject(pSecondFloorWallColumn3);
			}
			// 기둥4
			{
				DecoObject* pSecondFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(-13.7f, 3.2f, -20.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn4->GetTransform()->SetScale(Vec3(23.85f, 29.5f, 23.85f));
				
				AddGameObject(pSecondFloorWallColumn4);
			}
			// 기둥5
			{
				DecoObject* pSecondFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-13.6f, 3.31f, -9.84f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn5->GetTransform()->SetScale(Vec3(23.85f, 29.5f, 23.85f));
				
				AddGameObject(pSecondFloorWallColumn5);
			}
			// 기둥6
			{
				DecoObject* pSecondFloorWallColumn6 = Factory::CreateObject<DecoObject>(Vec3(-22.8f, 11.1f, -9.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn6->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn6->GetTransform()->SetScale(Vec3(23.85f, 14.15f, 23.85f));
				
				AddGameObject(pSecondFloorWallColumn6);
			}

			// 기둥7
			{
				DecoObject* pSecondFloorWallColumn7 = Factory::CreateObject<DecoObject>(Vec3(-11.6f, 10.9f, 20.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn7->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn7->GetTransform()->SetScale(Vec3(23.85f, 13.3f, 23.85f));
				
				AddGameObject(pSecondFloorWallColumn7);
			}

			// 기둥8
			{
				DecoObject* pSecondFloorWallColumn8 = Factory::CreateObject<DecoObject>(Vec3(18.1f, 10.9f, 20.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn8->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn8->GetTransform()->SetScale(Vec3(23.85f, 13.3f, 23.85f));

				//SetGizmoTarget(pSecondFloorWallColumn8);
				AddGameObject(pSecondFloorWallColumn8);
			}

			// 기둥9
			{
				DecoObject* pSecondFloorWallColumn9 = Factory::CreateObject<DecoObject>(Vec3(29.7f, 10.9f, 20.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn9->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn9->GetTransform()->SetScale(Vec3(23.85f, 13.3f, 23.85f));

				AddGameObject(pSecondFloorWallColumn9);
			}
			//			// 천장틀
			//			{
			//				DecoObject* pSecondFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-2.2f, 1.37f, 1.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pSecondFloorWallRim->GetTransform()->SetScale(Vec3(1.f, 1.4f, 1.4f));
			//
			//				AddGameObject(pSecondFloorWallRim);
			//			}
			//			// 천장틀2
			//			{
			//				DecoObject* pSecondFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-2.8f, 1.37f, 3.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
			//
			//				pSecondFloorWallRim2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorWallRim2->GetTransform()->SetScale(Vec3(3.5f, 1.4f, 1.4f));
			//
			//				AddGameObject(pSecondFloorWallRim2);
			//			}
			//			// 벽 패널(바닥틀처럼 보임)
			//			{
			//				DecoObject* pSecondFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-2.75f, -0.31f, 1.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pSecondFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorWallPanel->GetTransform()->SetScale(Vec3(1.4f, 1.4f, 2.f));
			//
			//				AddGameObject(pSecondFloorWallPanel);
			//			}
			//			// 벽 패널2(바닥틀처럼 보임)
			//			{
			//				DecoObject* pSecondFloorWallPanel2 = Factory::CreateObject<DecoObject>(Vec3(-2.75f, -0.31f, 4.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pSecondFloorWallPanel2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorWallPanel2->GetTransform()->SetScale(Vec3(1.5f, 1.4f, 2.f));
			//
			//				AddGameObject(pSecondFloorWallPanel2);
			//			}
			//			// 왼쪽 문틀
			//			{
			//				DecoObject* pSecondFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(-2.74f, 0.29f, 3.025f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");
			//
			//				pSecondFloorDoorFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorDoorFrame->GetTransform()->SetScale(Vec3(1.f, 1.15f, 1.3f));
			//
			//				AddGameObject(pSecondFloorDoorFrame);
			//			}
			//			// 왼쪽 문
			//			{
			//				DecoObject* pSecondFloorDoor = Factory::CreateObject<DecoObject>(Vec3(-2.75f, 0.3f, 3.025f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");
			//
			//				pSecondFloorDoor->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorDoor->GetTransform()->SetScale(Vec3(0.95f, 1.05f, 1.f));
			//
			//				AddGameObject(pSecondFloorDoor);
			//			}
			//			// 왼쪽 문 열쇠구멍
			//			{
			//				DecoObject* pSecondFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(-2.73f, 0.3f, 3.025f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");
			//
			//				pSecondFloorDoorLock->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorDoorLock->GetTransform()->SetScale(Vec3(0.25f, 0.25f, 0.35f));
			//
			//				AddGameObject(pSecondFloorDoorLock);
			//			}
			//			// 벽 패널3
			//			{
			//				DecoObject* pSecondFloorWallPanel3 = Factory::CreateObject<DecoObject>(Vec3(-2.15f, 0.06f, 4.89f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pSecondFloorWallPanel3->GetTransform()->SetScale(Vec3(1.1f, 1.6f, 2.f));
			//
			//				AddGameObject(pSecondFloorWallPanel3);
			//			}
			//			// 벽 패널4
			//			{
			//				DecoObject* pSecondFloorWallPanel4 = Factory::CreateObject<DecoObject>(Vec3(2.85f, 0.06f, 4.89f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
			//
			//				pSecondFloorWallPanel4->GetTransform()->SetScale(Vec3(1.1f, 1.6f, 2.f));
			//
			//				AddGameObject(pSecondFloorWallPanel4);
			//			}
			//			// 계단 벽(좌측)
			//			{
			//				DecoObject* pSecondFloorWall3 = Factory::CreateObject<DecoObject>(Vec3(-0.56f, 0.37f, 6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Cube (1).fbx");
			//
			//				pSecondFloorWall3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorWall3->GetTransform()->SetScale(Vec3(2.2f, 2.2f, 2.f));
			//
			//				AddGameObject(pSecondFloorWall3);
			//			}
			//			// 계단 벽(우측)
			//			{
			//				DecoObject* pSecondFloorWall4 = Factory::CreateObject<DecoObject>(Vec3(1.3f, 0.37f, 6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Cube (1).fbx");
			//
			//				pSecondFloorWall4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorWall4->GetTransform()->SetScale(Vec3(2.2f, 2.2f, 2.f));
			//
			//				AddGameObject(pSecondFloorWall4);
			//			}
			//			// 커튼(수평)
			//			{
			//				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-2.71f, 1.035f, 2.175f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");
			//
			//				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(1.73f, 1.98f, 1.f));
			//
			//				AddGameObject(pSecondFloorCurtainHorizontal);
			//			}
			//			// 커튼(수평)2
			//			{
			//				DecoObject* pSecondFloorCurtainHorizontal2 = Factory::CreateObject<DecoObject>(Vec3(-2.71f, 1.035f, 3.985f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");
			//
			//				pSecondFloorCurtainHorizontal2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			//				pSecondFloorCurtainHorizontal2->GetTransform()->SetScale(Vec3(1.73f, 1.98f, 1.f));
			//
			//				SetGizmoTarget(pSecondFloorCurtainHorizontal2);
			//				AddGameObject(pSecondFloorCurtainHorizontal2);
			//			}
		}
		//		// 2층 바닥
		//		{
		//			// 2층 중앙 난간 상부(가운데)
		//			{
		//				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.4f, 0.17f, -1.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(2.3f, 2.5f, 2.5f));
		//
		//				AddGameObject(pSecondFloorBannisterTop);
		//			}
		//			// 2층 중앙 난간 기둥(가운데)
		//			for (int i = 0; i < 7; i++)
		//			{
		//				DecoObject* pSecondFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-0.45f + (i * 0.28f), 0.01f, -1.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pSecondFloorBannisterStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pSecondFloorBannisterStick);
		//			}
		//			// 2층 중앙 난간 하부(가운데)
		//			{
		//				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(0.4f, -0.14f, -1.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(2.3f, 1.6f, 1.2f));
		//
		//				AddGameObject(pSecondFloorBannisterBase);
		//			}
		//			// 2층 중앙 난간 상부(왼쪽)
		//			{
		//				DecoObject* pSecondFloorLeftBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-0.76f, 0.17f, 0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pSecondFloorLeftBannisterTop->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pSecondFloorLeftBannisterTop->GetTransform()->SetScale(Vec3(2.3f, 2.5f, 2.5f));
		//
		//				AddGameObject(pSecondFloorLeftBannisterTop);
		//			}
		//			// 2층 중앙 난간 기둥(왼쪽)
		//			for (int i = 0; i < 7; i++)
		//			{
		//				DecoObject* pSecondFloorLeftBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-0.75f, 0.01f, -0.8f + (i * 0.34f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pSecondFloorLeftBannisterStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pSecondFloorLeftBannisterStick);
		//			}
		//			// 2층 중앙 난간 끝 기둥(왼쪽)
		//			{
		//				DecoObject* pSecondFloorLeftColumnStump = Factory::CreateObject<DecoObject>(Vec3(-0.75f, 0.11f, 1.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pSecondFloorLeftColumnStump->GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));
		//
		//				AddGameObject(pSecondFloorLeftColumnStump);
		//			}
		//			// 2층 중앙 난간 상부(오른쪽)
		//			{
		//				DecoObject* pSecondFloorRightBannisterTop = Factory::CreateObject<DecoObject>(Vec3(1.5f, 0.17f, 0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pSecondFloorRightBannisterTop->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pSecondFloorRightBannisterTop->GetTransform()->SetScale(Vec3(2.3f, 2.5f, 2.5f));
		//
		//				AddGameObject(pSecondFloorRightBannisterTop);
		//			}
		//			// 2층 중앙 난간 기둥(오른쪽)
		//			for (int i = 0; i < 7; i++)
		//			{
		//				DecoObject* pSecondFloorRightBannisterStick = Factory::CreateObject<DecoObject>(Vec3(1.5f, 0.01f, -0.8f + (i * 0.34f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pSecondFloorRightBannisterStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pSecondFloorRightBannisterStick);
		//			}
		//			// 2층 중앙 난간 하부(오른쪽)
		//			{
		//				DecoObject* pSecondFloorRightBannisterBase = Factory::CreateObject<DecoObject>(Vec3(1.5f, -0.14f, 0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pSecondFloorRightBannisterBase->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pSecondFloorRightBannisterBase->GetTransform()->SetScale(Vec3(2.3f, 1.6f, 1.2f));
		//
		//				AddGameObject(pSecondFloorRightBannisterBase);
		//			}
		//			// 2층 중앙 난간 끝 기둥(오른쪽)
		//			{
		//				DecoObject* pSecondFloorRightColumnStump = Factory::CreateObject<DecoObject>(Vec3(1.5f, 0.11f, 1.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pSecondFloorRightColumnStump->GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));
		//
		//				AddGameObject(pSecondFloorRightColumnStump);
		//			}
		//			// 2층 계단 앞 기둥(왼쪽)
		//			{
		//				DecoObject* pSecondFloorLeftColumnStump2 = Factory::CreateObject<DecoObject>(Vec3(-0.56f, 0.11f, 5.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pSecondFloorLeftColumnStump2->GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));
		//
		//				AddGameObject(pSecondFloorLeftColumnStump2);
		//			}
		//			// 2층 계단 앞 기둥(오른쪽)
		//			{
		//				DecoObject* pSecondFloorRightColumnStump2 = Factory::CreateObject<DecoObject>(Vec3(1.3f, 0.11f, 5.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pSecondFloorRightColumnStump2->GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));
		//
		//				AddGameObject(pSecondFloorRightColumnStump2);
		//			}
		//		}
		// 1층 계단(왼쪽)
		{

			Ground* pSecondFloorLeftStairs = Factory::CreateObject<Ground>(Vec3(-8.2f, 9.2f, 31.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pSecondFloorLeftStairs->GetTransform()->SetScale(Vec3(23.f, 21.8f, 23.f));
			
			AddGameObject(pSecondFloorLeftStairs);
		}

		// 1층 계단(오른쪽)
		{

			Ground* pSecondFloorRightStairs = Factory::CreateObject<Ground>(Vec3(14.6f, 9.2f, 31.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pSecondFloorRightStairs->GetTransform()->SetScale(Vec3(23.f, 21.8f, 23.f));

			AddGameObject(pSecondFloorRightStairs);
		}
		// 2층 계단 난간 상하부(왼쪽)
		{
			DecoObject* pSecondFloorLeftStairRail = Factory::CreateObject<DecoObject>(Vec3(-4.5f, 10.24f, 31.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\StairRail.fbx");

			pSecondFloorLeftStairRail->GetTransform()->SetRotation(Vec3(0.f, -180.f, 0.f));
			pSecondFloorLeftStairRail->GetTransform()->SetScale(Vec3(18.f, 18.f, 18.f));

			AddGameObject(pSecondFloorLeftStairRail);
		}

		// 2층 계단 난간 상하부(오른쪽)
		{
			DecoObject* pSecondFloorRightStairRail = Factory::CreateObject<DecoObject>(Vec3(10.77f, 10.24f, 31.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\StairRail.fbx");

			pSecondFloorRightStairRail->GetTransform()->SetRotation(Vec3(0.f, -180.f, 0.f));
			pSecondFloorRightStairRail->GetTransform()->SetScale(Vec3(18.f, 18.f, 18.f));
			

			AddGameObject(pSecondFloorRightStairRail);
		}

		// 좌측 계단 옆 기둥
		{
			DecoObject* pSecondFloorWallColumn1 = Factory::CreateObject<DecoObject>(Vec3(-4.5f, 6.5f, 21.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pSecondFloorWallColumn1->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pSecondFloorWallColumn1->GetTransform()->SetScale(Vec3(21.2f, 4.5f, 21.2f));
			
			AddGameObject(pSecondFloorWallColumn1);
		}
		// 우측 계단 옆 기둥
		{
			DecoObject* pSecondFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(10.9f, 6.5f, 21.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pSecondFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pSecondFloorWallColumn2->GetTransform()->SetScale(Vec3(21.2f, 4.5f, 21.2f));
			AddGameObject(pSecondFloorWallColumn2);
		}

		//#pragma region 3층

		// 기둥1
		{
			DecoObject* pThirdFloorWallColumn1 = Factory::CreateObject<DecoObject>(Vec3(-11.5f, 15.5f, 41.06f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn1->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pThirdFloorWallColumn1->GetTransform()->SetScale(Vec3(23.85f, 4.05f, 23.85f));
			
			AddGameObject(pThirdFloorWallColumn1);
		}
		// 기둥2
		{
			DecoObject* pThirdFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(-4.67f, 15.5f, 41.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pThirdFloorWallColumn2->GetTransform()->SetScale(Vec3(23.85f, 4.05f, 23.85f));
			
			AddGameObject(pThirdFloorWallColumn2);
		}
		// 기둥3
		{
			DecoObject* pThirdFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(11.f, 15.5f, 41.06f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pThirdFloorWallColumn3->GetTransform()->SetScale(Vec3(23.85f, 4.05f, 23.85f));
			
			AddGameObject(pThirdFloorWallColumn3);
		}
		// 기둥4
		{
			DecoObject* pThirdFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(18.1f, 15.5f, 41.06f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pThirdFloorWallColumn4->GetTransform()->SetScale(Vec3(23.85f, 4.05f, 23.85f));
			
			AddGameObject(pThirdFloorWallColumn4);
		}

		// 기둥5
		{
			DecoObject* pThirdFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-22.81f, 25.5f, 57.43f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pThirdFloorWallColumn5->GetTransform()->SetScale(Vec3(23.85f, 24.9f, 23.85f));
			
			AddGameObject(pThirdFloorWallColumn5);
		}

		// 기둥6
		{
			DecoObject* pThirdFloorWallColumn6 = Factory::CreateObject<DecoObject>(Vec3(29.6f, 25.5f, 57.43f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn6->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			pThirdFloorWallColumn6->GetTransform()->SetScale(Vec3(23.85f, 24.9f, 23.85f));

			AddGameObject(pThirdFloorWallColumn6);
		}


		//			// 천장틀
		//			{
		//				DecoObject* pThirdFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-2.8f, 3.61f, 7.17f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
		//
		//				pThirdFloorWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorWallRim->GetTransform()->SetScale(Vec3(4.2f, 1.4f, 1.4f));
		//
		//				AddGameObject(pThirdFloorWallRim);
		//			}
		//			// 천장틀2
		//			{
		//				DecoObject* pThirdFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(0.4f, 3.61f, 9.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
		//
		//				pThirdFloorWallRim2->GetTransform()->SetScale(Vec3(6.2f, 1.4f, 1.4f));
		//
		//				AddGameObject(pThirdFloorWallRim2);
		//			}
		//			// 벽 패널
		//			for (int i = 0; i < 4; i++)
		//			{
		//				DecoObject* pThirdFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-2.76f, 1.184f, 5.6f + (i * 1.14f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");
		//
		//				pThirdFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorWallPanel->GetTransform()->SetScale(Vec3(1.14f, 1.71f, 1.f));
		//
		//				AddGameObject(pThirdFloorWallPanel);
		//			}
		//			// 벽 패널2
		//			{
		//				DecoObject* pThirdFloorWallPanel2 = Factory::CreateObject<DecoObject>(Vec3(-2.01f, 1.184f, 9.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (5).fbx");
		//
		//				pThirdFloorWallPanel2->GetTransform()->SetScale(Vec3(1.35f, 1.31f, 1.f));
		//
		//				AddGameObject(pThirdFloorWallPanel2);
		//			}
		//			// 벽 패널3
		//			{
		//				DecoObject* pThirdFloorWallPanel3 = Factory::CreateObject<DecoObject>(Vec3(-0.66f, 1.184f, 9.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (6).fbx");
		//
		//				pThirdFloorWallPanel3->GetTransform()->SetScale(Vec3(1.35f, 1.335f, 1.f));
		//
		//				AddGameObject(pThirdFloorWallPanel3);
		//			}
		//			// 가운데 문틀
		//			{
		//				DecoObject* pThirdFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(0.375f, 1.34f, 9.245f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");
		//
		//				pThirdFloorDoorFrame->GetTransform()->SetScale(Vec3(1.06f, 1.15f, 1.3f));
		//
		//				AddGameObject(pThirdFloorDoorFrame);
		//			}
		//			// 가운데 문
		//			{
		//				DecoObject* pThirdFloorDoor = Factory::CreateObject<DecoObject>(Vec3(0.375f, 1.34f, 9.305f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");
		//
		//				pThirdFloorDoor->GetTransform()->SetScale(Vec3(1.02f, 1.05f, 1.f));
		//
		//				AddGameObject(pThirdFloorDoor);
		//			}
		//			// 가운데 문 열쇠구멍
		//			{
		//				DecoObject* pThirdFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(0.375f, 1.35f, 9.295f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");
		//				
		//				pThirdFloorDoorLock->GetTransform()->SetScale(Vec3(0.25f, 0.25f, 0.35f));
		//
		//				AddGameObject(pThirdFloorDoorLock);
		//			}
		//			// 벽 패널4
		//			{
		//				DecoObject* pThirdFloorWallPanel4 = Factory::CreateObject<DecoObject>(Vec3(1.4f, 1.184f, 9.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (5).fbx");
		//
		//				pThirdFloorWallPanel4->GetTransform()->SetScale(Vec3(1.35f, 1.31f, 1.f));
		//
		//				AddGameObject(pThirdFloorWallPanel4);
		//			}
		//			// 벽 패널5
		//			{
		//				DecoObject* pThirdFloorWallPanel5 = Factory::CreateObject<DecoObject>(Vec3(2.75f, 1.184f, 9.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (6).fbx");
		//
		//				pThirdFloorWallPanel5->GetTransform()->SetScale(Vec3(1.35f, 1.335f, 1.f));
		//
		//				AddGameObject(pThirdFloorWallPanel5);
		//			}
		//		}
		//		// 3층 바닥
		//		{

		//			// 바닥틀
		//			{
		//				DecoObject* pThirdFloorPanel = Factory::CreateObject<DecoObject>(Vec3(3.561f, 0.87f, 7.096f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (2).fbx");
		//
		//				pThirdFloorPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorPanel->GetTransform()->SetScale(Vec3(4.3f, 1.35f, 1.6f));
		//
		//				AddGameObject(pThirdFloorPanel);
		//			}
		//			// 좌측 난간 하부
		//			{
		//				DecoObject* pThirdFloorLeftBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-2.12f, 0.98f, 4.976f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pThirdFloorLeftBannisterBase->GetTransform()->SetScale(Vec3(1.22f, 1.75f, 1.39f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterBase);
		//			}
		//			// 좌측 난간 기둥
		//			for (int i = 0; i < 4; i++)
		//			{
		//				DecoObject* pThirdFloorLeftBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-1.78f - (i * 0.27f), 1.11f, 4.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pThirdFloorLeftBannisterStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterStick);
		//			}
		//			// 좌측 난간 상부
		//			{
		//				DecoObject* pThirdFloorLeftBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-2.12f, 1.27f, 4.975f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pThirdFloorLeftBannisterTop->GetTransform()->SetScale(Vec3(1.22f, 2.f, 2.3f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterTop);
		//			}
		//			// 좌측 난간 하부2
		//			{
		//				DecoObject* pThirdFloorLeftBannisterBase2 = Factory::CreateObject<DecoObject>(Vec3(-1.44f, 0.97f, 6.086f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pThirdFloorLeftBannisterBase2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorLeftBannisterBase2->GetTransform()->SetScale(Vec3(2.22f, 1.75f, 1.39f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterBase2);
		//			}
		//			// 좌측 난간 기둥2
		//			for (int i = 0; i < 7; i++)
		//			{
		//				DecoObject* pThirdFloorLeftBannisterStick2 = Factory::CreateObject<DecoObject>(Vec3(-1.44f, 1.11f, 5.27f + (i * 0.27f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pThirdFloorLeftBannisterStick2->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterStick2);
		//			}
		//			// 좌측 난간 상부2
		//			{
		//				DecoObject* pThirdFloorLeftBannisterTop2 = Factory::CreateObject<DecoObject>(Vec3(-1.44f, 1.27f, 6.075f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pThirdFloorLeftBannisterTop2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorLeftBannisterTop2->GetTransform()->SetScale(Vec3(2.22f, 2.f, 2.3f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterTop2);
		//			}
		//			// 좌측 난간 끝 기둥
		//			{
		//				DecoObject* pThirdFloorLeftColumnStump = Factory::CreateObject<DecoObject>(Vec3(-1.44f, 1.22f, 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pThirdFloorLeftColumnStump->GetTransform()->SetScale(Vec3(0.6f, 0.59f, 0.6f));
		//
		//				AddGameObject(pThirdFloorLeftColumnStump);
		//			}
		//			// 우측 난간 하부
		//			{
		//				DecoObject* pThirdFloorRightBannisterBase = Factory::CreateObject<DecoObject>(Vec3(2.88f, 0.98f, 4.976f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pThirdFloorRightBannisterBase->GetTransform()->SetScale(Vec3(1.22f, 1.75f, 1.39f));
		//
		//				AddGameObject(pThirdFloorRightBannisterBase);
		//			}
		//			// 우측 난간 기둥
		//			for (int i = 0; i < 4; i++)
		//			{
		//				DecoObject* pThirdFloorRightBannisterStick = Factory::CreateObject<DecoObject>(Vec3(3.26f - (i * 0.27f), 1.11f, 4.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pThirdFloorRightBannisterStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pThirdFloorRightBannisterStick);
		//			}
		//			// 우측 난간 상부
		//			{
		//				DecoObject* pThirdFloorRightBannisterTop = Factory::CreateObject<DecoObject>(Vec3(2.88f, 1.27f, 4.975f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pThirdFloorRightBannisterTop->GetTransform()->SetScale(Vec3(1.22f, 2.f, 2.3f));
		//
		//				AddGameObject(pThirdFloorRightBannisterTop);
		//			}
		//			// 우측 난간 하부2
		//			{
		//				DecoObject* pThirdFloorRightBannisterBase2 = Factory::CreateObject<DecoObject>(Vec3(2.19f, 0.97f, 6.086f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pThirdFloorRightBannisterBase2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorRightBannisterBase2->GetTransform()->SetScale(Vec3(2.22f, 1.75f, 1.39f));
		//
		//				AddGameObject(pThirdFloorRightBannisterBase2);
		//			}
		//			// 우측 난간 기둥2
		//			for (int i = 0; i < 7; i++)
		//			{
		//				DecoObject* pThirdFloorLeftBannisterStick2 = Factory::CreateObject<DecoObject>(Vec3(2.19f, 1.11f, 5.27f + (i * 0.27f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pThirdFloorLeftBannisterStick2->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterStick2);
		//			}
		//			// 우측 난간 상부2
		//			{
		//				DecoObject* pThirdFloorLeftBannisterTop2 = Factory::CreateObject<DecoObject>(Vec3(2.19f, 1.27f, 6.075f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pThirdFloorLeftBannisterTop2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
		//				pThirdFloorLeftBannisterTop2->GetTransform()->SetScale(Vec3(2.22f, 2.f, 2.3f));
		//
		//				AddGameObject(pThirdFloorLeftBannisterTop2);
		//			}
		//			// 우측 난간 끝 기둥
		//			{
		//				DecoObject* pThirdFloorRightColumnStump = Factory::CreateObject<DecoObject>(Vec3(2.19f, 1.22f, 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pThirdFloorRightColumnStump->GetTransform()->SetScale(Vec3(0.6f, 0.59f, 0.6f));
		//
		//				AddGameObject(pThirdFloorRightColumnStump);
		//			}
		//			// 중앙 난간 하부
		//			{
		//				DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(0.38f, 0.97f, 7.19f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");
		//
		//				pThirdFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		//				pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(2.f, 1.6f, 1.2f));
		//
		//				AddGameObject(pThirdFloorBannisterBase);
		//			}
		//			// 중앙 난간 기둥
		//			for (int i = 0; i < 5; i++)
		//			{
		//				DecoObject* pThirdFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-0.23f + (i * 0.3f), 1.17f, 7.19f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
		//
		//				pThirdFloorBannisterStick->GetTransform()->SetScale(Vec3(0.3f, 0.32f, 0.3f));
		//
		//				AddGameObject(pThirdFloorBannisterStick);
		//			}
		//			// 중앙 난간 상부
		//			{
		//				DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.38f, 1.34f, 7.19f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
		//
		//				pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(1.8f, 2.5f, 2.5f));
		//
		//				AddGameObject(pThirdFloorBannisterTop);
		//			}
		//			// 중앙 난간 끝 기둥(좌측)
		//			{
		//				DecoObject* pThirdFloorLeftColumnStump2 = Factory::CreateObject<DecoObject>(Vec3(-0.56f, 1.22f, 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pThirdFloorLeftColumnStump2->GetTransform()->SetScale(Vec3(0.6f, 0.59f, 0.6f));
		//
		//				AddGameObject(pThirdFloorLeftColumnStump2);
		//			}
		//			// 중앙 난간 끝 기둥(우측)
		//			{
		//				DecoObject* pThirdFloorRightColumnStump2 = Factory::CreateObject<DecoObject>(Vec3(1.29f, 1.22f, 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");
		//
		//				pThirdFloorRightColumnStump2->GetTransform()->SetScale(Vec3(0.6f, 0.59f, 0.6f));
		//
		//				AddGameObject(pThirdFloorRightColumnStump2);
		//			}
		//		}
#pragma endregion

		// Toy
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.2f, 0.2f, 0.2f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 1.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

			AddGameObject(pPlayer);
		}*/
	}

	void HallColliderCheckMap::Exit()
	{
	}
}