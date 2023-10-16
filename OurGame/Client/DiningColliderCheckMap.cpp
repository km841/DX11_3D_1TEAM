#include "pch.h"
#include "DiningColliderCheckMap.h"
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
#include "WallObject.h"
#include "HeadRoller.h"
#include "JarDoor.h"
#include "TeleportZone.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Bat.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
#include "IrreparablePot.h"
#include "KeyPot.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Fireplace.h"
#include "Mirror.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "PaperBurnScript.h"
#include "PlayerMoveOverMapScript.h"
#include "BonFireScript.h"
#include "OwnerFollowScript.h"
#include "FocusingScript.h"

/* Event */
#include "SceneChangeEvent.h"

#include "ContactCallback.h"
#include "Timer.h"


namespace sy
{
	DiningColliderCheckMap::DiningColliderCheckMap()
		: Map(MapType::DiningColliderCheckMap)
	{
	}

	DiningColliderCheckMap::~DiningColliderCheckMap()
	{
	}

	void DiningColliderCheckMap::Initialize()
	{
		Map::Initialize();
	}

	void DiningColliderCheckMap::Start()
	{
		Map::Start();
		mpMainCamera->GetTransform()->SetPosition(Vec3(-9.7f, 16.6f, 13.1f));
		mpMainCamera->GetTransform()->SetRotation(Vec3(51.7f, 139.7f, 0.f));

		OwnerFollowScript* pFollowScript = spPlayerHolder->GetScript<OwnerFollowScript>();
		pFollowScript->SetOffset(Vec3(-9.4f, 24.3f, 12.f));
		mpMainCamera->GetScript<FocusingScript>()->SetFocusingMode(true);

		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{

			case 6:
				PLAYER->GetTransform()->SetPosition(Vec3(-0.2f, -7.8f, 1.1f));
				break;
			}
		}
	}

	void DiningColliderCheckMap::Update()
	{
		Map::Update();
	}

	void DiningColliderCheckMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void DiningColliderCheckMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void DiningColliderCheckMap::Render()
	{
		Map::Render();
	}

	void DiningColliderCheckMap::Enter()
	{
		//배경맵 하얀색으로 만들어주는 코드
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));
		DisableDirLight();

		InitObjectAdd();
		InitColliderAdd();
		FuncObjectAdd();
	}

	void DiningColliderCheckMap::InitObjectAdd()
	{

#pragma region 어드민
#pragma endregion

		//DecoObject == 콜라이더 없는 오브젝트
		//WallObject == 콜라이더 있는 오브젝트

		//Forward == 빛 계산이 없는 명령어
		//Deferred == 빛 계산이 있는 명령어

		//->GetTransform()->SetPositionExcludingColliders == 콜라이더를 제외하고 오브젝트만 [이동] 시키는 함수
		//->GetTransform()->SetRotationExcludingColliders == 콜라이더를 제외하고 오브젝트만 [회전] 시키는 함수



		// 전체맵 가이드라인 벽
		{
			DecoObject* pNormalBase = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom.fbx", true);
			pNormalBase->SetReflect(false);
			pNormalBase->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pNormalBase->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			pNormalBase->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr, 2, 0); //3번째인자 == 텍스처 첫번째 png 인지 두번째 png인지 구별하게 해주는거
			pNormalBase->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(115, 118, 128), 2, 0); //3번째인자 == 텍스처 첫번째 png 인지 두번째 png인지 구별하게 해주는거
			AddGameObject(pNormalBase);
		}

