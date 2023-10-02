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
#include "Npc.h"
#include "Monster.h"
#include "SwordHeavyEffect.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "PaperBurnScript.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"

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

	void HallColliderCheckMap::Start()
	{
		SetDirLightPosition(Vec3(20.7f, 53.4f, 69.3f));
		SetDirLightRotation(Vec3(38.3f, 199.57f, 167.5f));
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

		DisableDirLight();
		InitObjectAdd();
		InitColliderAdd();
		FuncObjectAdd();
		//배경맵 하얀색으로 만들어주는 코드
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));
	}

	void HallColliderCheckMap::InitObjectAdd()
	{
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

		// Door
		{
			DecoObject* pDoor = Factory::CreateObject<DecoObject>(Vec3(2.8f, 15.3f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\ShortcutDoor_Fix.fbx");
			pDoor->AddComponent(new PaperBurnScript);

			PaperBurnScript* pScript = pDoor->GetScript<PaperBurnScript>();
			pScript->SetReverse(true);
			pScript->SetPaperBurn();

			pDoor->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pDoor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pDoor);
			SetMeshTarget(pDoor);
		}

		// Door Back Glow
		{
			DecoObject* pDoor = Factory::CreateObject<DecoObject>(Vec3(2.8f, 15.3f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\DoorBackGlow.fbx");

			pDoor->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
			pDoor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			pDoor->GetMeshRenderer()->GetMaterial()->SetBloom(true);
			pDoor->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f));

			AddGameObject(pDoor);
		}

		//Player
		{
			//PhysicsInfo physicsInfo;
			//physicsInfo.eActorType = ActorType::Kinematic;
			//physicsInfo.eGeometryType = GeometryType::Capsule;
			//physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			//Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			////Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow_Fix.fbx");
			//PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			//pPlayer->AddComponent(new PaperBurnScript);
			//pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			//pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			//pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));

			//pPlayer->GetRigidBody()->ApplyGravity();
			//pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			//pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			//AddGameObject(pPlayer);
		}

		// Sword_Heavy
		{
			SwordHeavyEffect* pSlashTest = Factory::CreateObject<SwordHeavyEffect>(Vec3(0.f, 8.f, 0.f), L"PlayerSlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbx");
			pSlashTest->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pSlashTest->AddComponent(new PlayerSlashScript);
			auto pFollowScript = pSlashTest->AddComponent(new OwnerFollowScript(PLAYER));
			pFollowScript->SetOffset(Vec3(0.f, 1.f, 0.f));

			pSlashTest->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::Clamp);

			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"HeavySlash", L"..\\Resources\\FBX\\Player\\Slash_Heavy.fbm\\sword_slash_texture_1.png");
			pSlashTest->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			pSlashTest->GetRigidBody()->RemoveGravity();
			AddGameObject(pSlashTest);
		}

		// Toy
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Static;
		//	physicsInfo.eGeometryType = GeometryType::Box;
		//	physicsInfo.size = Vec3(2.f, 2.f, 2.f);

		//	Monster* pPlayer = Factory::CreateObjectHasPhysical<Monster>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
		//	//pPlayer->AddComponent(new TestAnimationScript);
		//	pPlayer->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		//	AddGameObject(pPlayer);
		//}

