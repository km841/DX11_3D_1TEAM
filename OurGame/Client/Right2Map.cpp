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
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "Monster.h"
#include "UI.h"
#include "FireLamp.h"
#include "Ladder.h"
#include "Bat.h"
#include "LadderCollider.h"
#include "Effect.h"
#include "SwordGlareEffect.h"
#include "SpiderWeb.h"
#include "Mirror.h"
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
#include "UIText.h"
#include "Animator.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "RotateKeyScript.h"
#include "BonFireScript.h"
#include "MonsterCrackScript.h"
#include "SlashGlareScript.h"
#include "PlayerMoveOverMapScript.h"
#include "OwnerFollowScript.h"
#include "FocusingScript.h"
#include "HeadText.h"

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

		mpMainCamera->GetTransform()->SetPosition(Vec3(-38.7f, 32.f, 24.0f));
		mpMainCamera->GetTransform()->SetRotation(Vec3(54.3f, 135.f, 0.f));

		OwnerFollowScript* pFollowScript = spPlayerHolder->GetScript<OwnerFollowScript>();
		pFollowScript->SetOffset(Vec3(-15.f, 31.f, 16.5f));
		mpMainCamera->GetScript<FocusingScript>()->SetFocusingMode(true);

		PLAYER->GetKeyInfo().SetLeftKey(KeyType::RIGHT);
		PLAYER->GetKeyInfo().SetForwardKey(KeyType::DOWN);

		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{
			case 5:
				PLAYER->GetTransform()->SetPosition(Vec3(-15.6f, -10.0f, 24.4f));
				break;

			case 6: // CorriderMap -> Right2Map
				PLAYER->GetTransform()->SetPosition(Vec3(-23.8f, 1.5f, 7.6f));
				break;
			}
		}
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
		

	
	

		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{
			case 1:
				PLAYER->GetTransform()->SetPosition(Vec3(-0.9f, -8.27f, 19.1f));
				break;
			}
		}
		DisableDirLight();

		InitObjectAdd();
		InitCollidertAdd();
		InitFuncObjAdd();

		//마법사
		{
			Mage* pMage = Factory::CreateMage(Vec3(-16.f, 2.f, -10.f), Vec3(-90.f, 0.f, 180.f));
			AddGameObject(pMage);
			//SetGizmoTarget(pMage);
		}

		//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(-14.f, 1.5f, -5.8f), Vec3(-90.f, 0.f, 180.f));
			AddGameObject(pBat);
		}

		//박쥐
		{
			Bat* pBat = Factory::CreateBat(Vec3(-18.f, 1.5f, -5.8f), Vec3(-90.f, 0.f, 180.f));
			AddGameObject(pBat);
		}

		//초록 거미
		{
			Lurker* pLurker = Factory::CreateLurker(Vec3(9.5f, 1.5f, 10.8f), Vec3(-90.f, 0.f, 60.f));
			AddGameObject(pLurker);
		}

		//초록 거미
		{
			Lurker* pLurker = Factory::CreateLurker(Vec3(9.5f, 1.5f, 1.5f), Vec3(-90.f, 0.f, 120.f));
			AddGameObject(pLurker);
		}
	}

	void Right2Map::Exit()
	{
	}

	void Right2Map::InitObjectAdd()
	{

		shared_ptr<Texture> pTemp = nullptr;
		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(50.f, 1.f, 40.f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Right2_Ground.fbx");
			pTemp = pGround->GetMeshRenderer()->GetMaterial()->GetTexture(0);
			pGround->GetTransform()->SetScale(Vec3(50.f, 1.f, 50.f));

			AddGameObject(pGround);
		}

		// 미러
		{
			GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(0.f, 0.1f, 0.f), L"Forward", L"", false, LayerType::Mirror);

			pMirror->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTemp);
			pMirror->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pMirror->AddComponent(new Mirror);
			pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pMirror->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));

			AddGameObject(pMirror);
		}

		// Side
		{
			DecoObject* pSideWall = Factory::CreateObject<DecoObject>(Vec3(1.7f, 7.3f, -0.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Right2_Side.fbx");
			pSideWall->GetTransform()->SetScale(Vec3(46.7f, 50.f, 46.5f));

			AddGameObject(pSideWall);
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

			//// 식탁보
			//{
			//	DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(21.7f, 8.6f, 6.5f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\tableCloth.fbx");
			//	pTableCloth->GetTransform()->SetScale(Vec3(15.4f, 10.f, 23.3f));
			//	pTableCloth->GetTransform()->SetRotation(Vec3(-180.f, 0.f, 180.f));
			//	AddGameObject(pTableCloth);
			//}
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
					AddGameObject(pEmptyBox);
				}
			}

			// 사다리
			{
				DecoObject* pLadderObj = Factory::CreateObject<DecoObject>(Vec3(5.f, 2.43f, -1.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Ladder.fbx");
				pLadderObj->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));
				AddGameObject(pLadderObj);

				//GameObject* pEnterPoint = Factory::CreateObject<GameObject>(Vec3(5.0f, 0.33f, -0.9f), L"Deferred", L"",false, LayerType::DecoObject);
				//AddGameObject(pEnterPoint);
				////SetGizmoTarget(pEnterPoint);
				//
				//GameObject* pExitPoint = Factory::CreateObject<GameObject>(Vec3(5.0f, 6.13f, 1.3f), L"Deferred", L"",false, LayerType::DecoObject);
				//AddGameObject(pExitPoint);

				//PhysicsInfo mEnterInfo;
				//mEnterInfo.eActorType = ActorType::Static;
				//mEnterInfo.eGeometryType = GeometryType::Box;
				//mEnterInfo.size = Vec3(0.95f, 1.9f, 0.45f);
				//GameObject* pEnterCol = Factory::CreateObjectHasPhysical<GameObject>(Vec3(5.0f, 1.0f, -0.8f), mEnterInfo, L"Deferred", L"",false, LayerType::Ladder);
				//AddGameObject(pEnterCol);

				//PhysicsInfo mExitInfo;
				//mExitInfo.eActorType = ActorType::Static;
				//mExitInfo.eGeometryType = GeometryType::Box;
				//mExitInfo.size = Vec3(0.95f, 1.9f, 0.45f);
				//GameObject* pExitCol = Factory::CreateObjectHasPhysical<GameObject>(Vec3(5.0f, 6.63f, -1.3f), mExitInfo, L"Deferred", L"",false,LayerType::Ladder);
				//AddGameObject(pExitCol);

				//yj::Ladder* pLadder = Factory::CreateObject<yj::Ladder>(Vec3(5.f, 2.43f, -1.1f), L"Deferred", L"",false, pEnterPoint, pExitPoint,pEnterCol,pExitCol);
				//AddGameObject(pLadder);

				{
					PhysicsInfo mEnterInfo;
					mEnterInfo.eActorType = ActorType::Static;
					mEnterInfo.eGeometryType = GeometryType::Box;
					mEnterInfo.size = Vec3(1.f, 0.5f, 0.5f);

					LadderCollider* pEnterLadderCol = Factory::CreateObjectHasPhysical<LadderCollider>(Vec3(5.0f, 0.3f, -0.9f), mEnterInfo, L"Deferred", L"");
					pEnterLadderCol->SetPlayerToMovePos(Vec3(5.0f, 0.33f, -0.9f));
					pEnterLadderCol->SetDir(DirectionEvasion::BACKWARD);
					pEnterLadderCol->SetName(L"LadderEnterCol");

					AddGameObject(pEnterLadderCol);
					
				}

				{
					PhysicsInfo mExitInfo;
					mExitInfo.eActorType = ActorType::Static;
					mExitInfo.eGeometryType = GeometryType::Box;
					mExitInfo.size = Vec3(1.f, 0.5f, 0.5f);

					LadderCollider* pExitLadderCol = Factory::CreateObjectHasPhysical<LadderCollider>(Vec3(5.0f, 6.7f, -1.1f), mExitInfo, L"Deferred", L"");
					pExitLadderCol->SetPlayerToMovePos(Vec3(5.0f, 5.7f, -1.1f));
					pExitLadderCol->SetPlayerToDownPos(Vec3(5.0f, 5.5f, -0.9f));
					pExitLadderCol->SetDir(DirectionEvasion::BACKWARD);
					pExitLadderCol->SetName(L"LadderExitCol");

					AddGameObject(pExitLadderCol);
					//SetGizmoTarget(pExitLadderCol);
					
				}
			}
		}

		//// 식탁보
		//{
		//	DecoObject* pTableCloth = Factory::CreateObject<DecoObject>(Vec3(-5.6f, 5.3f, 11.9f), L"Deferred_CullNone", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\tableCloth.fbx");
		//	pTableCloth->GetTransform()->SetScale(Vec3(13.4f, 10.f, 12.4f));
		//	pTableCloth->GetTransform()->SetRotation(Vec3(-180.f, 0.f, 180.f));

		//	//pKey->AddComponent(new RotateKeyScript);
		//	AddGameObject(pTableCloth);
		//}

		// 꼭대기 나무판자
		{
			DecoObject* pTopShelf = Factory::CreateObject<DecoObject>(Vec3(17.f, 6.1f, -2.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\TopShelf.fbx");
			pTopShelf->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
			pTopShelf->GetTransform()->SetRotation(AXIS_Z, -1.f);

			AddGameObject(pTopShelf);
		}

		// 바닥 러그
		{
			DecoObject* pBottomRug = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 0.2f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Rug_Mark.fbx");
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
				//SetGizmoTarget(pLadder);
				
				{
					PhysicsInfo mEnterInfo;
					mEnterInfo.eActorType = ActorType::Static;
					mEnterInfo.eGeometryType = GeometryType::Box;
					mEnterInfo.size = Vec3(2.5f, 0.5f, 1.5f);

					LadderCollider* pEnterLadderCol = Factory::CreateObjectHasPhysical<LadderCollider>(Vec3(-14.f, 0.4f, -14.5f), mEnterInfo, L"Deferred", L"");
					pEnterLadderCol->SetPlayerToMovePos(Vec3(-14.f, 0.03f, -14.6f));
					pEnterLadderCol->SetDir(DirectionEvasion::BACKWARD);
					pEnterLadderCol->SetName(L"LadderEnterCol");

					AddGameObject(pEnterLadderCol);
					//SetGizmoTarget(pEnterLadderCol);
				}

				{
					PhysicsInfo mExitInfo;
					mExitInfo.eActorType = ActorType::Static;
					mExitInfo.eGeometryType = GeometryType::Box;
					mExitInfo.size = Vec3(2.f, 0.5f, 1.5f);

					LadderCollider* pExitLadderCol = Factory::CreateObjectHasPhysical<LadderCollider>(Vec3(-14.f, 6.03f, -14.7f), mExitInfo, L"Deferred", L"");
					pExitLadderCol->SetPlayerToMovePos(Vec3(-14.f, 6.03f, -14.7f));
					pExitLadderCol->SetPlayerToDownPos(Vec3(-14.f, 5.83f, -14.5f));
					pExitLadderCol->SetDir(DirectionEvasion::BACKWARD);
					pExitLadderCol->SetName(L"LadderExitCol");

					AddGameObject(pExitLadderCol);


				}

			}

			// to 2floor 사다리
			{
				DecoObject* pLadder = Factory::CreateObject<DecoObject>(Vec3(2.67f, 7.f, -17.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Ladder.fbx");
				pLadder->GetTransform()->SetScale(Vec3(6.5f, 17.8f, 6.5f));
				//SetGizmoTarget(pLadder);
				AddGameObject(pLadder);

				{
					PhysicsInfo mEnterInfo;
					mEnterInfo.eActorType = ActorType::Static;
					mEnterInfo.eGeometryType = GeometryType::Box;
					mEnterInfo.size = Vec3(1.f, 0.5f, 0.5f);

					LadderCollider* pEnterLadderCol = Factory::CreateObjectHasPhysical<LadderCollider>(Vec3(2.67f, 0.7f, -17.5f), mEnterInfo, L"Deferred", L"");
					pEnterLadderCol->SetPlayerToMovePos(Vec3(2.67f, 0.73f, -17.5f));
					pEnterLadderCol->SetDir(DirectionEvasion::BACKWARD);
					pEnterLadderCol->SetName(L"LadderEnterCol");

					AddGameObject(pEnterLadderCol);
					//SetGizmoTarget(pEnterLadderCol);
				}

				{
					PhysicsInfo mExitInfo;
					mExitInfo.eActorType = ActorType::Static;
					mExitInfo.eGeometryType = GeometryType::Box;
					mExitInfo.size = Vec3(1.f, 0.5f, 0.5f);

					LadderCollider* pExitLadderCol = Factory::CreateObjectHasPhysical<LadderCollider>(Vec3(2.67f, 15.8f, -17.5f), mExitInfo, L"Deferred", L"");
					pExitLadderCol->SetPlayerToMovePos(Vec3(2.67f, 15.8f, -17.5f));
					pExitLadderCol->SetPlayerToDownPos(Vec3(2.67f, 15.6f, -17.5f));
					pExitLadderCol->SetDir(DirectionEvasion::BACKWARD);
					pExitLadderCol->SetName(L"LadderExitCol");

					AddGameObject(pExitLadderCol);
					

				}

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
				PhysicsInfo physicsInfo;
				physicsInfo.eActorType = ActorType::Kinematic;
				physicsInfo.eGeometryType = GeometryType::Box;
				physicsInfo.size = Vec3(2.94f, 2.94f, 2.94f);


				DecoObject* pLampUpper = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampUpper->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampUpper->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
				AddGameObject(pLampUpper);


				DecoObject* pLampBelow = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampBelow->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampBelow->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
				AddGameObject(pLampBelow);

				DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(-5.8f, 8.4f, -16.5f), L"Fire", L"");
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

				yj::FireLamp* pFireLamp = Factory::CreateObjectHasPhysical<yj::FireLamp>(Vec3(-5.8f, 7.4f, -16.5f),physicsInfo, L"Deferred", L"", false, pLampUpper, pLampBelow, pBonFire, pLightObject);
				AddGameObject(pFireLamp);
			}

			// 화롯불
			{
				PhysicsInfo physicsInfo;
				physicsInfo.eActorType = ActorType::Kinematic;
				physicsInfo.eGeometryType = GeometryType::Box;
				physicsInfo.size = Vec3(2.94f, 2.94f, 2.94f);


				DecoObject* pLampUpper = Factory::CreateObject<DecoObject>(Vec3(11.1f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampUpper->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampUpper->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
				AddGameObject(pLampUpper);


				DecoObject* pLampBelow = Factory::CreateObject<DecoObject>(Vec3(11.1f, 7.4f, -16.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampBelow->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampBelow->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
				AddGameObject(pLampBelow);


				DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(11.1f, 8.4f, -16.5f), L"Fire", L"");
				pBonFire->GetMeshRenderer()->SetMaterial(pBonFire->GetMeshRenderer()->GetMaterial()->Clone());
				pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
				pBonFire->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
				pBonFire->AddComponent(new BonFireScript);

				AddGameObject(pBonFire);

				DecoObject* pLightObject = nullptr;
				{
					pLightObject = new DecoObject;
					Transform* pTransform = pLightObject->AddComponent(new Transform);
					pTransform->SetPosition(Vec3(11.1f, 7.4f, -16.5f));
					pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
					pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
					Light* pLight = pLightObject->AddComponent(new Light);
					pLight->SetDiffuse(Vec3(0.8f, 0.5f, 0.2f));
					pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
					pLight->SetLightRange(10.f);
					pLight->SetLightType(LightType::PointLight);
					AddGameObject(pLightObject);
				}
				
				yj::FireLamp* pFireLamp = Factory::CreateObjectHasPhysical<yj::FireLamp>(Vec3(11.1f, 7.4f, -16.5f), physicsInfo, L"Deferred", L"", false, pLampUpper, pLampBelow, pBonFire, pLightObject);
				AddGameObject(pFireLamp);
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

				PhysicsInfo physicsInfo;
				physicsInfo.eActorType = ActorType::Kinematic;
				physicsInfo.eGeometryType = GeometryType::Box;
				physicsInfo.size = Vec3(2.94f, 2.94f, 2.94f);


				DecoObject* pLampUpper = Factory::CreateObject<DecoObject>(Vec3(-5.9f, 7.4f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampUpper->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampUpper->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
				AddGameObject(pLampUpper);


				DecoObject* pLampBelow = Factory::CreateObject<DecoObject>(Vec3(-5.9f, 7.4f, -2.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\GRANDMA_FireLamp.fbx");

				pLampBelow->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				//pTwoTierFootAbs->GetTransform()->SetRotation(AXIS_Y, 180.f);
				//pFirelamp->AddComponent(new PlacementScript);
				pLampBelow->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
				AddGameObject(pLampBelow);

				DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(-5.9f, 8.4f, -2.8f), L"Fire", L"");
				pBonFire->GetMeshRenderer()->SetMaterial(pBonFire->GetMeshRenderer()->GetMaterial()->Clone());
				pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
				pBonFire->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
				pBonFire->AddComponent(new BonFireScript);
				AddGameObject(pBonFire);

				DecoObject* pLightObject = nullptr;
				{
					pLightObject = new DecoObject;
					Transform* pTransform = pLightObject->AddComponent(new Transform);
					pTransform->SetPosition(Vec3(-5.9f, 7.4f, -2.8f));
					pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
					pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
					Light* pLight = pLightObject->AddComponent(new Light);
					pLight->SetDiffuse(Vec3(0.8f, 0.5f, 0.2f));
					pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
					pLight->SetLightRange(10.f);
					pLight->SetLightType(LightType::PointLight);
					AddGameObject(pLightObject);
				}

				yj::FireLamp* pFireLamp = Factory::CreateObjectHasPhysical<yj::FireLamp>(Vec3(-5.9f, 7.4f, -2.8f), physicsInfo, L"Deferred", L"", false, pLampUpper, pLampBelow, pBonFire, pLightObject);
				pFireLamp->SetIsBurn();
				AddGameObject(pFireLamp);
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

			pChandelier->DrawShadow(false);
			AddGameObject(pChandelier);
		}


		

		// 샹들리에 라이트
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(10.7f, 45.7f, 9.8f));
			pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.5f, 0.5f, 0.2f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(55.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}

		//// Spider Web
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(2.f, 4.f, 4.f);

		//	SpiderWeb* pWeb = Factory::CreateObjectHasPhysical<SpiderWeb>(Vec3(0.f, 2.f, 0.f), info, L"SpiderWeb", L"..\\Resources\\FBX\\Map\\Dungeon\\Right2Map\\Cobweb_Flat.fbx");
		//	pWeb->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
		//	pWeb->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));
		//	AddGameObject(pWeb);
		//}
	}

	void Right2Map::InitCollidertAdd()
	{
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(35.57f, 11.28f, 3.7f);

			Ground* pCol1 = Factory::CreateObjectHasPhysical<Ground>(Vec3(3.5f,0.1f,16.3f), physicsInfo, L"Deferred", L"");

			AddGameObject(pCol1);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.78f, 11.28f, 23.27f);

			Ground* pCol2= Factory::CreateObjectHasPhysical<Ground>(Vec3(21.7f,3.4f,6.5f), physicsInfo, L"Deferred", L"");

			AddGameObject(pCol2);

		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(20.88f, 11.28f, 3.35f);

			Ground* pCol3 = Factory::CreateObjectHasPhysical<Ground>(Vec3(13.7f, 0.0f, -2.7f), physicsInfo, L"Deferred", L"");

			AddGameObject(pCol3);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.68f, 0.341f, 3.35f);

			Ground* pCol4 = Factory::CreateObjectHasPhysical<Ground>(Vec3(14.9f, 6.8f, -2.7f), physicsInfo, L"Deferred", L"");
			pCol4->GetTransform()->SetRotation(Vec3(0.0f,0.0f,201.0f));
			AddGameObject(pCol4);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.4f, 6.0f, 8.84f);

			Ground* pCol5 = Factory::CreateObjectHasPhysical<Ground>(Vec3(-5.7f, 2.7f, 10.2f), physicsInfo, L"Deferred", L"");
			AddGameObject(pCol5);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(12.24f, 6.0f, 3.18f);

			Ground* pCol6 = Factory::CreateObjectHasPhysical<Ground>(Vec3(-10.1f, 2.7f, -16.3f), physicsInfo, L"Deferred", L"");
			AddGameObject(pCol6);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(17.5f, 6.0f, 3.18f);

			Ground* pCol7 = Factory::CreateObjectHasPhysical<Ground>(Vec3(17.5f, 2.7f, -16.3f), physicsInfo, L"Deferred", L"");
			AddGameObject(pCol7);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.78f, 6.41f, 3.43f);

			Ground* pCol8 = Factory::CreateObjectHasPhysical<Ground>(Vec3(-5.9f, 2.7f, -2.8f), physicsInfo, L"Deferred", L"");
			AddGameObject(pCol8);
		}

	}
	void Right2Map::InitFuncObjAdd()
	{
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.4f, 4.1f, 4.82f);

			yj::TeleportZone* pRightZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(2.5f, 17.7f, -17.2f), physicsInfo, L"Deferred", L"", false, MapType::DiningColliderCheckMap,6);
			AddGameObject(pRightZone);
		}

		{
			GameObject* pClimbUpTextBox = Factory::CreateObject<GameObject>(Vec3::One, L"Forward", L"", false, LayerType::InterativeCol);
			pClimbUpTextBox->GetMeshRenderer()->GetMaterial()->SetTexture(0, GET_SINGLE(Resources)->Load<Texture>(L"Texture3D", L"..\\Resources\\Texture\\PopUpClimbUppng.png"));
			pClimbUpTextBox->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pClimbUpTextBox->GetTransform()->SetPosition(Vec3(-14.3f, 1.5f, -14.2f));
			pClimbUpTextBox->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pClimbUpTextBox->GetTransform()->SetScale(Vec3(2.0f, 1.0f, 1.0f));
			AddGameObject(pClimbUpTextBox);
			yj::HeadText* pClimbUpTextScript = pClimbUpTextBox->AddComponent<yj::HeadText>();
			pClimbUpTextScript->SetDectetorPos(Vec3(14.9f, 1.2f, -14.3f));
			//SetGizmoTarget(pClimbUpTextBox);
		}

		{
			GameObject* pClimbUpTextBox = Factory::CreateObject<GameObject>(Vec3::One, L"Forward", L"", false, LayerType::InterativeCol);
			pClimbUpTextBox->GetMeshRenderer()->GetMaterial()->SetTexture(0, GET_SINGLE(Resources)->Load<Texture>(L"Texture3D", L"..\\Resources\\Texture\\PopUpClimbUppng.png"));
			pClimbUpTextBox->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pClimbUpTextBox->GetTransform()->SetPosition(Vec3(-14.3f, 1.5f, -14.2f));
			pClimbUpTextBox->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pClimbUpTextBox->GetTransform()->SetScale(Vec3(2.0f, 1.0f, 1.0f));
			AddGameObject(pClimbUpTextBox);
			yj::HeadText* pClimbUpTextScript = pClimbUpTextBox->AddComponent<yj::HeadText>();
			pClimbUpTextScript->SetDectetorPos(Vec3(14.9f, 1.2f, -14.3f));
			//SetGizmoTarget(pClimbUpTextBox);
		}
	}
}