#pragma region 1층
		//1층
		{
			// 1층 바닥 - Floor
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(30.f, 0.1f, 37.f);

				Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");
				
				pFloor->GetTransform()->SetScale(Vec3(37.f, 37.f, 37.f));
				pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));

				AddGameObject(pFloor);
			}

			// 미러
			{
				GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(0.f, -8.4f, 6.6f), L"Forward", L"", false, LayerType::Mirror);

				pMirror->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pMirror->AddComponent(new Mirror);
				pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
				pMirror->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));
				pMirror->GetMirror()->SetAlpha(0.1f);

				AddGameObject(pMirror);
			}
			//1층 계단 - Stairs
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(5.f, 0.1f, 14.f);

				Ground* pStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-12.f, -5.2f, 0.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

				pStairs->GetTransform()->SetScale(Vec3(15.f, 15.f, 15.f));
				pStairs->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
				pStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 1.f));
				pStairs->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));
				AddGameObject(pStairs);
			}

			{
				//1-2층 계단 앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-16.7f, -0.7f, -6.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

				AddGameObject(pColumnFull);
			}

			//1층 계단 벽 - Cube1 
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				WallObject* pCube1 = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-9.8f, -4.f, 1.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube1.fbx");

				pCube1->GetTransform()->SetScale(Vec3(30.f, 26.f, 25.f));
				pCube1->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
				pCube1->GetTransform()->SetPositionExcludingColliders(Vec3(8.f, -0.3f, -1.0f));
				pCube1->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube1);
			}

			{
				//1층 맨앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.f, 3.f, 25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 40.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//1층 ㄱ자 사이 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.5f, -2.8f, -5.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 22.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}



			//외곽 감싸주는 계단 ㄱ자 라인 줄 -wallPanel_Merged
			{
				DecoObject* pWallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(0.2f, -5.35f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\wallPanel_Merged.fbx");

				pWallPanel_Merged->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

				AddGameObject(pWallPanel_Merged);
			}


			// 핑크색 잠금 여는 문 -POT_Door_4_Variant
			{
				PhysicsInfo info = {};
				info.eActorType = ActorType::Static;
				info.size = Vec3(3.8f, 5.f, 0.4f);

				WallObject* pPotLeft = Factory::CreateObjectHasPhysical<WallObject>(Vec3(8.75f, -5.5f, -5.8f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\POT_Door_4_Variant.fbx");
				pPotLeft->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
				pPotLeft->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.5f, 4.7f));


				pPotLeft->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
				pPotLeft->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
				pPotLeft->GetMeshRenderer()->SetSubsetRenderFlag(2, false);
				pPotLeft->GetMeshRenderer()->SetSubsetRenderFlag(3, false);
				pPotLeft->GetMeshRenderer()->SetSubsetRenderFlag(4, false);
				pDoorLeft = pPotLeft;

				AddGameObject(pPotLeft);

				{
					PhysicsInfo info = {};
					info.eActorType = ActorType::Static;
					info.size = Vec3(3.8f, 5.f, 0.4f);

					WallObject* pPotRight = Factory::CreateObjectHasPhysical<WallObject>(Vec3(8.75f, -5.5f, -5.8f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\POT_Door_4_Variant.fbx");
					pPotRight->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
					pPotRight->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.5f, 4.7f));

					AddGameObject(pPotRight);

					pPotRight->GetMeshRenderer()->SetSubsetRenderFlag(5, false);
					pPotRight->GetMeshRenderer()->SetSubsetRenderFlag(6, false);
					pPotRight->GetMeshRenderer()->SetSubsetRenderFlag(7, false);
					pPotRight->GetMeshRenderer()->SetSubsetRenderFlag(8, false);
					pPotRight->GetMeshRenderer()->SetSubsetRenderFlag(9, false);
					pDoorRight = pPotRight;
				}
			}

			// 핑크색 문 프레임 나무 - DoorFrame
			{
				DecoObject* pDoorFrame = Factory::CreateObject<DecoObject>(Vec3(8.75f, -6.0f, -1.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\DoorFrame.fbx");

				pDoorFrame->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

				AddGameObject(pDoorFrame);
			}

			//벽난로 -fireplace
			{
				DecoObject* pfireplace = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -5.f, -1.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\fireplace.fbx");

				pfireplace->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


				AddGameObject(pfireplace);
			}

			//1층 바닥 구멍 테두리 - RimStarter
			{
				DecoObject* pRimStarter = Factory::CreateObject<DecoObject>(Vec3(-0.3f, -8.5f, 3.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\RimStarter.fbx");

				pRimStarter->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
				pRimStarter->SetReflect(false);

				AddGameObject(pRimStarter);
			}

			//1층 벽에 붙은 벽돌모양 테두리 오른쪽 벽1 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(13.5f, -7.2f, -5.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 90.f, 0.f));

				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 오른쪽 벽2 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(4.0f, -7.2f, -5.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 90.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 오른쪽 벽3 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -7.2f, -5.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 6.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 90.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽1 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, -2.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽2 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 2.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽3 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));

				AddGameObject(pWallPanel);
			}
			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽4 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 12.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽4 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 16.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽5 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			// 1층 천장 샹들리에 - ChandelierWithChain
			{
				DecoObject* pChandelierWithChain = Factory::CreateObject<DecoObject>(Vec3(0.0f, 20.0f, 16.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ChandelierWithChain.fbx");

				pChandelierWithChain->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
				pChandelierWithChain->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				pChandelierWithChain->DrawShadow(false);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 13, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 13, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 13, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 14, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 14, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 14, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 15, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 15, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 15, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 16, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 16, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 16, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 17, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 17, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 17, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 18, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 18, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 18, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 19, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 19, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 19, 0);

				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloom(true, 20, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomPower(1.5f, 20, 0);
				pChandelierWithChain->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 0.4f, 1.f), 20, 0);


				AddGameObject(pChandelierWithChain);
			}

			//1층 테이블 1 -CofeeTableWithCloth
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(4.5f, 2.f, 6.5f);

				Ground* pCofeeTableWithCloth = Factory::CreateObjectHasPhysical<Ground>(Vec3(5.67f, -7.4f, 16.1f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CofeeTableWithCloth.fbx");

				pCofeeTableWithCloth->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pCofeeTableWithCloth->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));

				AddGameObject(pCofeeTableWithCloth);
			}

			//1층 테이블 2 -CofeeTableWithCloth
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(4.5f, 2.f, 6.5f);

				Ground* pCofeeTableWithCloth = Factory::CreateObjectHasPhysical<Ground>(Vec3(-6.3f, -7.4f, 16.1f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CofeeTableWithCloth.fbx");

				pCofeeTableWithCloth->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pCofeeTableWithCloth->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));

				AddGameObject(pCofeeTableWithCloth);
			}

			//1층 러그 - Rug_Mark
			{
				DecoObject* pRug_Mark = Factory::CreateObject<DecoObject>(Vec3(-0.2f, -8.4f, 16.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Rug_Mark.fbx");

				pRug_Mark->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pRug_Mark->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pRug_Mark);
			}

			//1층 체어 1 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.0f, -7.6f, 17.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));

				AddGameObject(pChair);
			}

			//1층 체어 2 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(3.0f, -7.6f, 22.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, -120.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));

				AddGameObject(pChair);
			}

			//1층 체어 3 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(3.0f, -7.6f, 10.5f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, 120.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
				AddGameObject(pChair);
			}

			//1층 체어 4 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.8f, -7.6f, 22.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, -60.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));

				AddGameObject(pChair);
			}

			//1층 체어 5 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-10.f, -7.6f, 22.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, -150.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));

				AddGameObject(pChair);
			}

			//1층 체어 6 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.8f, -7.6f, 11.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, 60.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));

				AddGameObject(pChair);
			}


		}