#pragma region 1층
		// 1층 벽
		{
			// 1, 2층 벽
			{
				DecoObject* pTotalFrame = Factory::CreateObject<DecoObject>(Vec3(2.8f, 15.3f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MapFrame.fbx");

				pTotalFrame->GetTransform()->SetScale(Vec3(130.f, 130.f, 130.f));
				pTotalFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				pTotalFrame->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pTotalFrame->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));


				AddGameObject(pTotalFrame);

			}

			// 숨은통로
			{
				DecoObject* pSecretPassage = Factory::CreateObject<DecoObject>(Vec3(-13.f, 5.94f, -37.85f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main-detach (1).fbx");

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

			// 천장틀
			{
				DecoObject* pFirstFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-12.9f, 17.f, -53.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
				pFirstFloorWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));

				AddGameObject(pFirstFloorWallRim);
			}
			// 천장틀2
			{
				DecoObject* pFirstFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-17.f, 17.f, -38.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
				//SetGizmoTarget(pFirstFloorWallRim2);
				pFirstFloorWallRim2->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim2->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));

				AddGameObject(pFirstFloorWallRim2);
			}
			// 천장틀3
			{
				DecoObject* pFirstFloorWallRim3 = Factory::CreateObject<DecoObject>(Vec3(-13.4f, 17.f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim3->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim3->GetTransform()->SetScale(Vec3(19.35f, 14.f, 14.f));

				AddGameObject(pFirstFloorWallRim3);
			}
			// 천장틀4
			{
				DecoObject* pFirstFloorWallRim4 = Factory::CreateObject<DecoObject>(Vec3(-18.3f, 15.6f, -9.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim4->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorWallRim4->GetTransform()->SetScale(Vec3(8.12f, 14.f, 14.f));

				AddGameObject(pFirstFloorWallRim4);
			}
			// 천장틀5
			{
				DecoObject* pFirstFloorWallRim5 = Factory::CreateObject<DecoObject>(Vec3(-22.8f, 17.1f, 5.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim5->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallRim5->GetTransform()->SetScale(Vec3(30.1f, 14.f, 14.f));

				AddGameObject(pFirstFloorWallRim5);
			}
			// 벽 패널
			for (int i = 0; i < 2; ++i)
			{
				DecoObject* pFirstFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-12.95f, -3.57f, -57.1f + i * 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel->GetTransform()->SetScale(Vec3(7.2f, 12.f, 12.f));

				AddGameObject(pFirstFloorWallPanel);
			}
			// 벽 패널2
			for (int i = 0; i < 2; ++i)
			{
				DecoObject* pFirstFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-16.4f, -3.5f, -43.3f + i * 11.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pFirstFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pFirstFloorWallPanel->GetTransform()->SetScale(Vec3(7.2f, 12.f, 12.f));

				AddGameObject(pFirstFloorWallPanel);
			}

			// 액자 1
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-12.6f, 8.f, -57.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				AddGameObject(pPaintingFrame);
			}

			// 액자 2
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-12.6f, 2.2f, -56.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 4.f, 4.f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				AddGameObject(pPaintingFrame);
			}

			// 액자 3
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-12.6f, 9.f, -49.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				AddGameObject(pPaintingFrame);
			}

			// 액자 4
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-16.7f, 9.f, -34.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame0.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 5
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-13.f, 8.6f, -24.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 4.f, 4.f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 6
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-12.6f, 12.f, -17.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 7
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-12.9f, 9.4f, -13.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				AddGameObject(pPaintingFrame);
			}

			// 철창
			{
				DecoObject* pSpikeDoor = Factory::CreateObject<DecoObject>(Vec3(-17.04f, -2.9f, -37.57f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\SpikeDoor.fbx");

				pSpikeDoor->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
				pSpikeDoor->GetTransform()->SetScale(Vec3(10.f, 7.9f, 5.2f));
				AddGameObject(pSpikeDoor);
			}

			// 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(2.6f, -5.3f, -42.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(15.f, 8.f, 16.2f));
				AddGameObject(pBottomRug);

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(1.6f, -3.5f, -42.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

					AddGameObject(pPotHeal);
				}

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(3.8f, -3.5f, -42.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

					AddGameObject(pPotHeal);
				}

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(2.8f, -3.5f, -44.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.f, 170.5f, 0.f));
					AddGameObject(pPotHeal);
				}
			}

			// 액자 1
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-2.7f, 0.75f, -29.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame1.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 2
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(8.5f, 0.75f, -29.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame1.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				AddGameObject(pPaintingFrame);
			}

		}
		// 1층 바닥
		{
			// 바닥틀
			{
				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(-5.73f, -5.6f, -61.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (2).fbx");

				pFirstFloorPanel->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));

				AddGameObject(pFirstFloorPanel);
			}
			// 바닥틀2
			{
				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(12.73f, -5.57f, -45.62f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3)-Merged.fbx");

				pFirstFloorPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorPanel->GetTransform()->SetScale(Vec3(32.f, 30.f, 33.32f));
				AddGameObject(pFirstFloorPanel);
			}

			// 계단틀
			{
				DecoObject* pFirstFloorRightStairsPanel = Factory::CreateObject<DecoObject>(Vec3(19.25f, -0.85f, -19.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3).fbx");

				pFirstFloorRightStairsPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
				pFirstFloorRightStairsPanel->GetTransform()->SetScale(Vec3(19.f, 19.f, 19.f));

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

				AddGameObject(pFirstFloorLeftColumn);
			}
			// 1층 기둥(오른쪽 계단)
			{
				DecoObject* pFirstFloorRightColumn = Factory::CreateObject<DecoObject>(Vec3(12.2f, 1.6f, -29.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorRightColumn->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pFirstFloorRightColumn->GetTransform()->SetScale(Vec3(23.85f, 14.3f, 23.85f));



				AddGameObject(pFirstFloorRightColumn);
			}

#pragma region "화톳불 세트 1"
			{
				//화톳불 3개 오브젝트 세트
				float x = -2.4f;
				float y = -4.4f;
				float z = -31.7f;
				{
					//바텀 - FireLamp_Bottom
					DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\FireLamp_Bottom.fbx");
					pFireLamp_Bottom->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					AddGameObject(pFireLamp_Bottom);
				}
				{
					//나무장작 - FireLamp_Wood
					DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\FireLamp_Wood.fbx");
					pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

					AddGameObject(pFireLamp_Wood);
				}
				{
					//상단부 - FireLamp_Top
					DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 2.f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\FireLamp_Top.fbx");
					pFireLamp_Top->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

					AddGameObject(pFireLamp_Top);
				}
			}

#pragma region "화톳불 세트 2"
			{
				//화톳불 3개 오브젝트 세트
				float x = 8.5f;
				float y = -4.4f;
				float z = -31.7f;
				{
					//바텀 - FireLamp_Bottom
					DecoObject* pFireLamp_Bottom = Factory::CreateObject<DecoObject>(Vec3(x, y, z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\FireLamp_Bottom.fbx");
					pFireLamp_Bottom->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					AddGameObject(pFireLamp_Bottom);
				}
				{
					//나무장작 - FireLamp_Wood
					DecoObject* pFireLamp_Wood = Factory::CreateObject<DecoObject>(Vec3(x, (y + 0.5f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\FireLamp_Wood.fbx");
					pFireLamp_Wood->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

					AddGameObject(pFireLamp_Wood);
				}
				{
					//상단부 - FireLamp_Top
					DecoObject* pFireLamp_Top = Factory::CreateObject<DecoObject>(Vec3(x, (y + 2.f), z), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\FireLamp_Top.fbx");
					pFireLamp_Top->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

					AddGameObject(pFireLamp_Top);
				}
			}
#pragma endregion
			// 문틀
			{
				DecoObject* pFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(2.9f, -1.1f, -29.74f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

				pFloorDoorFrame->GetTransform()->SetScale(Vec3(8.48f, 8.74f, 13.f));

				AddGameObject(pFloorDoorFrame);
			}
			// 문
			{
				DecoObject* pFloorDoor = Factory::CreateObject<DecoObject>(Vec3(2.9f, -1.1f, -29.74f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

				pFloorDoor->GetTransform()->SetScale(Vec3(9.f, 8.5f, 8.5f));

				AddGameObject(pFloorDoor);
			}
			// 열쇠구멍
			{
				DecoObject* pFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(2.9f, -1.1f, -29.94f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

				pFloorDoorLock->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
				AddGameObject(pFloorDoorLock);
			}

		}
#pragma endregion
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


				AddGameObject(pSecondFloorWallColumn8);
			}

			// 기둥9
			{
				DecoObject* pSecondFloorWallColumn9 = Factory::CreateObject<DecoObject>(Vec3(29.7f, 10.9f, 20.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn9->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
				pSecondFloorWallColumn9->GetTransform()->SetScale(Vec3(23.85f, 13.3f, 23.85f));

				AddGameObject(pSecondFloorWallColumn9);
			}

			// 커피 테이블
			{
				DecoObject* pCoffeeTable = Factory::CreateObject<DecoObject>(Vec3(3.4f, 5.8f, -11.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CoffeeTable.fbx");

				pCoffeeTable->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
				pCoffeeTable->GetTransform()->SetScale(Vec3(9.f, 9.f, 9.f));

				AddGameObject(pCoffeeTable);
			}

			// 식탁보
			{
				DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(3.5f, 6.8f, -11.9f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\tableCloth.fbx", true);

				pTableCloth->GetTransform()->SetScale(Vec3(9.f, 9.f, 9.2f));

				AddGameObject(pTableCloth);
			}

			// 커피 테이블 식기
			{
				DecoObject* pTablePlates = Factory::CreateObject<DecoObject>(Vec3(3.5f, 8.2f, -11.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CoffeeTablePlates.fbx");

				pTablePlates->GetTransform()->SetScale(Vec3(5.5f, 5.5f, 5.5f));
				pTablePlates->GetTransform()->SetRotation(Vec3(0.f, 225.3f, 0.f));

				AddGameObject(pTablePlates);
			}

			// 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(-0.1f, 6.8f, -16.82f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.f, 149.f, 0.f));
				AddGameObject(pChair);
			}

			// 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(2.6f, 6.8f, -5.52f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pChair);
			}

			//  우측 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(15.51f, 4.7f, 5.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(12.f, 8.f, 13.2f));
				pBottomRug->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				AddGameObject(pBottomRug);

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(15.51f, 6.3f, 5.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

					AddGameObject(pPotHeal);
				}
			}

			//  좌측 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(-9.2f, 4.7f, 5.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(12.f, 8.f, 13.2f));
				pBottomRug->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				AddGameObject(pBottomRug);

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-9.2f, 6.3f, 5.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

					AddGameObject(pPotHeal);
				}
			}

			//  정면 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(2.92f, 4.7f, 17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(12.f, 8.f, 13.2f));
				pBottomRug->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
				AddGameObject(pBottomRug);
			}

			//  좌측 2단 선반
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-19.f, 6.7f, 17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(8.f, 8.f, 8.f));
				pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

				AddGameObject(pTwoTierShelf);
			}

			// 선반 위 화분
			{
				DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(-16.5f, 11.f, 17.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionPlantPot.fbx");
				pMansionPlantPot->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
				AddGameObject(pMansionPlantPot);
			}

			// 선반 안쪽 스크롤
			{
				DecoObject* pScroll = Factory::CreateObject<DecoObject>(Vec3(-18.9f, 7.5f, 17.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rolls.fbx");
				pScroll->GetTransform()->SetScale(Vec3(4.5f, 4.5f, 4.5f));
				pScroll->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

				AddGameObject(pScroll);
			}

			// 좌측 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(-12.6f, 7.3f, 17.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(6.f, 6.f, 6.f));
				pChair->GetTransform()->SetRotation(Vec3(0.f, 288.47f, 0.f));
				AddGameObject(pChair);
			}


			// 우측 캐비넷
			{
				DecoObject* pCabinet = Factory::CreateObject<DecoObject>(Vec3(25.3f, 11.f, 17.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CabinetStructure.fbx");

				pCabinet->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));
				pCabinet->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pCabinet);
			}

			// 우측 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(19.3f, 7.3f, 17.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(6.f, 6.f, 6.f));
				pChair->GetTransform()->SetRotation(Vec3(0.f, 288.47f, 0.f));
				AddGameObject(pChair);
			}

			// 우측 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(27.1f, 7.3f, -8.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(6.f, 6.f, 6.f));
				pChair->GetTransform()->SetRotation(Vec3(0.f, 53.9f, 0.f));

				AddGameObject(pChair);
			}

			// 의자 옆 항아리1
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(27.7f, 6.3f, -4.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			// 의자 옆 항아리2
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(27.7f, 6.3f, -0.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			// 의자 옆 항아리3
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(23.4f, 6.3f, -8.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			// 의자 옆 항아리4
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(20.3f, 6.3f, -8.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				AddGameObject(pPotHeal);
			}


			// 왼쪽 문틀
			{
				DecoObject* pSecondFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(-22.6f, 8.6f, 4.765f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

				pSecondFloorDoorFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorDoorFrame->GetTransform()->SetScale(Vec3(9.3f, 8.74f, 13.f));

				AddGameObject(pSecondFloorDoorFrame);
			}
			// 왼쪽 문
			{
				DecoObject* pSecondFloorDoor = Factory::CreateObject<DecoObject>(Vec3(-22.8f, 8.4f, 4.72f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

				pSecondFloorDoor->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorDoor->GetTransform()->SetScale(Vec3(9.f, 8.5f, 8.5f));

				AddGameObject(pSecondFloorDoor);
			}
			// 왼쪽 문 열쇠구멍
			{
				DecoObject* pSecondFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(-22.5f, 8.4f, 4.72f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

				pSecondFloorDoorLock->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorDoorLock->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

				AddGameObject(pSecondFloorDoorLock);
			}


			// 커튼(수평)
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-11.9f, 15.1f, -53.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(13.5f, 13.5f, 13.5f));

				AddGameObject(pSecondFloorCurtainHorizontal);
			}
			// 커튼(수평)2
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-15.6f, 15.1f, -38.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(13.5f, 13.5f, 13.5f));
				AddGameObject(pSecondFloorCurtainHorizontal);
			}

			// 커튼(수직)
			{
				DecoObject* pSecondFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-11.9f, 8.1f, -53.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

				pSecondFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorCurtainVertical->GetTransform()->SetScale(Vec3(13.5f, 13.5f, 13.5f));

				AddGameObject(pSecondFloorCurtainVertical);
			}

			// 커튼(수직)
			{
				DecoObject* pSecondFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-15.5f, 8.1f, -38.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

				pSecondFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorCurtainVertical->GetTransform()->SetScale(Vec3(13.5f, 13.5f, 13.5f));
				AddGameObject(pSecondFloorCurtainVertical);
			}
		}

		// 2층 바닥
		{
			// 2층 중앙 난간 상부(가운데)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(3.2f, 8.17f, -29.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(16.3f, 16.3f, 16.3f));

				AddGameObject(pSecondFloorBannisterTop);
			}
			// 2층 중앙 난간 기둥(가운데)
			for (int i = 0; i < 7; i++)
			{
				DecoObject* pSecondFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-3.5f + i * 2.2f, 6.67f, -29.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

				pSecondFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				AddGameObject(pSecondFloorBannisterStick);
			}
			// 2층 중앙 난간 하부(가운데)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(3.1f, 4.67f, -29.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(16.3f, 16.3f, 16.3f));
				AddGameObject(pSecondFloorBannisterBase);
			}
			// 2층 중앙 난간 상부(왼쪽)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-6.f, 8.17f, -19.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(18.93f, 16.3f, 16.3f));
				pSecondFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

				AddGameObject(pSecondFloorBannisterTop);
			}
			// 2층 중앙 난간 기둥(왼쪽)
			for (int i = 0; i < 7; i++)
			{
				DecoObject* pSecondFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-6.f, 6.67f, -12.05f - i * 2.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

				pSecondFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				AddGameObject(pSecondFloorBannisterStick);
			}
			// 2층 중앙 난간 하부(왼쪽)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-6.f, 4.77f, -19.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(18.93f, 16.3f, 16.3f));
				pSecondFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

				AddGameObject(pSecondFloorBannisterBase);
			}

			// 2층 중앙 난간 상부(오른쪽)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(12.2f, 8.17f, -19.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(18.93f, 16.3f, 16.3f));
				pSecondFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

				AddGameObject(pSecondFloorBannisterTop);
			}
			// 2층 중앙 난간 기둥(오른쪽)
			for (int i = 0; i < 7; i++)
			{
				DecoObject* pSecondFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(12.2f, 6.67f, -12.05f - i * 2.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

				pSecondFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				AddGameObject(pSecondFloorBannisterStick);
			}
			// 2층 중앙 난간 하부(오른쪽)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(12.2f, 4.77f, -19.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(18.93f, 16.3f, 16.3f));
				pSecondFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

				AddGameObject(pSecondFloorBannisterBase);
			}

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

			// 커튼(수평)
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-21.8f, 15.1f, -1.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(13.5f, 13.5f, 13.5f));
				//SetGizmoTarget(pSecondFloorCurtainHorizontal);
				AddGameObject(pSecondFloorCurtainHorizontal);
			}

			// 커튼2(수평)
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-21.8f, 15.1f, 12.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(13.5f, 13.5f, 13.5f));

				AddGameObject(pSecondFloorCurtainHorizontal);
			}

			// 벽 패널
			{
				DecoObject* pSecondFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-17.1f, 6.15f, 20.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
				pSecondFloorWallPanel->GetTransform()->SetScale(Vec3(10.2f, 12.f, 12.f));
				AddGameObject(pSecondFloorWallPanel);
			}

			// 벽 패널
			{
				DecoObject* pSecondFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(23.9f, 6.15f, 20.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
				pSecondFloorWallPanel->GetTransform()->SetScale(Vec3(10.2f, 12.f, 12.f));
				AddGameObject(pSecondFloorWallPanel);
			}
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


		// 천장틀
		{
			DecoObject* pThirdFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-22.8f, 36.95f, 38.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

			pThirdFloorWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pThirdFloorWallRim->GetTransform()->SetScale(Vec3(36.2f, 14.f, 14.f));

			AddGameObject(pThirdFloorWallRim);
		}

		// 천장틀
		{
			DecoObject* pThirdFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(3.6f, 36.95f, 57.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

			pThirdFloorWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pThirdFloorWallRim->GetTransform()->SetScale(Vec3(50.9f, 14.f, 14.f));

			AddGameObject(pThirdFloorWallRim);
		}

		// 3층 좌측 난간 상부(가로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-17.3f, 16.87f, 20.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(9.95f, 16.3f, 16.3f));

			AddGameObject(pThirdFloorBannisterTop);
		}
		// 3층 좌측 난간 기둥(가로)
		for (int i = 0; i < 4; i++)
		{
			DecoObject* pThirdFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-20.5f + i * 2.2f, 15.87f, 20.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
			pThirdFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 2.16f, 3.f));
			AddGameObject(pThirdFloorBannisterStick);
		}
		// 3층 좌측 난간 하부(가로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-17.2f, 14.5f, 20.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(9.84f, 16.3f, 16.3f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 좌측 난간 상부(세로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-11.9f, 16.87f, 31.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(18.9f, 16.3f, 16.3f));
			pThirdFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pThirdFloorBannisterTop);
		}
		// 3층 좌측 난간 기둥(세로)
		for (int i = 0; i < 7; i++)
		{
			DecoObject* pThirdFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-11.9f, 15.87f, 23.35f + i * 2.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

			pThirdFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 2.16f, 3.f));
			AddGameObject(pThirdFloorBannisterStick);
		}
		// 3층 좌측 난간 하부(세로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-11.9f, 14.47f, 31.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(18.9f, 16.3f, 16.3f));
			pThirdFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 우측 난간 상부(가로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(23.8f, 16.87f, 20.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(9.95f, 16.3f, 16.3f));
			AddGameObject(pThirdFloorBannisterTop);
		}
		// 3층 우측 난간 기둥(가로)
		for (int i = 0; i < 4; i++)
		{
			DecoObject* pThirdFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(20.5f + i * 2.2f, 15.87f, 20.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
			pThirdFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 2.16f, 3.f));
			AddGameObject(pThirdFloorBannisterStick);
		}
		// 3층 우측 난간 하부(가로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(23.9f, 14.5f, 20.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(9.84f, 16.3f, 16.3f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 우측 난간 상부(세로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(17.9f, 16.87f, 31.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(18.9f, 16.3f, 16.3f));
			pThirdFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));

			AddGameObject(pThirdFloorBannisterTop);
		}
		// 3층 우측 난간 기둥(세로)
		for (int i = 0; i < 7; i++)
		{
			DecoObject* pThirdFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(17.9f, 15.87f, 23.35f + i * 2.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");

			pThirdFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 2.16f, 3.f));
			AddGameObject(pThirdFloorBannisterStick);
		}
		// 3층 우측 난간 하부(세로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(17.9f, 14.47f, 31.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(18.9f, 16.3f, 16.3f));
			pThirdFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 중앙 난간 상부
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(3.18f, 16.9f, 41.03f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(13.9f, 16.3f, 16.3f));

			AddGameObject(pThirdFloorBannisterTop);
		}
		// 3층 중앙 난간 기둥
		for (int i = 0; i < 5; i++)
		{
			DecoObject* pThirdFloorBannisterStick = Factory::CreateObject<DecoObject>(Vec3(-1.72f + i * 2.5f, 15.8f, 41.03f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterStick.fbx");
			pThirdFloorBannisterStick->GetTransform()->SetScale(Vec3(3.f, 2.16f, 3.f));
			AddGameObject(pThirdFloorBannisterStick);
		}
		// 3층 중앙 난간 하부
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(3.18f, 14.5f, 41.03f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(13.2f, 16.3f, 16.3f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-21.2f, 34.4f, 30.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(18.f, 18.f, 18.f));
			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-21.2f, 34.4f, 47.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(18.f, 18.f, 18.f));
			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-13.2f, 34.4f, 56.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(3.6f, 34.4f, 56.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));

			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(20.2f, 34.4f, 56.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));

			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-13.2f, 26.f, 56.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(20.f, 26.f, 56.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-21.5f, 26.f, 30.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
			pThirdFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-21.5f, 26.f, 47.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
			pThirdFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 벽 패널
		for (int i = 0; i < 5; ++i)
		{
			DecoObject* pThirdFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-22.85f, 15.8f, 24.9f + i * 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

			pThirdFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			pThirdFloorWallPanel->GetTransform()->SetScale(Vec3(7.2f, 12.f, 12.f));

			AddGameObject(pThirdFloorWallPanel);
		}

		// 벽 패널(정면 왼쪽)
		for (int i = 0; i < 3; ++i)
		{
			DecoObject* pThirdFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-18.3f + i * 7.4f, 15.8f, 58.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

			pThirdFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pThirdFloorWallPanel->GetTransform()->SetScale(Vec3(7.4f, 12.f, 12.f));

			AddGameObject(pThirdFloorWallPanel);
		}

		// 벽 패널(정면 오른쪽)
		for (int i = 0; i < 3; ++i)
		{
			DecoObject* pThirdFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(9.8f + i * 7.7f, 15.8f, 58.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

			pThirdFloorWallPanel->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pThirdFloorWallPanel->GetTransform()->SetScale(Vec3(7.7f, 12.f, 12.f));

			AddGameObject(pThirdFloorWallPanel);
		}

		// 액자 1
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-22.9f, 28.7f, 24.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 2
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-22.9f, 22.7f, 27.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 4.f, 4.f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 3
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-22.9f, 24.3f, 33.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 4
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-22.9f, 28.4f, 38.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame0.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 5
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-22.9f, 28.7f, 43.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 4.f, 4.f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 6
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-22.9f, 23.6f, 53.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 7
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-8.6f, 29.4f, 58.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 8
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-6.f, 23.4f, 58.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 4.f, 4.f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 9
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-1.9f, 27.3f, 58.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 10
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(3.3f, 26.3f, 58.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame0.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 11
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(9.5f, 26.9f, 58.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 4.f, 4.f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 12
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(14.8f, 24.f, 58.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(6.3f, 6.3f, 6.3f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pPaintingFrame);
		}

		// 좌측 항아리들
		{
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-12.2f, 15.2f, 55.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-10.f, 15.2f, 55.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-11.1f, 15.2f, 53.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				AddGameObject(pPotHeal);
			}
		}

		// 우측 항아리들
		{
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(18.2f, 15.2f, 55.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(16.f, 15.2f, 55.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(17.1f, 15.2f, 53.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
				AddGameObject(pPotHeal);
			}
		}

		// 좌측 의자
		{
			DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(-18.f, 17.f, 28.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

			pChair->GetTransform()->SetScale(Vec3(6.f, 6.f, 6.f));
			pChair->GetTransform()->SetRotation(Vec3(0.f, 288.47f, 0.f));
			AddGameObject(pChair);
		}

		// 2단 선반
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-20.9f, 16.5f, 27.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pTwoTierShelf);

			// 선반 안 항아리들
			for (int i = 0; i < 3; ++i)
			{
				DecoObject* pMansionSpicePot = Factory::CreateObject<DecoObject>(Vec3(-20.9f, 19.6f, 25.9f + i * 2.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\MansionSpicePot.fbx");
				pMansionSpicePot->GetTransform()->SetScale(i == 0 ? Vec3(2.3f, 2.3f, 2.3f) : Vec3(1.5f, 1.5f, 1.5f));
				AddGameObject(pMansionSpicePot);
			}
		}

		// 2단 선반
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-20.9f, 16.5f, 34.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));

			AddGameObject(pTwoTierShelf);
		}

		// 캐비넷
		{
			DecoObject* pCabinet = Factory::CreateObject<DecoObject>(Vec3(-19.8f, 20.2f, 41.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CabinetStructure.fbx");

			pCabinet->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));
			pCabinet->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

			AddGameObject(pCabinet);
		}

		// 2단 책상
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-20.9f, 16.5f, 49.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			AddGameObject(pTwoTierShelf);
		}

		// 2단 선반
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-18.8f, 16.5f, 54.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddGameObject(pTwoTierShelf);
		}

		// 2단 선반 (우측)
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(24.9f, 16.5f, 54.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pTwoTierShelf);
		}

		// 선반 위 화분
		{
			DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(26.8f, 20.4f, 54.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionPlantPot.fbx");
			pMansionPlantPot->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pMansionPlantPot);
		}

		// 문틀
		{
			DecoObject* pFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(3.f, 18.1f, 57.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

			pFloorDoorFrame->GetTransform()->SetScale(Vec3(8.48f, 8.74f, 13.f));
			AddGameObject(pFloorDoorFrame);
		}
		// 문
		{
			DecoObject* pFloorDoor = Factory::CreateObject<DecoObject>(Vec3(3.f, 18.1f, 57.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

			pFloorDoor->GetTransform()->SetScale(Vec3(9.f, 8.5f, 8.5f));

			AddGameObject(pFloorDoor);
		}
		// 열쇠구멍
		{
			DecoObject* pFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(3.f, 18.1f, 57.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

			pFloorDoorLock->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
			AddGameObject(pFloorDoorLock);
		}

#pragma endregion

		// 1F 샹들리에
		{
			DecoObject* pChandelier = Factory::CreateObject<DecoObject>(Vec3(2.3f, 42.4f, 36.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ChandelierWithChain.fbx");
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

			AddGameObject(pChandelier);
		}

		// 3F 샹들리에
		{
			DecoObject* pChandelier = Factory::CreateObject<DecoObject>(Vec3(2.3f, 36.4f, -45.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ChandelierWithChain.fbx");
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

		// 샹들리에 라이트
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(2.3f, 43.6f, -2.f));
			pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.5f, 0.5f, 0.2f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(50.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}


		// PotHead
		{
			PhysicsInfo info = {};

			Npc* pPotHead = Factory::CreateObjectHasPhysical<Npc>(Vec3(2.9f, 14.5f, 43.2f), info, L"Deferred", L"..\\Resources\\FBX\\Npc\\Npc_PotHead.fbx");
			pPotHead->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
			pPotHead->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));

			// 애니메이션의 이름은 FBX에 저장되어 있는 것을 그대로 가져오므로 해당 FBX를 사용하는 클래스의 생성자와 같은 특정 부분에서
			// 사용하기 편한 이름으로 일괄적으로 바꿔줄 필요가 있음
			pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

			// 반복 여부를 설정하는 함수 (Finished 플래그를 사용할 수 없음)
			pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

			// 인덱스 번호로도 사용 가능
			pPotHead->GetAnimator()->SetLoop(9, true);

			// HasExit는 현재 애니메이션 실행중에 다른 애니메이션이 실행되었을 때 바로 넘길건지 여부를 결정 (기본적으로 true)
			// 이 값이 false면 애니메이션 플레이 도중 다른 애니메이션 Play가 실행되었을 때 기존 애니메이션이 다 끝나고 실행됨
			pPotHead->GetAnimator()->SetHasExitFlag(9, false);

			// 애니메이션 실행하는 방법은 2D와 비슷하게 애니메이션 이름, 반복할건지 여부를 넣어주면 됨
			pPotHead->GetAnimator()->Play(L"PotHead_Idle", true);

			AddGameObject(pPotHead);

		}
	}

	void HallColliderCheckMap::InitColliderAdd()
	{

	}

	void HallColliderCheckMap::FuncObjectAdd()
	{
		{
			GameObject* pLightObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pLightObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(3.4f, 7.7f, -3.5f));
			pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Light* pLight = pLightObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.5f, 0.5f, 0.2f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(22.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pLightObject);
			SetGizmoTarget(pLightObject);
		}
	}

	void HallColliderCheckMap::Exit()
	{
	}
}