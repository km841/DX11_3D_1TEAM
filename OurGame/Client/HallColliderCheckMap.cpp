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

#pragma region 1층
		// 1층 벽
		{
			// 1, 2층 벽
			{
				DecoObject* pFirstFloorWall = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main.fbx");

				pFirstFloorWall->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
				pFirstFloorWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				pFirstFloorWall->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pFirstFloorWall->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));

				AddGameObject(pFirstFloorWall);
			}
			// 1층 벽2
			{
				DecoObject* pFirstFloorWall2 = Factory::CreateObject<DecoObject>(Vec3(-1.88f, 0.07f, -2.11f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main-detach (1).fbx", true);

				pFirstFloorWall2->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorWall2->GetTransform()->SetScale(Vec3(1.f, 2.6f, 2.75f));

				pFirstFloorWall2->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pFirstFloorWall2->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));

				AddGameObject(pFirstFloorWall2);
			}
			// 기둥
			{
				DecoObject* pFirstFloorWallColumn = Factory::CreateObject<DecoObject>(Vec3(-1.59f, 0.02f, -4.91f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn->GetTransform()->SetScale(Vec3(2.8f, 2.85f, 2.8f));

				AddGameObject(pFirstFloorWallColumn);
			}
			// 기둥2
			{
				DecoObject* pFirstFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(-1.59f, 0.02f, -3.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn2->GetTransform()->SetScale(Vec3(2.8f, 2.85f, 2.8f));

				AddGameObject(pFirstFloorWallColumn2);
			}
			// 기둥3
			{
				DecoObject* pFirstFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(-2.05f, 0.02f, -3.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn3->GetTransform()->SetScale(Vec3(2.8f, 2.85f, 2.8f));

				AddGameObject(pFirstFloorWallColumn3);
			}
			// 기둥4
			{
				DecoObject* pFirstFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(-2.05f, 0.02f, -1.16f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn4->GetTransform()->SetScale(Vec3(2.8f, 2.85f, 2.8f));

				AddGameObject(pFirstFloorWallColumn4);
			}
			// 기둥5
			{
				DecoObject* pFirstFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-1.62f, 0.02f, -1.17f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorWallColumn5->GetTransform()->SetScale(Vec3(2.8f, 2.85f, 2.8f));

				AddGameObject(pFirstFloorWallColumn5);
			}
			// õ�� Ʋ
			{
				DecoObject* pFirstFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-1.6f, 1.37f, -3.97f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim->GetTransform()->SetScale(Vec3(1.7f, 1.4f, 1.4f));

				AddGameObject(pFirstFloorWallRim);
			}
			// õ�� Ʋ2
			{
				DecoObject* pFirstFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-1.8f, 1.37f, -3.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim2->GetTransform()->SetScale(Vec3(0.5f, 1.4f, 1.4f));

				AddGameObject(pFirstFloorWallRim2);
			}
			// õ�� Ʋ3
			{
				DecoObject* pFirstFloorWallRim3 = Factory::CreateObject<DecoObject>(Vec3(-2.05f, 1.37f, -2.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim3->GetTransform()->SetScale(Vec3(1.7f, 1.4f, 1.4f));

				AddGameObject(pFirstFloorWallRim3);
			}
			// õ�� Ʋ4
			{
				DecoObject* pFirstFloorWallRim4 = Factory::CreateObject<DecoObject>(Vec3(-1.8f, 1.37f, -1.16f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim4->GetTransform()->SetScale(Vec3(0.5f, 1.4f, 1.4f));

				AddGameObject(pFirstFloorWallRim4);
			}
			// õ�� Ʋ5(1, 2�� ����)
			{
				DecoObject* pFirstFloorWallRim5 = Factory::CreateObject<DecoObject>(Vec3(-1.62f, 1.37f, 0.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim5->GetTransform()->SetScale(Vec3(2.3f, 1.4f, 1.4f));

				AddGameObject(pFirstFloorWallRim5);
			}
			// �� �г�
			{
				DecoObject* pFirstFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-1.55f, -0.975f, -4.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));

				AddGameObject(pFirstFloorWallPanel);
			}
			// �� �г�2
			{
				DecoObject* pFirstFloorWallPanel2 = Factory::CreateObject<DecoObject>(Vec3(-1.55f, -0.975f, -3.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel2->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));

				AddGameObject(pFirstFloorWallPanel2);
			}
			// �� �г�3
			{
				DecoObject* pFirstFloorWallPanel3 = Factory::CreateObject<DecoObject>(Vec3(-2.04f, -0.975f, -2.83f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel3->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));

				AddGameObject(pFirstFloorWallPanel3);
			}
			// �� �г�4
			{
				DecoObject* pFirstFloorWallPanel4 = Factory::CreateObject<DecoObject>(Vec3(-2.04f, -0.975f, -1.34f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel4->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel4->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));

				AddGameObject(pFirstFloorWallPanel4);
			}
			// �� �г�5
			{
				DecoObject* pFirstFloorWallPanel5 = Factory::CreateObject<DecoObject>(Vec3(-2.04f, -0.808f, -2.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (12).fbx");

				pFirstFloorWallPanel5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel5->GetTransform()->SetScale(Vec3(0.5f, 0.46f, 0.25f));

				AddGameObject(pFirstFloorWallPanel5);
			}
			// �� �г�6
			{
				DecoObject* pFirstFloorWallPanel6 = Factory::CreateObject<DecoObject>(Vec3(-2.15f, -0.975f, -1.24f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel6->GetTransform()->SetScale(Vec3(1.f, 1.7f, 1.f));

				AddGameObject(pFirstFloorWallPanel6);
			}
			// öâ
			{
				DecoObject* pSpikeDoor = Factory::CreateObject<DecoObject>(Vec3(-2.07f, -1.17f, -2.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\SpikeDoor.fbx");

				pSpikeDoor->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
				pSpikeDoor->GetTransform()->SetScale(Vec3(1.f, 0.9f, 0.8f));

				AddGameObject(pSpikeDoor);
			}
			// �� �г�7
			{
				DecoObject* pFirstFloorWallPanel7 = Factory::CreateObject<DecoObject>(Vec3(-0.3f, -1.275f, -1.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel7->GetTransform()->SetScale(Vec3(0.7f, 1.4f, 1.f));

				AddGameObject(pFirstFloorWallPanel7);
			}
			// �� �г�8
			{
				DecoObject* pFirstFloorWallPanel8 = Factory::CreateObject<DecoObject>(Vec3(1.f, -1.275f, -1.09f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel8->GetTransform()->SetScale(Vec3(0.7f, 1.4f, 1.f));

				AddGameObject(pFirstFloorWallPanel8);
			}
			// ��� ��Ʋ
			{
				DecoObject* pFirstFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(0.35f, -0.775f, -1.075f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

				pFirstFloorDoorFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorDoorFrame->GetTransform()->SetScale(Vec3(0.9f, 0.95f, 1.1f));

				AddGameObject(pFirstFloorDoorFrame);
			}
			// ��� ��
			{
				DecoObject* pFirstFloorDoor = Factory::CreateObject<DecoObject>(Vec3(0.35f, -0.775f, -1.075f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

				pFirstFloorDoor->GetTransform()->SetScale(Vec3(0.89f, 0.9f, 1.f));

				AddGameObject(pFirstFloorDoor);
			}
		}
		// 1층 바닥
		{
			// 1층 바닥
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(5.f, 0.1f, 5.f);

				Ground* pFirstFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.14f, -1.3f, -2.82f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor Lower.fbx");

				pFirstFloor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloor->GetTransform()->SetScale(Vec3(5.1f, 5.f, 5.1f));

				pFirstFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pFirstFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(154.f, 140.f, 105.f));

				AddGameObject(pFirstFloor);
			}
			// 바닥틀
			{
				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(-0.77f, -1.3f, -4.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (2).fbx");

				pFirstFloorPanel->GetTransform()->SetScale(Vec3(1.6f, 1.6f, 1.9f));

				AddGameObject(pFirstFloorPanel);
			}
			// 바닥틀2
			{
				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(1.55f, -1.29f, -2.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3)-Merged.fbx");

				pFirstFloorPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorPanel->GetTransform()->SetScale(Vec3(3.9f, 3.5f, 4.2f));

				AddGameObject(pFirstFloorPanel);
			}
			// 계단틀
			{
				DecoObject* pFirstFloorRightStairsPanel = Factory::CreateObject<DecoObject>(Vec3(2.345f, -0.771f, -0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3).fbx");

				pFirstFloorRightStairsPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorRightStairsPanel->GetTransform()->SetScale(Vec3(2.3f, 2.09f, 2.35f));

				AddGameObject(pFirstFloorRightStairsPanel);
			}
		}
		// 1층 계단(왼쪽)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pFirstFloorLeftStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-1.15f, -0.75f, 0.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pFirstFloorLeftStairs->GetTransform()->SetRotation(Vec3(-24.2f, 0.f, 0.f));
			pFirstFloorLeftStairs->GetTransform()->SetScale(Vec3(2.6f, 2.4f, 2.65f));
			pFirstFloorLeftStairs->GetTransform()->SetRotationExcludingColliders(Vec3(24.2f, 0.f, 0.f));
			pFirstFloorLeftStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));

			AddGameObject(pFirstFloorLeftStairs);
		}
		// 1층 계단(오른쪽)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pFirstFloorRightStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.94f, -0.75f, 0.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pFirstFloorRightStairs->GetTransform()->SetRotation(Vec3(-24.2f, 0.f, 0.f));
			pFirstFloorRightStairs->GetTransform()->SetScale(Vec3(2.7f, 2.4f, 2.65f));
			pFirstFloorRightStairs->GetTransform()->SetRotationExcludingColliders(Vec3(24.2f, 0.f, 0.f));
			pFirstFloorRightStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));

			AddGameObject(pFirstFloorRightStairs);
		}
#pragma endregion
#pragma region 2��
		// 2�� ��
		{
			// 2�� ��2
			{
				DecoObject* pSecondFloorWall = Factory::CreateObject<DecoObject>(Vec3(-2.1f, 0.215f, -1.66f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main (1).fbx");

				pSecondFloorWall->GetTransform()->SetScale(Vec3(6.2f, 6.45f, 10.f));
				pSecondFloorWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				AddGameObject(pSecondFloorWall);
			}
			// ���
			{
				DecoObject* pSecondFloorWallColumn = Factory::CreateObject<DecoObject>(Vec3(-1.6f, 0.62f, 1.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (10).fbx");

				pSecondFloorWallColumn->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn->GetTransform()->SetScale(Vec3(1.6f, 1.65f, 1.6f));

				AddGameObject(pSecondFloorWallColumn);
			}
			// ���2
			{
				DecoObject* pSecondFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(-2.8f, 0.62f, 1.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (10).fbx");

				pSecondFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn2->GetTransform()->SetScale(Vec3(1.6f, 1.65f, 1.6f));

				AddGameObject(pSecondFloorWallColumn2);
			}
			// ���3(~3��)
			{
				DecoObject* pSecondFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(-2.79f, 1.77f, 4.94f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnInnerCorner.fbx");

				pSecondFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pSecondFloorWallColumn3->GetTransform()->SetScale(Vec3(4.1f, 3.9f, 4.f));

				AddGameObject(pSecondFloorWallColumn3);
			}
			// ���4
			{
				DecoObject* pSecondFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(-1.49f, 0.57f, 4.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (10).fbx");

				pSecondFloorWallColumn4->GetTransform()->SetScale(Vec3(1.6f, 1.55f, 1.6f));

				AddGameObject(pSecondFloorWallColumn4);
			}
			// ���5
			{
				DecoObject* pSecondFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(2.21f, 0.52f, 4.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnFull (18).fbx");

				pSecondFloorWallColumn5->AddComponent<PlacementScript>();
				pSecondFloorWallColumn5->GetTransform()->SetScale(Vec3(1.7f, 1.7f, 1.6f));

				AddGameObject(pSecondFloorWallColumn5);
			}
			// ���6
			{
				DecoObject* pSecondFloorWallColumn6 = Factory::CreateObject<DecoObject>(Vec3(3.51f, 0.52f, 4.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnFull (18).fbx");

				pSecondFloorWallColumn6->GetTransform()->SetScale(Vec3(1.7f, 1.7f, 1.6f));

				AddGameObject(pSecondFloorWallColumn6);
			}
			// õ�� Ʋ
			{
				DecoObject* pSecondFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-2.2f, 1.37f, 1.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pSecondFloorWallRim->GetTransform()->SetScale(Vec3(1.f, 1.4f, 1.4f));

				AddGameObject(pSecondFloorWallRim);
			}
			// õ�� Ʋ2
			{
				DecoObject* pSecondFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-2.8f, 1.37f, 3.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pSecondFloorWallRim2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorWallRim2->GetTransform()->SetScale(Vec3(3.5f, 1.4f, 1.4f));

				AddGameObject(pSecondFloorWallRim2);
			}
			// �� �г�(�ٴ� Ʋó�� ����)
			{
				DecoObject* pSecondFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-2.75f, -0.31f, 1.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorWallPanel->GetTransform()->SetScale(Vec3(1.4f, 1.4f, 2.f));

				AddGameObject(pSecondFloorWallPanel);
			}
			// �� �г�2(�ٴ� Ʋó�� ����)
			{
				DecoObject* pSecondFloorWallPanel2 = Factory::CreateObject<DecoObject>(Vec3(-2.75f, -0.31f, 4.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorWallPanel2->GetTransform()->SetScale(Vec3(1.5f, 1.4f, 2.f));

				AddGameObject(pSecondFloorWallPanel2);
			}
			// ���� ��Ʋ
			{
				DecoObject* pSecondFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(-2.74f, 0.29f, 3.025f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

				pSecondFloorDoorFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorDoorFrame->GetTransform()->SetScale(Vec3(1.f, 1.15f, 1.3f));

				AddGameObject(pSecondFloorDoorFrame);
			}
			// ���� ��
			{
				DecoObject* pSecondFloorDoor = Factory::CreateObject<DecoObject>(Vec3(-2.75f, 0.3f, 3.025f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

				pSecondFloorDoor->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorDoor->GetTransform()->SetScale(Vec3(0.95f, 1.05f, 1.f));

				AddGameObject(pSecondFloorDoor);
			}
			// ���� �� ���豸��
			{
				DecoObject* pSecondFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(-2.73f, 0.3f, 3.025f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

				pSecondFloorDoorLock->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorDoorLock->GetTransform()->SetScale(Vec3(0.25f, 0.25f, 0.35f));

				AddGameObject(pSecondFloorDoorLock);
			}
			// �� �г�3
			{
				DecoObject* pSecondFloorWallPanel3 = Factory::CreateObject<DecoObject>(Vec3(-2.15f, 0.06f, 4.89f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel3->GetTransform()->SetScale(Vec3(1.1f, 1.6f, 2.f));

				AddGameObject(pSecondFloorWallPanel3);
			}
			// �� �г�4
			{
				DecoObject* pSecondFloorWallPanel4 = Factory::CreateObject<DecoObject>(Vec3(2.85f, 0.06f, 4.89f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel4->GetTransform()->SetScale(Vec3(1.1f, 1.6f, 2.f));

				AddGameObject(pSecondFloorWallPanel4);
			}
		}
		// 2층 바닥
		{
			// 2�� �ٴ�
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				//info.size = Vec3(7.8f, 0.1f, 8.4f);

				Ground* pSecondFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.34f, -0.23f, 3.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor.fbx", true);

				pSecondFloor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 180.f));
				pSecondFloor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, -0.98f));
				pSecondFloor->GetTransform()->SetScale(Vec3(10.3f, 5.f, 10.3f));

				pSecondFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr, 1, 0);
				pSecondFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(154.f, 140.f, 105.f), 1, 0);

				AddGameObject(pSecondFloor);
			}
			// �ٴ�Ʋ
			{
				DecoObject* pSecondFloorPanel = Factory::CreateObject<DecoObject>(Vec3(2.963f, -0.25f, 1.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionComplexCornerEdge.fbx");

				pSecondFloorPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pSecondFloorPanel->GetTransform()->SetScale(Vec3(2.1f, 1.9f, 2.19f));

				AddGameObject(pSecondFloorPanel);
			}
			// �ٴ�Ʋ2
			{
				DecoObject* pSecondFloorPanel2 = Factory::CreateObject<DecoObject>(Vec3(3.581f, -0.25f, 4.076f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (2).fbx");

				pSecondFloorPanel2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorPanel2->GetTransform()->SetScale(Vec3(1.5f, 1.35f, 1.49f));

				AddGameObject(pSecondFloorPanel2);
			}
			// 2�� �߾� ���� ���(���)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.4f, 0.17f, -1.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(2.3f, 2.5f, 2.5f));

				AddGameObject(pSecondFloorBannisterTop);
			}
			// 2�� �߾� ���� ���(���)
			for (int i = 0; i < 7; i++)
			{
				DecoObject* pSecondFloorColumnStick = Factory::CreateObject<DecoObject>(Vec3(-0.45f + (i * 0.28f), 0.01f, -1.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

				pSecondFloorColumnStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));

				AddGameObject(pSecondFloorColumnStick);
			}
			// 2�� �߾� ���� �Ϻ�(���)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(0.4f, -0.14f, -1.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(2.3f, 1.6f, 1.2f));

				AddGameObject(pSecondFloorBannisterBase);
			}
			// 2�� �߾� ���� ���(����)
			{
				DecoObject* pSecondFloorLeftBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-0.76f, 0.17f, 0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorLeftBannisterTop->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorLeftBannisterTop->GetTransform()->SetScale(Vec3(2.3f, 2.5f, 2.5f));

				AddGameObject(pSecondFloorLeftBannisterTop);
			}
			// 2�� �߾� ���� ���(����)
			for (int i = 0; i < 7; i++)
			{
				DecoObject* pSecondFloorLeftColumnStick = Factory::CreateObject<DecoObject>(Vec3(-0.75f, 0.01f, -0.8f + (i * 0.34f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

				pSecondFloorLeftColumnStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));

				pSecondFloorLeftBannisterBase->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorLeftBannisterBase->GetTransform()->SetScale(Vec3(2.3f, 1.6f, 1.2f));

				AddGameObject(pSecondFloorLeftBannisterBase);
			}
			// 2�� �߾� ���� �� ���(����)
			{
				DecoObject* pSecondFloorLeftColumnStump = Factory::CreateObject<DecoObject>(Vec3(-0.75f, 0.11f, 1.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");

				pSecondFloorLeftColumnStump->GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));

				AddGameObject(pSecondFloorLeftColumnStump);
			}
			// 2�� �߾� ���� ���(������)
			{
				DecoObject* pSecondFloorRightBannisterTop = Factory::CreateObject<DecoObject>(Vec3(1.5f, 0.17f, 0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorRightBannisterTop->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorRightBannisterTop->GetTransform()->SetScale(Vec3(2.3f, 2.5f, 2.5f));

				AddGameObject(pSecondFloorRightBannisterTop);
			}
			// 2�� �߾� ���� ���(������)
			for (int i = 0; i < 7; i++)
			{
				DecoObject* pSecondFloorRightColumnStick = Factory::CreateObject<DecoObject>(Vec3(1.5f, 0.01f, -0.8f + (i * 0.34f)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

				pSecondFloorRightColumnStick->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));

				AddGameObject(pSecondFloorRightColumnStick);
			}
			// 2�� �߾� ���� �Ϻ�(������)
			{
				DecoObject* pSecondFloorRightBannisterBase = Factory::CreateObject<DecoObject>(Vec3(1.5f, -0.14f, 0.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorRightBannisterBase->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorRightBannisterBase->GetTransform()->SetScale(Vec3(2.3f, 1.6f, 1.2f));

				AddGameObject(pSecondFloorRightBannisterBase);
			}
			// 2�� �߾� ���� �� ���(������)
			{
				DecoObject* pSecondFloorRightColumnStump = Factory::CreateObject<DecoObject>(Vec3(1.5f, 0.11f, 1.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ColumnStump (7).fbx");

				pSecondFloorRightColumnStump->GetTransform()->SetScale(Vec3(0.6f, 0.6f, 0.6f));

				AddGameObject(pSecondFloorRightColumnStump);
			}
		}
		// 2층 계단(왼쪽)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pSecondFloorLeftStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-1.f, 0.35f, 6.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pSecondFloorLeftStairs->AddComponent<PlacementScript>();
			pSecondFloorLeftStairs->GetTransform()->SetRotation(Vec3(-24.2f, 0.f, 0.f));
			pSecondFloorLeftStairs->GetTransform()->SetScale(Vec3(2.7f, 2.4f, 2.55f));
			pSecondFloorLeftStairs->GetTransform()->SetRotationExcludingColliders(Vec3(24.2f, 0.f, 0.f));
			pSecondFloorLeftStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));
			AddGameObject(pSecondFloorLeftStairs);
		}

		// 2층 계단(왼쪽)
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 0.1f, 2.5f);

			Ground* pSecondFloorRightStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.75f, 0.33f, 6.1f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

			pSecondFloorRightStairs->GetTransform()->SetRotation(Vec3(-26.5f, 0.f, 0.f));
			pSecondFloorRightStairs->GetTransform()->SetScale(Vec3(2.7f, 2.6f, 2.55f));
			pSecondFloorRightStairs->GetTransform()->SetRotationExcludingColliders(Vec3(27.f, 0.f, 0.f));
			pSecondFloorRightStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.045f, -0.1f));
			
			AddGameObject(pSecondFloorRightStairs);
		}
#pragma endregion
#pragma region 3층
		// 3층 벽
		{
			DecoObject* pThirdFloorWall = Factory::CreateObject<DecoObject>(Vec3(0.4f, 1.7f, 7.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TopFloor.fbx");

			pThirdFloorWall->GetTransform()->SetScale(Vec3(6.1f, 6.f, 6.35f));
			pThirdFloorWall->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pThirdFloorWall);
		}
		// 3층 벽2
		{
			DecoObject* pThirdFloorWall2 = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.15f, 7.11f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TopFloor-detach.fbx");

			pThirdFloorWall2->GetTransform()->SetScale(Vec3(4.35f, 4.3f, 6.35f));
			pThirdFloorWall2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pThirdFloorWall2);
		}
		// 3층 바닥
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.1f, 0.1f, 6.4f);

			Ground* pThirdFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.4f, 0.85f, 7.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor Upper 2.fbx");
			
			pThirdFloor->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pThirdFloor->GetTransform()->SetScale(Vec3(6.1f, 5.f, 6.4f));

			pThirdFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pThirdFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(154.f, 140.f, 105.f));

			AddGameObject(pThirdFloor);
		}
#pragma endregion

		// Toy
		/*{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.2f, 0.2f, 0.2f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 1.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(0.2f, 0.2f, 0.2f));

			AddGameObject(pPlayer);
		}*/
	}

	void HallColliderCheckMap::Exit()
	{
	}
}