#pragma endregion




#pragma region 2층

		//2층
		{
			// 2층 바닥 - floorextension_nocollider
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(27.2f, 0.1f, 19.f);

				Ground* pfloorextension_nocollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -1.87f, -15.4f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

				pfloorextension_nocollider->GetTransform()->SetScale(Vec3(110.f, 10.f, 145.f));
				pfloorextension_nocollider->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 62.5f));
				pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));
				AddGameObject(pfloorextension_nocollider);
			}

			//2층 계단 - Stairs
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(5.f, 0.1f, 14.2f);

				Ground* pStairs_2floor = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.2f, 1.6f, -22.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

				pStairs_2floor->GetTransform()->SetScale(Vec3(15.f, 15.5f, 15.f));
				pStairs_2floor->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pStairs_2floor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.1f, 0.f));
				pStairs_2floor->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));


				AddGameObject(pStairs_2floor);
			}

			{
				//2층 계단 아래 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(5.6f, -1.8f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 51.f, 21.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));

				AddGameObject(pWallRim);

			}

			{
				//2층 계단-벽 사이 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-3.4f, -1.8f, -25.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 51.f, 21.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));

				AddGameObject(pWallRim);

			}

			//2층 계단 벽 왼쪽- Cube2
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -20.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

				pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(1.1f, -0.5f, 12.1f));
				pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube2);
			}

			//2층 계단 벽 오른쪽 - Cube2
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -25.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

				pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(1.1f, -0.5f, 12.1f));
				pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube2);
			}

			{
				//2층 난간 아래 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(3.8f, -1.9f, -6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 27.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));

				AddGameObject(pWallRim);

			}
			{
				//2층 난간 위 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(3.8f, -0.4f, -6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 27.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));

				AddGameObject(pWallRim);

			}


			// 2층 계단 아랫벽 - Cube3
			{
				DecoObject* pCube3 = Factory::CreateObject<DecoObject>(Vec3(3.f, 0.5f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube3.fbx");

				pCube3->GetTransform()->SetScale(Vec3(13.f, 13.f, 13.f));
				pCube3->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pCube3);
			}

			{
				//2층 맨앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.7f, -6.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(19.f, 16.f, 19.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);


			}

			{
				//2층 중간 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.7f, -13.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(19.f, 16.f, 19.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);

			}

			{
				//2층 계단 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.1f, 2.5f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 계단 앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.8f, -0.7f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 계단 앞 벽쪽 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.8f, -0.7f, -24.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);

			}

			{
				//2-3층 계단 벽쪽 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.1f, 9.8f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 맨오른쪽 큰기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-27.6f, 6.2f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 난간 막대기 - BannisterStick
				for (float i = 0; i < 12; i++)
				{
					DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(7.5f - (i * 1.5f), -1.f, -6.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

					pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
					pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

					AddGameObject(pBannisterStick);

				}
			}

			{
				//벽에 붙은 그림 - AssortedPaintings
				DecoObject* pAssortedPaintings = Factory::CreateObject<DecoObject>(Vec3(-4.3f, 6.4f, -12.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\AssortedPaintings.fbx");

				pAssortedPaintings->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pAssortedPaintings->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

				AddGameObject(pAssortedPaintings);
			}

			//2층 테이블 1 -CofeeTableWithCloth
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(4.5f, 2.f, 6.5f);

				WallObject* pCofeeTableWithCloth = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-0.1f, -0.7f, -9.6f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CofeeTableWithCloth.fbx");

				pCofeeTableWithCloth->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pCofeeTableWithCloth->GetTransform()->SetRotation(Vec3(0.0f, -90.f, 0.f));

				AddGameObject(pCofeeTableWithCloth);
			}

			//2층 러그 - Rug_Mark
			{
				DecoObject* pRug_Mark = Factory::CreateObject<DecoObject>(Vec3(-9.2f, -1.8f, -13.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Rug_Mark.fbx");

				pRug_Mark->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pRug_Mark->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

				AddGameObject(pRug_Mark);
			}

			//2층 왕의자 - fancyChairSit
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pfancyChairSit = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-0.1f, -1.1f, -14.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\fancyChairSit.fbx");

				pfancyChairSit->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pfancyChairSit->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				pfancyChairSit->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 0.f, 0.f));
				pfancyChairSit->GetTransform()->SetPositionExcludingColliders(Vec3(.0f, 3.6f, 11.f));

				AddGameObject(pfancyChairSit);
			}

		}
#pragma endregion




#pragma region 3층
		// 3층 바닥 콜라이더
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.5f, 0.1f, 50.f);

			Ground* pWallObject = Factory::CreateObjectHasPhysical<Ground>(Vec3(11.f, 4.9f, 0.f), info, L"Deferred", L"");
			AddGameObject(pWallObject);
		}

		// 3층 바닥 - floorextension_nocollider
		{
			Ground* pfloorextension_nocollider = Factory::CreateObject<Ground>(Vec3(11.5f, 5.f, 169.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

			pfloorextension_nocollider->GetTransform()->SetScale(Vec3(20.f, 10.f, 400.f));
			pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));
			AddGameObject(pfloorextension_nocollider);
		}

		{
			//3층 벽쪽 커튼 1 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 18.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 2 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 9.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 3 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}


		{
			//3층 벽쪽 커튼 4 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, -11.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 5 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 6 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(2.1f, 12.5f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 7 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-7.1f, 12.5f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pCurtainHorizontal);
		}





		{
			//3층 ㄱ자 벽쪽 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(6.3f, 9.8f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}


		{
			//3층 중간 벽쪽 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(6.3f, 9.8f, -6.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}


		{
			//3층 난간 맨왼쪽 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.4f, 6.2f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);

		}


		{
			//3층 난간 맨왼쪽 두번째 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 6.2f, 18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pColumnFull);
		}

		{
			//3층 난간 맨왼쪽 세번째 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 6.2f, 13.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}

		{
			//3층 난간 긴 막대기 아래 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 5.1f, 4.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 49.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3층 난간 긴 막대기 위 가로줄 
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 6.5f, 4.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 49.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3층 난간 긴 막대기 반대편 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(14.1f, 5.1f, 10.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 72.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

			AddGameObject(pWallRim);
		}

		{
			//3층 난간 긴 막대기 반대편 천장 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(14.3f, 14.2f, 12.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 20.f, 73.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));


			AddGameObject(pWallRim);
		}

		{
			//3층 난간 긴 천장 세로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-5.7f, 14.2f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 20.f, 40.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));


			AddGameObject(pWallRim);
		}

		{
			//3층 난간 짧은 막대기 아래 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 5.1f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3층 난간 짧은 막대기 위 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 6.5f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

			AddGameObject(pWallRim);

		}

		{
			//3층 난간 짧은 막대기 세로 /  아래 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.8f, 5.1f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3층 난간 짧은 막대기 세로 / 위 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.8f, 6.5f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pWallRim);

		}

		{
			//난간 막대기 - BannisterStick
			DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

			pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pBannisterStick);
		}

		{
			//난간 막대기 - BannisterStick
			DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 20.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

			pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pBannisterStick);
		}

		{
			//난간 막대기 - BannisterStick
			for (float i = 0; i < 9; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 11.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}

		{
			//난간 막대기 - BannisterStick
			for (float i = 0; i < 3; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, -7.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}

		{
			//난간 막대기 - BannisterStick
			for (float i = 0; i < 3; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, -14.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}





#pragma endregion
	}

	void DiningColliderCheckMap::InitColliderAdd()
	{

		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Kinematic;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(49.f, 49.f, 49.f);

		pDoorCol = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(9.f, 5.8f, -14.7f), physicsInfo, L"Forward", L"");

		pDoorCol->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
		pDoorCol->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
		AddGameObject(pDoorCol);

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(49.f, 49.f, 49.f);

			pDoorCol = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(9.f, 5.8f, -14.7f), physicsInfo, L"Forward", L"");

			pDoorCol->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pDoorCol->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pDoorCol);
		}
	}
	void DiningColliderCheckMap::FuncObjectAdd()
	{
		{
			GameObject* pLightObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pLightObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(0.3f, 11.2f, 11.2f));
			pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Light* pLight = pLightObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.8f, 0.8f, 0.5f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(80.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pLightObject);
			
		}

		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(-0.5f, -5.6f, -4.f));
			pTransform->SetRotation(Vec3(71.9f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Fireplace* pLight = pGameObject->AddComponent(new Fireplace);
			pLight->SetDiffuse(Vec3(1.0f, 0.3f, 0.3f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(30.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}

		{
			DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -6.5f, -5.2f), L"Fireplace", L"");
			pBonFire->GetMeshRenderer()->SetMaterial(pBonFire->GetMeshRenderer()->GetMaterial()->Clone());
			pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
			pBonFire->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
			pBonFire->AddComponent(new BonFireScript);
			AddGameObject(pBonFire);
		}

		{
			yj::JarDoor* pJarDoor = Factory::CreateObject<yj::JarDoor>(Vec3::Zero, L"Deferred", L"", false, 2, pDoorLeft, pDoorRight, pDoorCol);
			AddGameObject(pJarDoor);


			//키+파란색 항아리 두번째 - POT_Key
			{
				PhysicsInfo physicsInfo;
				physicsInfo.eActorType = ActorType::Kinematic;
				physicsInfo.eGeometryType = GeometryType::Box;
				physicsInfo.size = Vec3(2.f, 3.1f, 2.f);

				yj::KeyPot* pPot2 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(11.65f, 6.35f, 15.85f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\OrgPot.fbx");
				pPot2->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				pPot2->GetTransform()->SetScale(Vec3(3.15f, 2.85f, 3.15f));
				pPot2->SetReceiver(pJarDoor);
				AddGameObject(pPot2);

				PhysicsInfo basePhysicsInfo;
				basePhysicsInfo.eActorType = ActorType::Kinematic;
				basePhysicsInfo.eGeometryType = GeometryType::Box;
				basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

				jh::IrreparablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::IrreparablePot>(Vec3(11.65f, 6.35f, 15.85f), basePhysicsInfo, L"Deferred", L"", false, pPot2);

				AddGameObject(pIrreparablePot);
			}

			//키+파란색 항아리 세번째 - POT_Key
			{
				PhysicsInfo physicsInfo;
				physicsInfo.eActorType = ActorType::Kinematic;
				physicsInfo.eGeometryType = GeometryType::Box;
				physicsInfo.size = Vec3(2.f, 3.1f, 2.f);

				yj::KeyPot* pPot3 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(-6.15f, -4.95f, 17.45f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\OrgPot.fbx");
				pPot3->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
				pPot3->GetTransform()->SetScale(Vec3(3.15f, 2.85f, 3.15f));
				pPot3->SetReceiver(pJarDoor);
				AddGameObject(pPot3);
				//SetGizmoTarget(pPot3);

				PhysicsInfo basePhysicsInfo;
				basePhysicsInfo.eActorType = ActorType::Kinematic;
				basePhysicsInfo.eGeometryType = GeometryType::Box;
				basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

				jh::IrreparablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::IrreparablePot>(Vec3(-6.15f, -4.95f, 17.45f), basePhysicsInfo, L"Deferred", L"", false, pPot3);

				AddGameObject(pIrreparablePot);
			}
		}


		{

			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.8, 3.8f, 4.9f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(8.8f, -6.5f, -9.0f), physicsInfo, L"Deferred", L"", false, MapType::RightSecretPassageMap, 1);
			AddGameObject(pTelZone);
			//SetGizmoTarget(pTelZone);

		}

	}

	void DiningColliderCheckMap::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
	}
}
