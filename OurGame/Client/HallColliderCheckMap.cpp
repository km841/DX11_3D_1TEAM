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
#include "TeleportZone.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Bat.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
#include "BreakablePot.h"
/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"
#include "Mirror.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "PaperBurnScript.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "PlayerMoveOverMapScript.h"

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
		LightDirSet();
		mpMainCamera->GetTransform()->SetPosition(Vec3(11.7f, 22.3f, -60.6f));
		mpMainCamera->GetTransform()->SetRotation(Vec3(53.9f, -48.3f, 0.f));

		OwnerFollowScript* pFollowScript = spPlayerHolder->GetScript<OwnerFollowScript>();
		pFollowScript->SetOffset(Vec3(9.f, 25.f, -14.f));

		PLAYER->GetKeyInfo().SetLeftKey(KeyType::LEFT);
		PLAYER->GetKeyInfo().SetForwardKey(KeyType::UP);

		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{
			case 3:
				PLAYER->GetTransform()->SetPosition(Vec3(2.16f, 0.f, -46.33f));
				break;
			case 4:
				PLAYER->GetTransform()->SetPosition(Vec3(3.1f, -4.3f, -59.3f));
				break;
			}
		}
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
		

		DisableDirLight();
		InitObjectAdd();
		InitColliderAdd();
		FuncObjectAdd();
		//배경맵 하얀색으로 만들어주는 코드
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

				//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(-5.18f, -3.45f, -34.35f), Vec3(-90.f, 0.00f, -90.f));
			AddGameObject(pBat);
		}

		//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(-5.18f, -3.45f, -40.12f), Vec3(-90.f, 0.00f, -90.f));
			AddGameObject(pBat);
		}

		//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(-5.18f, -3.45f, -26.25f), Vec3(-90.f, 0.00f, -90.f));
			AddGameObject(pBat);
		}

		//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(9.15f, -3.38f, -29.40f), Vec3(-90.f, 0.00f, 90.f));
			AddGameObject(pBat);

		}

		//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(9.15f, -3.38f, -37.65f), Vec3(-90.f, 0.00f, 90.f));
			AddGameObject(pBat);
		}

		//초록거미
		{
			Lurker* pLurker = Factory::CreateLurker(Vec3(5.78f, 4.12f, 4.12f), Vec3(-90.f, 0.00f, 90.f));
			AddGameObject(pLurker);

		}

		//초록거미
		{
			Lurker* pLurker = Factory::CreateLurker(Vec3(5.78f, 4.12f, 0.38f), Vec3(-90.f, 0.00f, 90.f));
			AddGameObject(pLurker);

		}

		//초록거미
		{
			Lurker* pLurker = Factory::CreateLurker(Vec3(0.00f, 4.12f, 4.12f), Vec3(-90.f, 0.00f, -90.f));
			AddGameObject(pLurker);

		}

		//초록거미
		{
			Lurker* pLurker = Factory::CreateLurker(Vec3(0.00f, 4.12f, 0.38f), Vec3(-90.f, 0.00f, -90.f));
			AddGameObject(pLurker);
		}





	}

	void HallColliderCheckMap::LightDirSet()
	{
		SetDirLightPosition(Vec3(20.7f, 53.4f, 69.3f));
		SetDirLightRotation(Vec3(38.3f, 199.57f, 167.5f));
	}

	void HallColliderCheckMap::InitObjectAdd()
	{
		// 1층 벽
		{
			// 1, 2층 벽
			{
				DecoObject* pTotalFrame = Factory::CreateObject<DecoObject>(Vec3(2.10f, 11.48f, 0.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MapFrame.fbx");

				pTotalFrame->GetTransform()->SetScale(Vec3(97.50f, 97.50f, 97.50f));
				pTotalFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

				pTotalFrame->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);

				pTotalFrame->DrawShadow(false);
				AddGameObject(pTotalFrame);

			}

			// 1층 미러
			{
				GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(2.10f, 2.78f, -0.45f), L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\HallColliderMirr.fbx", false, LayerType::Mirror);

				pMirror->SetFrustumCheckFlag(false);
				pMirror->GetTransform()->SetScale(Vec3(97.50f, 97.50f, 97.50f));
				pMirror->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				pMirror->AddComponent(new Mirror);

				AddGameObject(pMirror);
			}

			// 숨은통로
			{
				DecoObject* pSecretPassage = Factory::CreateObject<DecoObject>(Vec3(-9.75f, 4.46f, -28.39f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main-detach (1).fbx");

				pSecretPassage->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				pSecretPassage->GetTransform()->SetScale(Vec3(17.06f, 17.06f, 17.06f));

				AddGameObject(pSecretPassage);
			}

			// 기둥
			{
				DecoObject* pFirstFloorWallColumn = Factory::CreateObject<DecoObject>(Vec3(-9.75f, 4.57f, -45.90f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorWallColumn->GetTransform()->SetScale(Vec3(17.89f, 17.89f, 17.89f));

				AddGameObject(pFirstFloorWallColumn);
			}
			// 기둥2
			{
				DecoObject* pFirstFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(-9.75f, 4.57f, -34.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorWallColumn2->GetTransform()->SetScale(Vec3(17.89f, 17.89f, 17.89f));
				AddGameObject(pFirstFloorWallColumn2);
			}

			// 기둥3
			{
				DecoObject* pFirstFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(-12.60f, 4.57f, -34.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorWallColumn3->GetTransform()->SetScale(Vec3(17.89f, 17.89f, 17.89f));
				AddGameObject(pFirstFloorWallColumn3);
			}

			// 기둥4
			{
				DecoObject* pFirstFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(-9.75f, 4.57f, -22.80f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorWallColumn4->GetTransform()->SetScale(Vec3(17.89f, 17.89f, 17.89f));
				AddGameObject(pFirstFloorWallColumn4);
			}

			// 기둥5
			{
				DecoObject* pFirstFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-12.60f, 4.57f, -22.80f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorWallColumn5->GetTransform()->SetScale(Vec3(17.89f, 17.89f, 17.89f));

				AddGameObject(pFirstFloorWallColumn5);
			}

			// 천장틀
			{
				DecoObject* pFirstFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-9.68f, 12.75f, -40.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
				pFirstFloorWallRim->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pFirstFloorWallRim->GetTransform()->SetScale(Vec3(10.50f, 10.50f, 10.50f));

				AddGameObject(pFirstFloorWallRim);
			}
			// 천장틀2
			{
				DecoObject* pFirstFloorWallRim2 = Factory::CreateObject<DecoObject>(Vec3(-12.75f, 12.75f, -28.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");
				//SetGizmoTarget(pFirstFloorWallRim2);
				pFirstFloorWallRim2->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pFirstFloorWallRim2->GetTransform()->SetScale(Vec3(10.50f, 10.50f, 10.50f));

				AddGameObject(pFirstFloorWallRim2);
			}
			// 천장틀3
			{
				DecoObject* pFirstFloorWallRim3 = Factory::CreateObject<DecoObject>(Vec3(-10.05f, 12.75f, -15.08f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim3->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pFirstFloorWallRim3->GetTransform()->SetScale(Vec3(14.51f, 10.50f, 10.50f));

				AddGameObject(pFirstFloorWallRim3);
			}
			// 천장틀4
			{
				DecoObject* pFirstFloorWallRim4 = Factory::CreateObject<DecoObject>(Vec3(-13.73f, 11.70f, -7.20f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim4->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				pFirstFloorWallRim4->GetTransform()->SetScale(Vec3(6.09f, 10.50f, 10.50f));

				AddGameObject(pFirstFloorWallRim4);
			}
			// 천장틀5
			{
				DecoObject* pFirstFloorWallRim5 = Factory::CreateObject<DecoObject>(Vec3(-17.10f, 12.83f, 4.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

				pFirstFloorWallRim5->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pFirstFloorWallRim5->GetTransform()->SetScale(Vec3(22.58f, 10.50f, 10.50f));

				AddGameObject(pFirstFloorWallRim5);
			}


			// 액자 1
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-9.45f, 6.00f, -43.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				AddGameObject(pPaintingFrame);
			}

			// 액자 2
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-9.45f, 1.65f, -42.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 3.00f, 3.00f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				AddGameObject(pPaintingFrame);
			}

			// 액자 3
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-9.45f, 6.75f, -36.97f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				AddGameObject(pPaintingFrame);
			}

			// 액자 4
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-12.52f, 6.75f, -25.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame0.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 5
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-9.75f, 6.45f, -18.23f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 3.00f, 3.00f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 6
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-9.45f, 9.00f, -12.90f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 7
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-9.68f, 7.05f, -9.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

				AddGameObject(pPaintingFrame);
			}

			// 철창
			{
				DecoObject* pSpikeDoor = Factory::CreateObject<DecoObject>(Vec3(-12.78f, -2.17f, -28.18f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\SpikeDoor.fbx");

				pSpikeDoor->GetTransform()->SetRotation(Vec3(-90.f, 0.00f, 0.00f));
				pSpikeDoor->GetTransform()->SetScale(Vec3(7.50f, 5.93f, 3.90f));
				AddGameObject(pSpikeDoor);
			}

			// 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(1.95f, -3.97f, -32.03f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(11.25f, 6.00f, 12.15f));
				AddGameObject(pBottomRug);

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(1.20f, -2.62f, -31.72f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(2.f, 3.1f, 2.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

					AddGameObject(pPotHeal);

					PhysicsInfo basePhysicsInfo;
					basePhysicsInfo.eActorType = ActorType::Kinematic;
					basePhysicsInfo.eGeometryType = GeometryType::Box;
					basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

					jh::BreakablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::BreakablePot>(Vec3(1.20f, -2.62f, -31.72f), basePhysicsInfo, L"Deferred", L"", false, pPotHeal);

					AddGameObject(pIrreparablePot);
				}

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(2.85f, -2.62f, -31.72f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(2.f, 3.1f, 2.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

					AddGameObject(pPotHeal);

					PhysicsInfo basePhysicsInfo;
					basePhysicsInfo.eActorType = ActorType::Kinematic;
					basePhysicsInfo.eGeometryType = GeometryType::Box;
					basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

					jh::BreakablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::BreakablePot>(Vec3(2.85f, -2.62f, -31.72f), basePhysicsInfo, L"Deferred", L"", false, pPotHeal);

					AddGameObject(pIrreparablePot);
				}

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(2.10f, -2.62f, -33.08f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(2.f, 3.1f, 2.f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, 127.88f, 0.00f));
					AddGameObject(pPotHeal);

					PhysicsInfo basePhysicsInfo;
					basePhysicsInfo.eActorType = ActorType::Kinematic;
					basePhysicsInfo.eGeometryType = GeometryType::Box;
					basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

					jh::BreakablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::BreakablePot>(Vec3(2.10f, -2.62f, -33.08f), basePhysicsInfo, L"Deferred", L"", false, pPotHeal);

					AddGameObject(pIrreparablePot);
				}
			}

			// 액자 1
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-2.03f, 0.56f, -22.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame1.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(3.75f, 3.75f, 3.75f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

				AddGameObject(pPaintingFrame);
			}

			// 액자 2
			{
				DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(6.38f, 0.56f, -22.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame1.fbx");
				pPaintingFrame->GetTransform()->SetScale(Vec3(3.75f, 3.75f, 3.75f));
				pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				AddGameObject(pPaintingFrame);
			}

		}
		// 1층 바닥
		{
			// 바닥틀
			{
				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(-4.30f, -4.20f, -46.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallPanel (2).fbx");

				pFirstFloorPanel->GetTransform()->SetScale(Vec3(9.00f, 9.00f, 9.00f));

				AddGameObject(pFirstFloorPanel);
			}
			// 바닥틀2
			{
				DecoObject* pFirstFloorPanel = Factory::CreateObject<DecoObject>(Vec3(9.55f, -4.18f, -34.21f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3)-Merged.fbx");

				pFirstFloorPanel->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				pFirstFloorPanel->GetTransform()->SetScale(Vec3(24.00f, 22.50f, 24.99f));
				AddGameObject(pFirstFloorPanel);
			}

			// 계단틀
			{
				DecoObject* pFirstFloorRightStairsPanel = Factory::CreateObject<DecoObject>(Vec3(14.44f, -0.64f, -14.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel (3).fbx");

				pFirstFloorRightStairsPanel->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
				pFirstFloorRightStairsPanel->GetTransform()->SetScale(Vec3(14.25f, 14.25f, 14.25f));

				AddGameObject(pFirstFloorRightStairsPanel);
			}
			// 1층 계단(왼쪽)
			{

				Ground* pFirstFloorLeftStairs = Factory::CreateObject<Ground>(Vec3(-7.46f, -0.45f, -14.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

				pFirstFloorLeftStairs->GetTransform()->SetScale(Vec3(17.25f, 16.35f, 17.25f));

				AddGameObject(pFirstFloorLeftStairs);
			}

			// 1층 계단(오른쪽)
			{

				Ground* pFirstFloorRightStairs = Factory::CreateObject<Ground>(Vec3(12.08f, -0.45f, -14.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

				pFirstFloorRightStairs->GetTransform()->SetScale(Vec3(17.25f, 16.35f, 17.25f));


				AddGameObject(pFirstFloorRightStairs);
			}

			// 1층 기둥(왼쪽 계단)
			{
				DecoObject* pFirstFloorLeftColumn = Factory::CreateObject<DecoObject>(Vec3(-4.50f, 1.20f, -21.83f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorLeftColumn->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorLeftColumn->GetTransform()->SetScale(Vec3(17.89f, 10.73f, 17.89f));

				AddGameObject(pFirstFloorLeftColumn);
			}
			// 1층 기둥(오른쪽 계단)
			{
				DecoObject* pFirstFloorRightColumn = Factory::CreateObject<DecoObject>(Vec3(9.15f, 1.20f, -21.83f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pFirstFloorRightColumn->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pFirstFloorRightColumn->GetTransform()->SetScale(Vec3(17.89f, 10.73f, 17.89f));



				AddGameObject(pFirstFloorRightColumn);
			}

			// 문틀
			{
				DecoObject* pFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(2.17f, -0.83f, -22.30f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

				pFloorDoorFrame->GetTransform()->SetScale(Vec3(6.36f, 6.55f, 9.75f));

				AddGameObject(pFloorDoorFrame);
			}
			// 문
			{
				DecoObject* pFloorDoor = Factory::CreateObject<DecoObject>(Vec3(2.17f, -0.83f, -22.30f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

				pFloorDoor->GetTransform()->SetScale(Vec3(6.75f, 6.38f, 6.38f));

				AddGameObject(pFloorDoor);
			}
			// 열쇠구멍
			{
				DecoObject* pFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(2.17f, -0.83f, -22.46f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

				pFloorDoorLock->GetTransform()->SetScale(Vec3(1.50f, 1.50f, 1.50f));
				AddGameObject(pFloorDoorLock);
			}

		}
#pragma endregion
		//#pragma region 2층
		{
			// 기둥1
			{
				DecoObject* pSecondFloorWallColumn1 = Factory::CreateObject<DecoObject>(Vec3(-4.50f, 4.88f, -6.82f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn1->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn1->GetTransform()->SetScale(Vec3(17.89f, 3.38f, 17.89f));


				AddGameObject(pSecondFloorWallColumn1);
			}
			// 기둥2
			{
				DecoObject* pSecondFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(9.15f, 4.88f, -6.82f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn2->GetTransform()->SetScale(Vec3(17.89f, 3.38f, 17.89f));

				AddGameObject(pSecondFloorWallColumn2);
			}
			// 기둥3(~3층까지)
			{
				DecoObject* pSecondFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(-17.10f, 15.83f, 15.38f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn3->GetTransform()->SetScale(Vec3(17.89f, 25.28f, 17.89f));

				AddGameObject(pSecondFloorWallColumn3);
			}
			// 기둥4
			{
				DecoObject* pSecondFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(-10.27f, 2.40f, -15.15f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn4->GetTransform()->SetScale(Vec3(17.89f, 22.12f, 17.89f));

				AddGameObject(pSecondFloorWallColumn4);
			}
			// 기둥5
			{
				DecoObject* pSecondFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-10.20f, 2.48f, -7.38f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn5->GetTransform()->SetScale(Vec3(17.89f, 22.12f, 17.89f));

				AddGameObject(pSecondFloorWallColumn5);
			}
			// 기둥6
			{
				DecoObject* pSecondFloorWallColumn6 = Factory::CreateObject<DecoObject>(Vec3(-17.10f, 8.32f, -6.98f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn6->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn6->GetTransform()->SetScale(Vec3(17.89f, 10.61f, 17.89f));

				AddGameObject(pSecondFloorWallColumn6);
			}

			// 기둥7
			{
				DecoObject* pSecondFloorWallColumn7 = Factory::CreateObject<DecoObject>(Vec3(-8.70f, 8.18f, 15.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn7->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn7->GetTransform()->SetScale(Vec3(17.89f, 9.98f, 17.89f));

				AddGameObject(pSecondFloorWallColumn7);
			}

			// 기둥8
			{
				DecoObject* pSecondFloorWallColumn8 = Factory::CreateObject<DecoObject>(Vec3(13.58f, 8.18f, 15.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn8->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn8->GetTransform()->SetScale(Vec3(17.89f, 9.98f, 17.89f));


				AddGameObject(pSecondFloorWallColumn8);
			}

			// 기둥9
			{
				DecoObject* pSecondFloorWallColumn9 = Factory::CreateObject<DecoObject>(Vec3(22.27f, 8.18f, 15.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn9->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn9->GetTransform()->SetScale(Vec3(17.89f, 9.98f, 17.89f));

				AddGameObject(pSecondFloorWallColumn9);
			}

			// 커피 테이블
			{
				DecoObject* pCoffeeTable = Factory::CreateObject<DecoObject>(Vec3(2.55f, 4.35f, -8.93f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CoffeeTable.fbx");

				pCoffeeTable->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				pCoffeeTable->GetTransform()->SetScale(Vec3(6.75f, 6.75f, 6.75f));

				AddGameObject(pCoffeeTable);
			}

			// 식탁보
			{
				DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(2.62f, 5.10f, -8.93f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\tableCloth.fbx", true);

				pTableCloth->GetTransform()->SetScale(Vec3(6.75f, 6.75f, 6.90f));

				AddGameObject(pTableCloth);
			}

			// 커피 테이블 식기
			{
				DecoObject* pTablePlates = Factory::CreateObject<DecoObject>(Vec3(2.62f, 6.15f, -8.93f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CoffeeTablePlates.fbx");

				pTablePlates->GetTransform()->SetScale(Vec3(4.12f, 4.12f, 4.12f));
				pTablePlates->GetTransform()->SetRotation(Vec3(0.00f, 168.98f, 0.00f));

				AddGameObject(pTablePlates);
			}

			// 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(-0.08f, 5.10f, -12.62f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(3.75f, 3.75f, 3.75f));
				pChair->GetTransform()->SetRotation(Vec3(0.00f, 111.75f, 0.00f));
				AddGameObject(pChair);
			}

			// 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(1.95f, 5.10f, -4.14f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(3.75f, 3.75f, 3.75f));
				pChair->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pChair);
			}

			//  우측 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(11.63f, 3.53f, 3.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(9.00f, 6.00f, 9.90f));
				pBottomRug->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				AddGameObject(pBottomRug);

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(11.63f, 4.72f, 3.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

					AddGameObject(pPotHeal);
				}
			}

			//  좌측 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(-6.90f, 3.53f, 3.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(9.00f, 6.00f, 9.90f));
				pBottomRug->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				AddGameObject(pBottomRug);

				// 그 위에 항아리
				{
					DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-6.90f, 4.72f, 3.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
					pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
					pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

					AddGameObject(pPotHeal);
				}
			}

			//  정면 바닥 러그
			{
				DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(2.19f, 3.53f, 13.20f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rug_Mark.fbx");
				pBottomRug->GetTransform()->SetScale(Vec3(9.00f, 6.00f, 9.90f));
				pBottomRug->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				AddGameObject(pBottomRug);
			}

			//  좌측 2단 선반
			{
				DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-14.25f, 5.03f, 13.20f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
				pTwoTierShelf->GetTransform()->SetScale(Vec3(6.00f, 6.00f, 6.00f));
				pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));

				AddGameObject(pTwoTierShelf);
			}

			// 선반 위 화분
			{
				DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(-12.38f, 8.25f, 13.20f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionPlantPot.fbx");
				pMansionPlantPot->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				AddGameObject(pMansionPlantPot);
			}

			// 선반 안쪽 스크롤
			{
				DecoObject* pScroll = Factory::CreateObject<DecoObject>(Vec3(-14.17f, 5.62f, 12.90f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Rolls.fbx");
				pScroll->GetTransform()->SetScale(Vec3(3.38f, 3.38f, 3.38f));
				pScroll->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

				AddGameObject(pScroll);
			}

			// 좌측 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(-9.45f, 5.47f, 12.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(4.50f, 4.50f, 4.50f));
				pChair->GetTransform()->SetRotation(Vec3(0.00f, 216.35f, 0.00f));
				AddGameObject(pChair);
			}


			// 우측 캐비넷
			{
				DecoObject* pCabinet = Factory::CreateObject<DecoObject>(Vec3(18.98f, 8.25f, 13.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CabinetStructure.fbx");

				pCabinet->GetTransform()->SetScale(Vec3(9.00f, 9.00f, 9.00f));
				pCabinet->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pCabinet);
			}

			// 우측 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(14.48f, 5.47f, 12.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(4.50f, 4.50f, 4.50f));
				pChair->GetTransform()->SetRotation(Vec3(0.00f, 216.35f, 0.00f));
				AddGameObject(pChair);
			}

			// 우측 의자
			{
				DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(20.33f, 5.47f, -6.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(4.50f, 4.50f, 4.50f));
				pChair->GetTransform()->SetRotation(Vec3(0.00f, 40.42f, 0.00f));

				AddGameObject(pChair);
			}

			// 의자 옆 항아리1
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(20.77f, 4.72f, -3.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			// 의자 옆 항아리2
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(20.77f, 4.72f, -0.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			// 의자 옆 항아리3
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(17.55f, 4.72f, -6.30f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			// 의자 옆 항아리4
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(15.23f, 4.72f, -6.30f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				AddGameObject(pPotHeal);
			}


			// 왼쪽 문틀
			{
				DecoObject* pSecondFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(-16.95f, 6.45f, 3.57f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

				pSecondFloorDoorFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorDoorFrame->GetTransform()->SetScale(Vec3(6.98f, 6.55f, 9.75f));

				AddGameObject(pSecondFloorDoorFrame);
			}
			// 왼쪽 문
			{
				DecoObject* pSecondFloorDoor = Factory::CreateObject<DecoObject>(Vec3(-17.10f, 6.30f, 3.54f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

				pSecondFloorDoor->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorDoor->GetTransform()->SetScale(Vec3(6.75f, 6.38f, 6.38f));

				AddGameObject(pSecondFloorDoor);
			}
			// 왼쪽 문 열쇠구멍
			{
				DecoObject* pSecondFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(-16.88f, 6.30f, 3.54f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

				pSecondFloorDoorLock->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorDoorLock->GetTransform()->SetScale(Vec3(1.50f, 1.50f, 1.50f));

				AddGameObject(pSecondFloorDoorLock);
			}


			// 커튼(수평)
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-8.93f, 11.32f, -40.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(10.12f, 10.12f, 10.12f));

				AddGameObject(pSecondFloorCurtainHorizontal);
			}
			// 커튼(수평)2
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-11.70f, 11.32f, -28.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(10.12f, 10.12f, 10.12f));
				AddGameObject(pSecondFloorCurtainHorizontal);
			}

			// 커튼(수직)
			{
				DecoObject* pSecondFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-8.93f, 6.07f, -40.12f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

				pSecondFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorCurtainVertical->GetTransform()->SetScale(Vec3(10.12f, 10.12f, 10.12f));

				AddGameObject(pSecondFloorCurtainVertical);
			}

			// 커튼(수직)
			{
				DecoObject* pSecondFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-11.62f, 6.07f, -28.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

				pSecondFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorCurtainVertical->GetTransform()->SetScale(Vec3(10.12f, 10.12f, 10.12f));
				AddGameObject(pSecondFloorCurtainVertical);
			}
		}

		// 2층 바닥
		{
			// 2층 중앙 난간 상부(가운데)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(2.40f, 6.13f, -21.79f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(12.23f, 12.23f, 12.23f));

				AddGameObject(pSecondFloorBannisterTop);
			}

			// 2층 중앙 난간 하부(가운데)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(2.33f, 3.50f, -21.79f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(12.23f, 12.23f, 12.23f));
				AddGameObject(pSecondFloorBannisterBase);
			}
			// 2층 중앙 난간 상부(왼쪽)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-4.50f, 6.13f, -14.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(14.20f, 12.23f, 12.23f));
				pSecondFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

				AddGameObject(pSecondFloorBannisterTop);
			}

			// 2층 중앙 난간 하부(왼쪽)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-4.50f, 3.58f, -14.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(14.20f, 12.23f, 12.23f));
				pSecondFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

				AddGameObject(pSecondFloorBannisterBase);
			}

			// 2층 중앙 난간 상부(오른쪽)
			{
				DecoObject* pSecondFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(9.15f, 6.13f, -14.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

				pSecondFloorBannisterTop->GetTransform()->SetScale(Vec3(14.20f, 12.23f, 12.23f));
				pSecondFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

				AddGameObject(pSecondFloorBannisterTop);
			}

			// 2층 중앙 난간 하부(오른쪽)
			{
				DecoObject* pSecondFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(9.15f, 3.58f, -14.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

				pSecondFloorBannisterBase->GetTransform()->SetScale(Vec3(14.20f, 12.23f, 12.23f));
				pSecondFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

				AddGameObject(pSecondFloorBannisterBase);
			}

			// 1층 계단(왼쪽)
			{

				Ground* pSecondFloorLeftStairs = Factory::CreateObject<Ground>(Vec3(-6.15f, 6.90f, 23.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

				pSecondFloorLeftStairs->GetTransform()->SetScale(Vec3(17.25f, 16.35f, 17.25f));

				AddGameObject(pSecondFloorLeftStairs);
			}

			// 1층 계단(오른쪽)
			{

				Ground* pSecondFloorRightStairs = Factory::CreateObject<Ground>(Vec3(10.95f, 6.90f, 23.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\stairs (1).fbx");

				pSecondFloorRightStairs->GetTransform()->SetScale(Vec3(17.25f, 16.35f, 17.25f));

				AddGameObject(pSecondFloorRightStairs);
			}
			// 2층 계단 난간 상하부(왼쪽)
			{
				DecoObject* pSecondFloorLeftStairRail = Factory::CreateObject<DecoObject>(Vec3(-3.38f, 7.68f, 23.33f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\StairRail.fbx");

				pSecondFloorLeftStairRail->GetTransform()->SetRotation(Vec3(0.00f, -180.00f, 0.00f));
				pSecondFloorLeftStairRail->GetTransform()->SetScale(Vec3(13.50f, 13.50f, 13.50f));

				AddGameObject(pSecondFloorLeftStairRail);
			}

			// 2층 계단 난간 상하부(오른쪽)
			{
				DecoObject* pSecondFloorRightStairRail = Factory::CreateObject<DecoObject>(Vec3(8.08f, 7.68f, 23.33f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\StairRail.fbx");

				pSecondFloorRightStairRail->GetTransform()->SetRotation(Vec3(0.00f, -180.00f, 0.00f));
				pSecondFloorRightStairRail->GetTransform()->SetScale(Vec3(13.50f, 13.50f, 13.50f));


				AddGameObject(pSecondFloorRightStairRail);
			}

			// 좌측 계단 옆 기둥
			{
				DecoObject* pSecondFloorWallColumn1 = Factory::CreateObject<DecoObject>(Vec3(-3.38f, 4.88f, 16.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn1->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn1->GetTransform()->SetScale(Vec3(15.90f, 3.38f, 15.90f));

				AddGameObject(pSecondFloorWallColumn1);
			}
			// 우측 계단 옆 기둥
			{
				DecoObject* pSecondFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(8.18f, 4.88f, 16.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

				pSecondFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
				pSecondFloorWallColumn2->GetTransform()->SetScale(Vec3(15.90f, 3.38f, 15.90f));
				AddGameObject(pSecondFloorWallColumn2);
			}

			// 커튼(수평)
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-16.35f, 11.32f, -1.20f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(10.12f, 10.12f, 10.12f));
				//SetGizmoTarget(pSecondFloorCurtainHorizontal);
				AddGameObject(pSecondFloorCurtainHorizontal);
			}

			// 커튼2(수평)
			{
				DecoObject* pSecondFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-16.35f, 11.32f, 9.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

				pSecondFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				pSecondFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(10.12f, 10.12f, 10.12f));

				AddGameObject(pSecondFloorCurtainHorizontal);
			}

			// 벽 패널
			{
				DecoObject* pSecondFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(-12.83f, 4.61f, 15.38f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				pSecondFloorWallPanel->GetTransform()->SetScale(Vec3(7.65f, 9.00f, 9.00f));
				AddGameObject(pSecondFloorWallPanel);
			}

			// 벽 패널
			{
				DecoObject* pSecondFloorWallPanel = Factory::CreateObject<DecoObject>(Vec3(17.92f, 4.61f, 15.38f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\wallPanel.fbx");

				pSecondFloorWallPanel->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				pSecondFloorWallPanel->GetTransform()->SetScale(Vec3(7.65f, 9.00f, 9.00f));
				AddGameObject(pSecondFloorWallPanel);
			}
		}

		//#pragma region 3층

		// 기둥1
		{
			DecoObject* pThirdFloorWallColumn1 = Factory::CreateObject<DecoObject>(Vec3(-8.62f, 11.62f, 30.80f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn1->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
			pThirdFloorWallColumn1->GetTransform()->SetScale(Vec3(17.89f, 3.04f, 17.89f));

			AddGameObject(pThirdFloorWallColumn1);
		}
		// 기둥2
		{
			DecoObject* pThirdFloorWallColumn2 = Factory::CreateObject<DecoObject>(Vec3(-3.50f, 11.62f, 30.79f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn2->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
			pThirdFloorWallColumn2->GetTransform()->SetScale(Vec3(17.89f, 3.04f, 17.89f));

			AddGameObject(pThirdFloorWallColumn2);
		}
		// 기둥3
		{
			DecoObject* pThirdFloorWallColumn3 = Factory::CreateObject<DecoObject>(Vec3(8.25f, 11.62f, 30.80f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn3->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
			pThirdFloorWallColumn3->GetTransform()->SetScale(Vec3(17.89f, 3.04f, 17.89f));

			AddGameObject(pThirdFloorWallColumn3);
		}
		// 기둥4
		{
			DecoObject* pThirdFloorWallColumn4 = Factory::CreateObject<DecoObject>(Vec3(13.58f, 11.62f, 30.80f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn4->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
			pThirdFloorWallColumn4->GetTransform()->SetScale(Vec3(17.89f, 3.04f, 17.89f));

			AddGameObject(pThirdFloorWallColumn4);
		}

		// 기둥5
		{
			DecoObject* pThirdFloorWallColumn5 = Factory::CreateObject<DecoObject>(Vec3(-17.11f, 19.12f, 43.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn5->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
			pThirdFloorWallColumn5->GetTransform()->SetScale(Vec3(17.89f, 18.67f, 17.89f));

			AddGameObject(pThirdFloorWallColumn5);
		}

		// 기둥6
		{
			DecoObject* pThirdFloorWallColumn6 = Factory::CreateObject<DecoObject>(Vec3(22.20f, 19.12f, 43.07f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\column2Base (3).fbx");

			pThirdFloorWallColumn6->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));
			pThirdFloorWallColumn6->GetTransform()->SetScale(Vec3(17.89f, 18.67f, 17.89f));

			AddGameObject(pThirdFloorWallColumn6);
		}


		// 천장틀
		{
			DecoObject* pThirdFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(-17.10f, 27.71f, 29.17f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

			pThirdFloorWallRim->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
			pThirdFloorWallRim->GetTransform()->SetScale(Vec3(27.15f, 10.50f, 10.50f));

			AddGameObject(pThirdFloorWallRim);
		}

		// 천장틀
		{
			DecoObject* pThirdFloorWallRim = Factory::CreateObject<DecoObject>(Vec3(2.70f, 27.71f, 43.35f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\WallRim.fbx");

			pThirdFloorWallRim->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
			pThirdFloorWallRim->GetTransform()->SetScale(Vec3(38.17f, 10.50f, 10.50f));

			AddGameObject(pThirdFloorWallRim);
		}

		// 3층 좌측 난간 상부(가로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-12.98f, 12.65f, 15.71f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(7.46f, 12.23f, 12.23f));

			AddGameObject(pThirdFloorBannisterTop);
		}

		// 3층 좌측 난간 하부(가로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-12.90f, 10.88f, 15.52f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(7.38f, 12.23f, 12.23f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 좌측 난간 상부(세로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(-8.93f, 12.65f, 23.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(14.17f, 12.23f, 12.23f));
			pThirdFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

			AddGameObject(pThirdFloorBannisterTop);
		}

		// 3층 좌측 난간 하부(세로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(-8.93f, 10.85f, 23.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(14.17f, 12.23f, 12.23f));
			pThirdFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 우측 난간 상부(가로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(17.85f, 12.65f, 15.71f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(7.46f, 12.23f, 12.23f));
			AddGameObject(pThirdFloorBannisterTop);
		}

		// 3층 우측 난간 하부(가로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(17.92f, 10.88f, 15.52f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(7.38f, 12.23f, 12.23f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 우측 난간 상부(세로)
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(13.42f, 12.65f, 23.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");

			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(14.17f, 12.23f, 12.23f));
			pThirdFloorBannisterTop->GetTransform()->SetRotation(Vec3(0.00f, 90.f, 0.00f));

			AddGameObject(pThirdFloorBannisterTop);
		}

		// 3층 우측 난간 하부(세로)
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(13.42f, 10.85f, 23.29f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(14.17f, 12.23f, 12.23f));
			pThirdFloorBannisterBase->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 3층 중앙 난간 상부
		{
			DecoObject* pThirdFloorBannisterTop = Factory::CreateObject<DecoObject>(Vec3(2.39f, 12.67f, 30.77f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\bannisterTop.fbx");
			pThirdFloorBannisterTop->GetTransform()->SetScale(Vec3(10.43f, 12.23f, 12.23f));

			AddGameObject(pThirdFloorBannisterTop);
		}

		// 3층 중앙 난간 하부
		{
			DecoObject* pThirdFloorBannisterBase = Factory::CreateObject<DecoObject>(Vec3(2.39f, 10.88f, 30.77f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\BannisterBase.fbx");

			pThirdFloorBannisterBase->GetTransform()->SetScale(Vec3(9.90f, 12.23f, 12.23f));
			AddGameObject(pThirdFloorBannisterBase);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-15.90f, 25.80f, 22.80f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(13.50f, 13.50f, 13.50f));
			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-15.90f, 25.80f, 35.78f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(13.50f, 13.50f, 13.50f));
			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-9.90f, 25.80f, 42.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(12.75f, 12.75f, 12.75f));
			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(2.70f, 25.80f, 42.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(12.75f, 12.75f, 12.75f));

			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수평)
		{
			DecoObject* pThirdFloorCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(15.15f, 25.80f, 42.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainHorizontal.fbx");

			pThirdFloorCurtainHorizontal->GetTransform()->SetScale(Vec3(12.75f, 12.75f, 12.75f));

			AddGameObject(pThirdFloorCurtainHorizontal);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-9.90f, 19.50f, 42.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(10.50f, 10.50f, 10.50f));
			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(15.00f, 19.50f, 42.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(10.50f, 10.50f, 10.50f));
			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-16.12f, 19.50f, 23.02f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(10.50f, 10.50f, 10.50f));
			pThirdFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
			AddGameObject(pThirdFloorCurtainVertical);
		}

		// 커튼(수직)
		{
			DecoObject* pThirdFloorCurtainVertical = Factory::CreateObject<DecoObject>(Vec3(-16.12f, 19.50f, 35.85f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CurtainVertical1.fbx");

			pThirdFloorCurtainVertical->GetTransform()->SetScale(Vec3(10.50f, 10.50f, 10.50f));
			pThirdFloorCurtainVertical->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pThirdFloorCurtainVertical);
		}



		// 액자 1
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-17.17f, 21.52f, 18.23f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 2
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-17.17f, 17.02f, 20.40f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 3.00f, 3.00f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 3
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-17.17f, 18.23f, 25.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 4
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-17.17f, 21.30f, 28.72f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame0.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 5
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-17.17f, 21.52f, 32.62f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 3.00f, 3.00f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 6
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-17.17f, 17.70f, 39.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 7
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-6.45f, 22.05f, 43.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 8
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-4.50f, 17.55f, 43.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 3.00f, 3.00f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 9
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(-1.42f, 20.48f, 43.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame3.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 10
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(2.47f, 19.73f, 43.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame0.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 11
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(7.12f, 20.17f, 43.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame2.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 3.00f, 3.00f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 액자 12
		{
			DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(11.10f, 18.00f, 43.58f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\PaintingFrame4.fbx");
			pPaintingFrame->GetTransform()->SetScale(Vec3(4.72f, 4.72f, 4.72f));
			pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pPaintingFrame);
		}

		// 좌측 항아리들
		{
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-9.15f, 11.40f, 41.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-7.50f, 11.40f, 41.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(-8.32f, 11.40f, 40.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				AddGameObject(pPotHeal);
			}
		}

		// 우측 항아리들
		{
			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(13.65f, 11.40f, 41.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(12.00f, 11.40f, 41.92f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

				AddGameObject(pPotHeal);
			}

			{
				DecoObject* pPotHeal = Factory::CreateObject<DecoObject>(Vec3(12.83f, 11.40f, 40.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\POT_HEAL_Generic.fbx");
				pPotHeal->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
				pPotHeal->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));
				AddGameObject(pPotHeal);
			}
		}

		// 좌측 의자
		{
			DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(-13.50f, 12.75f, 21.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Chair.fbx");

			pChair->GetTransform()->SetScale(Vec3(4.50f, 4.50f, 4.50f));
			pChair->GetTransform()->SetRotation(Vec3(0.00f, 216.35f, 0.00f));
			AddGameObject(pChair);
		}

		// 2단 선반
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-15.67f, 12.38f, 20.70f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(5.25f, 5.25f, 5.25f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.00f, -90.f, 0.00f));

			AddGameObject(pTwoTierShelf);


		}

		// 2단 선반
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-15.67f, 12.38f, 25.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(5.25f, 5.25f, 5.25f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));

			AddGameObject(pTwoTierShelf);
		}

		// 캐비넷
		{
			DecoObject* pCabinet = Factory::CreateObject<DecoObject>(Vec3(-14.85f, 15.15f, 31.42f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\CabinetStructure.fbx");

			pCabinet->GetTransform()->SetScale(Vec3(9.00f, 9.00f, 9.00f));
			pCabinet->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));

			AddGameObject(pCabinet);
		}

		// 2단 책상
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-15.67f, 12.38f, 36.97f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(5.25f, 5.25f, 5.25f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.00f, -90.00f, 0.00f));
			AddGameObject(pTwoTierShelf);
		}

		// 2단 선반
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(-14.10f, 12.38f, 40.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(5.25f, 5.25f, 5.25f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
			AddGameObject(pTwoTierShelf);
		}

		// 2단 선반 (우측)
		{
			DecoObject* pTwoTierShelf = Factory::CreateObject<DecoObject>(Vec3(18.67f, 12.38f, 40.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\TwoTierShelf.fbx");
			pTwoTierShelf->GetTransform()->SetScale(Vec3(5.25f, 5.25f, 5.25f));
			pTwoTierShelf->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));

			AddGameObject(pTwoTierShelf);
		}

		// 선반 위 화분
		{
			DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(20.10f, 15.30f, 40.65f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionPlantPot.fbx");
			pMansionPlantPot->GetTransform()->SetScale(Vec3(2.25f, 2.25f, 2.25f));
			pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));

			AddGameObject(pMansionPlantPot);
		}

		// 문틀
		{
			DecoObject* pFloorDoorFrame = Factory::CreateObject<DecoObject>(Vec3(2.25f, 13.58f, 43.31f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\doorSideFrame.fbx");

			pFloorDoorFrame->GetTransform()->SetScale(Vec3(6.36f, 6.55f, 9.75f));
			AddGameObject(pFloorDoorFrame);
		}
		// 문
		{
			DecoObject* pFloorDoor = Factory::CreateObject<DecoObject>(Vec3(2.25f, 13.58f, 43.31f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor.fbx");

			pFloorDoor->GetTransform()->SetScale(Vec3(6.75f, 6.38f, 6.38f));

			AddGameObject(pFloorDoor);
		}
		// 열쇠구멍
		{
			DecoObject* pFloorDoorLock = Factory::CreateObject<DecoObject>(Vec3(2.25f, 13.58f, 43.16f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MansionLockDoor (1).fbx");

			pFloorDoorLock->GetTransform()->SetScale(Vec3(1.50f, 1.50f, 1.50f));
			AddGameObject(pFloorDoorLock);
		}

#pragma endregion

		// 1F 샹들리에
		{
			DecoObject* pChandelier = Factory::CreateObject<DecoObject>(Vec3(1.72f, 31.80f, 27.53f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ChandelierWithChain.fbx");
			pChandelier->GetTransform()->SetScale(Vec3(37.50f, 37.50f, 37.50f));
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
			pChandelier->DrawShadow(false);
		}

		// 3F 샹들리에
		{
			DecoObject* pChandelier = Factory::CreateObject<DecoObject>(Vec3(1.72f, 27.30f, -34.28f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\ChandelierWithChain.fbx");
			pChandelier->GetTransform()->SetScale(Vec3(37.50f, 37.50f, 37.50f));
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
			pChandelier->DrawShadow(false);
		}



		// 샹들리에 라이트
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(1.72f, 58.35f, -34.35f));
			pTransform->SetRotation(Vec3(90.0f, 0.00f, 0.00f));
			pTransform->SetScale(Vec3(75.00f, 75.00f, 75.00f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.52f, 0.52f, 0.38f));
			pLight->SetAmbient(Vec3(0.00f, 0.00f, 0.00f));
			pLight->SetLightRange(150.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);


		}

		// 샹들리에 라이트
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(1.72f, 42.90f, 27.97f));
			pTransform->SetRotation(Vec3(90.0f, 0.00f, 0.00f));
			pTransform->SetScale(Vec3(75.00f, 75.00f, 75.00f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.52f, 0.52f, 0.38f));
			pLight->SetAmbient(Vec3(0.00f, 0.00f, 0.00f));
			pLight->SetLightRange(50.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}


		// PotHead
		{
			PhysicsInfo info = {};

			Npc* pPotHead = Factory::CreateObjectHasPhysical<Npc>(Vec3(2.17f, 10.88f, 32.40f), info, L"Deferred", L"..\\Resources\\FBX\\Npc\\Npc_PotHead.fbx");
			pPotHead->GetTransform()->SetScale(Vec3(1.12f, 1.12f, 1.12f));
			pPotHead->GetTransform()->SetRotation(Vec3(-90.0f, 0.00f, 0.00f));

			// 애니메이션의 이름은 FBX에 저장되어 있는 것을 그대로 가져오므로 해당 FBX를 사용하는 클래스의 생성자와 같은 특정 부분에서
			// 사용하기 편한 이름으로 일괄적으로 바꿔줄 필요가 있음
			//pPotHead->GetAnimator()->RenameAnimation(L"Sat_loop", L"PotHead_Idle");

			//// 반복 여부를 설정하는 함수 (Finished 플래그를 사용할 수 없음)
			//pPotHead->GetAnimator()->SetLoop(L"PotHead_Idle", true);

			//// 인덱스 번호로도 사용 가능
			//pPotHead->GetAnimator()->SetLoop(9, true);

			//// HasExit는 현재 애니메이션 실행중에 다른 애니메이션이 실행되었을 때 바로 넘길건지 여부를 결정 (기본적으로 true)
			//// 이 값이 false면 애니메이션 플레이 도중 다른 애니메이션 Play가 실행되었을 때 기존 애니메이션이 다 끝나고 실행됨
			//pPotHead->GetAnimator()->SetHasExitFlag(9, false);

			//// 애니메이션 실행하는 방법은 2D와 비슷하게 애니메이션 이름, 반복할건지 여부를 넣어주면 됨
			//pPotHead->GetAnimator()->Play(L"PotHead_Idle", true);

			AddGameObject(pPotHead);

		}


	}



	void HallColliderCheckMap::InitColliderAdd()
	{
		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(27.00f, 0.75f, 27.00f);
			Ground* pStGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.17f, -4.43f, -35.70f), physicsInfo, L"Forward", L"");

			AddGameObject(pStGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.40f, 0.75f, 16.20f);
			Ground* pStairR = Factory::CreateObjectHasPhysical<Ground>(Vec3(12.52f, -0.90f, -15.30f), physicsInfo, L"Forward", L"");
			pStairR->GetTransform()->SetRotation(Vec3(333.f, 0.00f, 0.00f));

			AddGameObject(pStairR);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.40f, 0.75f, 16.20f);
			Ground* pStairL = Factory::CreateObjectHasPhysical<Ground>(Vec3(-7.65f, -0.90f, -15.30f), physicsInfo, L"Forward", L"");
			pStairL->GetTransform()->SetRotation(Vec3(333.f, 0.00f, 0.00f));

			AddGameObject(pStairL);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(14.70f, 0.75f, 17.25f);
			Ground* pNdFGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.17f, 2.85f, -14.92f), physicsInfo, L"Forward", L"");

			AddGameObject(pNdFGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(39.75f, 0.75f, 24.23f);
			Ground* pNdFGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.17f, 2.85f, 3.82f), physicsInfo, L"Forward", L"");

			AddGameObject(pNdFGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.17f, 0.75f, 23.02f);
			Ground* pNdFGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.17f, 2.85f, 3.82f), physicsInfo, L"Forward", L"");

			AddGameObject(pNdFGround);
			//SetGizmoTarget(pNdFGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.40f, 0.75f, 16.20f);
			Ground* pNdStairR = Factory::CreateObjectHasPhysical<Ground>(Vec3(10.50f, 6.45f, 23.10f), physicsInfo, L"Forward", L"");
			pNdStairR->GetTransform()->SetRotation(Vec3(333.f, 0.00f, 0.00f));

			AddGameObject(pNdStairR);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.40f, 0.75f, 16.20f);
			Ground* pNdStairL = Factory::CreateObjectHasPhysical<Ground>(Vec3(-6.07f, 6.45f, 23.10f), physicsInfo, L"Forward", L"");
			pNdStairL->GetTransform()->SetRotation(Vec3(333.f, 0.00f, 0.00f));

			AddGameObject(pNdStairL);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(41.07f, 0.75f, 14.29f);
			Ground* pRdFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.17f, 10.12f, 37.65f), physicsInfo, L"Forward", L"");

			AddGameObject(pRdFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(4.10f, 10.77f, 14.29f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-10.50f, 0.75f, -40.50f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(7.68f, 17.24f, 38.57f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(18.38f, 2.55f, -26.85f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.38f, 17.24f, 9.34f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(24.90f, 2.55f, -3.22f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.38f, 17.24f, 9.34f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(24.90f, 2.55f, 10.20f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.38f, 17.24f, 33.61f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(24.90f, 6.82f, 28.95f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(4.20f, 17.24f, 16.88f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-11.32f, 4.57f, -15.15f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(4.20f, 17.24f, 16.88f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-14.17f, 4.57f, -27.30f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(8.82f, 14.48f, 17.77f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-12.38f, 3.30f, 23.77f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(12.24f, 14.48f, 1.78f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(2.33f, 5.93f, 30.15f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 14.48f, 14.79f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.38f, 5.93f, 23.10f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 14.48f, 14.79f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(8.10f, 5.93f, 23.10f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 14.48f, 14.79f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(13.35f, 5.93f, 23.10f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 14.48f, 14.79f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.15f, -0.45f, -14.33f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 14.48f, 14.79f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.15f, -0.45f, -14.33f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 14.48f, 14.79f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-4.57f, -0.45f, -14.33f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.80f, 18.08f, 49.62f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-17.10f, 12.15f, 17.62f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.45f, 6.32f, 1.48f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-5.47f, -1.88f, -47.25f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.45f, 6.32f, 1.48f);
			WallObject* pStLFloor = Factory::CreateObjectHasPhysical<WallObject>(Vec3(10.27f, -1.88f, -47.25f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
			//SetGizmoTarget(pStLFloor);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.03f, 0.75f, 3.90f);
			Ground* pStLFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(24.45f, 2.78f, 3.97f), physicsInfo, L"Forward", L"");

			AddGameObject(pStLFloor);
		}

	}

	void HallColliderCheckMap::FuncObjectAdd()
	{
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(4.15f, 2.85f, 1.97f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(2.33f, -2.78f, -48.60f), physicsInfo, L"Forward", L"", false, MapType::EntranceHallMap, 3);
			AddGameObject(pTelZone);
			//SetGizmoTarget(pTelZone);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.66f, 2.85f, 4.13f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(26.03f, 4.57f, 3.53f), physicsInfo, L"Forward", L"", false, MapType::RightMap, 4);
			AddGameObject(pTelZone);
			//SetGizmoTarget(pTelZone);
		}
	}

	void HallColliderCheckMap::Exit()
	{
	}
}