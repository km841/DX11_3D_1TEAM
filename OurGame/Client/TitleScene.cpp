#include "pch.h"
#include "TitleScene.h"
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
#include "UI.h"
#include "CameraHolder.h"
#include "Elevator.h"
#include "HpUi.h"
#include "ManaUi.h"
#include "Banker.h"

/* Interface */
#include "Interface.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"
#include "AudioSound.h"
#include "Mirror.h"
#include "Animator.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "CinematicCamMove.h"
#include "InterfaceAlphaScript.h"
#include "InterfaceButtonScript.h"
#include "StartButtonScript.h"
#include "LogoBlinkScript.h"
#include "PlayerMoveScript.h"
#include "PlayerMoveOverMapScript.h"
#include "FocusingScript.h"
#include "OwnerFollowScript.h"
#include "CutSceneCameraMoveScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	TitleScene::TitleScene()
		: Map(SceneType::Title)
		, mpFollowTarget(nullptr)
		, mpFocusTarget(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
		

		AudioSound* pSound = PLAYER->AddComponent(new AudioSound);

		pSound->SetSound(L"BGM", this, true, "..\\Resources\\Sound\\TitleBGM.mp3");
		pSound->Play(10);
	
	}

	void TitleScene::Update()
	{
		Scene::Update();

		if (IS_DOWN(KeyType::A))
		{
			if (pTextBox != nullptr)
			{

				pTextBox->SetWriteTexts(0, 5);
				pTextBox->Apear();
			}
		}

		if (nullptr != mpActiveInterface)
		{
			Vec3 pos = mpActiveInterface->GetTransform()->GetPosition();
			pos.x -= 80.f;
			pos.y += 15.f;

			mpSelectedInterface->GetTransform()->SetPosition(pos);
		}

		// 현모
		// - GrandmaBossMap
		// - Right2Map
		if (IS_DOWN(KeyType::P))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::MainOfficeMap);
		}

		// 지형
		// - HallColliderCheckMap - 2개치 분량
		// - CorridorRightMap
		// - RightSecretPassageMap
		if (IS_DOWN(KeyType::O))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::PhysicsTest);
		}

		// 상연
		// - DiningColliderCheckMap
		// - EntranceHallMap
		// - LeftSecretFightMap
		// - LeftSecretTrialMap
		// - Monster_Player_Test
		if (IS_DOWN(KeyType::L))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::Monster_Player_Test);
		}

		// 영진
		// - MainOfficeMap - 3개치 분량
		// - RightMap
		if (IS_DOWN(KeyType::K))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::Right2Map);
		}
		/*MainOfficeMap,
			CorridorRightMap,
			DiningColliderCheckMap,
			EntranceHallMap,
			GrandmaBossMap,
			HallColliderCheckMap,
			LeftSecretFightMap,
			LeftSecretTrialMap,
			Right2Map,
			RightMap,
			RightSecretPassageMap,
			BossMap,*/



		/*Vec3 pos = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetGameObject()->GetTransform()->GetPosition();
		wstring strPos = {};
		strPos += L"x = " + std::to_wstring(pos.x) + L" ";
		strPos += L"y = " + std::to_wstring(pos.y) + L" ";
		strPos += L"z = " + std::to_wstring(pos.z);

		Vec3 rot = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetGameObject()->GetTransform()->GetRotation();
		wstring strRot = {};
		strRot += L"x = " + std::to_wstring(rot.x) + L" ";
		strRot += L"y = " + std::to_wstring(rot.y) + L" ";
		strRot += L"z = " + std::to_wstring(rot.z);
		FONT->DrawString(strPos, 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);
		FONT->DrawString(strRot, 30.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);*/
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::FinalUpdate()
	{
		Scene::FinalUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::Destroy()
	{
		Scene::Destroy();
	}

	void TitleScene::Enter()
	{

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster_ProjectTile);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::MonsterSlowCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::MonsterCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ladder);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::InterativeCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::DecoObject);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Portal);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Portal);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Trigger);

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::PlayerCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::WallObject);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::ArrowCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::DecoObject);

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PlayerCol, LayerType::Monster_ProjectTile);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::ArrowCol, LayerType::Item);

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::WallObject);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::PotCell);


		//Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(0.8f, 0.5f, 0.8f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, -100.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			pPlayer->SetDontDestroyObject(L"Player");
			pPlayer->SetReflect(true);
			pPlayer->DrawShadow(false);

			AudioSound* pSound = PLAYER->AddComponent(new AudioSound);

			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			yj::PlayerMoveOverMapScript* pMoveOverSc = pPlayer->AddComponent(new yj::PlayerMoveOverMapScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));
			pPlayer->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.6f, 0.f));

			//pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			//SetMeshTarget(pPlayer);
		}

		// Create DirLight
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"DirLight");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(0.f, 10.f, 0.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(1.f, 1.f, 1.f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightDirection(Vec3(0.f, -1.f, 0.f));
			pLight->SetLightType(LightType::DirectionalLight);
			AddGameObject(pGameObject);
		}

		{
			mpFocusTarget = Factory::CreateObject<DecoObject>(Vec3(7.f, -7.f, -6.f), L"Forward", L"");
			mpFocusTarget->SetDontDestroyObject(L"PlayerFocusTarget");
			AddGameObject(mpFocusTarget);

			spPlayerHolder = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f));
			spPlayerHolder->SetDontDestroyObject(L"PlayerFollowTarget");
			AddGameObject(spPlayerHolder);
		}

		InitObject();
		InitCamera();
		InitUI();

		AddSceneChangeCallback(L"플레이어 충돌 초기화", []()
			{
				GET_SINGLE(CollisionManager)->ClearAllCollisionForObject(PLAYER);
			});
	}

	void TitleScene::Exit()
	{
	
		PLAYER->GetAudioSound()->SetSound(L"BGM");
		PLAYER->GetAudioSound()->Stop();
		PLAYER->GetRigidBody()->ApplyGravity();
		ChangeCameraMode();
	}

	void TitleScene::InitCamera()
	{
		// Create Main Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"MainCamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pGameObject->AddComponent(new RigidBody);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			pGameObject->AddComponent(new CameraMoveScript);
			FocusingScript* pScript = pGameObject->AddComponent(new FocusingScript);
			pScript->SetFollowTarget(spPlayerHolder);
			//////pScript->SetFocusingTarget(mpFocusTarget);
			OwnerFollowScript* pFollowScript = spPlayerHolder->AddComponent(new OwnerFollowScript(PLAYER));
			pFollowScript->SetOffset(Vec3(-0.f, 30.f, 20.f));
			////pGameObject->AddComponent(new yj::CinematicCamMove);

			pCamera->SetCullingMask(LayerType::Interface, true);
			pCamera->SetCullingMask(LayerType::Mirror, true);

			pTransform->SetPosition(Vec3(-12.7f, 19.f, 40.2f));
			pTransform->SetRotation(Vec3(52.6f, 162.f, 0.f));
			AddGameObject(pGameObject);
		}

		// Create UI Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"UICamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			pCamera->SetProjectionType(ProjectionType::Orthographic);
			pCamera->EnableAllCullingMask();
			pCamera->SetCullingMask(LayerType::Interface, false);

			pTransform->SetPosition(Vec3(0.f, 0.f, 0.f));
			AddGameObject(pGameObject);
		}

		// Create CutScene Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"CutSceneCamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pGameObject->AddComponent(new RigidBody);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			pGameObject->AddComponent(new CameraMoveScript);
			FocusingScript* pScript = pGameObject->AddComponent(new FocusingScript);
			pScript->SetFollowTarget(spPlayerHolder);
			//pScript->SetFocusingTarget(spCutSceneFocusingTarget);
			pScript->SetFocusingMode(false);
			jh::CutSceneCameraMoveScript* pCutSceneCameraScript = pGameObject->AddComponent(new jh::CutSceneCameraMoveScript);
			pCutSceneCameraScript->SetLeft(Vec3(3.4f, -2.91f, 22.6f), Vec3(10.52f, 174.23f, 0.f));
			pCutSceneCameraScript->SetRight(Vec3(-3.3f, -2.91f, 21.1f), Vec3(10.52f, 163.5f, 0.f));
			pCamera->SetCullingMask(LayerType::Interface, true);
			pCamera->SetCullingMask(LayerType::Mirror, true);

			pTransform->SetPosition(Vec3(3.4f, -2.91f, 22.6f));
			pTransform->SetRotation(Vec3(10.52f, 174.23f, 0.f));
			AddGameObject(pGameObject);
		}

		ChangeCameraMode();
	}

	void TitleScene::InitObject()
	{
		{
			/*PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(10.0f, 10.0f, 10.0f);

			Banker* pBanker = Factory::CreateObjectHasPhysical<Banker>(Vec3(13.9f, -6.3f, -8.6f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Banker.fbx");*/
			Banker* pBanker = Factory::CreateObject<Banker>(Vec3(13.9f, -6.3f, -8.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Banker.fbx");
			pBanker->GetTransform()->SetScale(Vec3(1.3f, 1.3f, 1.3f));
			pBanker->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 135.f));

			pBanker->GetAnimator()->Play(L"Banker_WriteLoop", true);
			AddGameObject(pBanker);
		}

		{
			/*PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(10.0f, 10.0f, 10.0f);

			Npc* pHallCrow = Factory::CreateObjectHasPhysical<Npc>(Vec3(-5.2f, -8.f, -10.5f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HallCrowWorker.fbx");*/
			Npc* pHallCrow = Factory::CreateObject<Npc>(Vec3(-5.2f, -8.f, -10.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HallCrowWorker.fbx");
			pHallCrow->GetTransform()->SetScale(Vec3(0.7f, 0.7f, 0.7f));
			pHallCrow->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 135.f));

			AddGameObject(pHallCrow);
		}

		{
			Ground* pFrontGround = Factory::CreateObject<Ground>(Vec3(0.4f, -5.3f, -0.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\uv1.fbx");
			pFrontGround->GetTransform()->SetScale(Vec3(49.0f, 49.0f, 49.0f));

			AddGameObject(pFrontGround);
		}

		{
			Ground* pREFLECTIONS = Factory::CreateObject<Ground>(Vec3(5.5f, -9.0f, -1.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Floor_REFLECTIONS.fbx");
			pREFLECTIONS->GetTransform()->SetScale(Vec3(40, 40, 40));
			pREFLECTIONS->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));
			AddGameObject(pREFLECTIONS);
		}

		{
			GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(4.9f, -8.85f, -12.1f), L"Forward", L"", false, LayerType::Mirror);

			pMirror->GetTransform()->SetScale(Vec3(25.f, 20.f, 20.f));
			pMirror->AddComponent(new Mirror);
			pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pMirror->GetTransform()->SetRotation(Vec3(90.f, 319.4f, 0.f));
			pMirror->GetMirror()->SetAlpha(0.4f);

			AddGameObject(pMirror);
		}

		{
			Ground* pUpstair = Factory::CreateObject<Ground>(Vec3(9.5f, 3.0f, -5.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Upstairs.fbx");
			pUpstair->GetTransform()->SetScale(Vec3(35.f, 35.f, 35.f));

			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloom(true, 7);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 7);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloom(true, 31);
			pUpstair->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 31);


			AddGameObject(pUpstair);
		}

		{
			Ground* pBusStop = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\stairsIsland.fbx");
			pBusStop->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pBusStop->GetTransform()->SetRotation(Vec3(0.0f, -160.0f, 0.0f));
			pBusStop->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.04f, 0.04f));
			AddGameObject(pBusStop);
		}

#pragma region 사무실 책상 리스트
		{
			std::vector<GameObject*> deskList;
			for (int i = 0; i < 9; i++)
			{

				Ground* pDesk = Factory::CreateObject<Ground>(Vec3::Zero, L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Desk.fbx");
				AddGameObject(pDesk);
				deskList.push_back(pDesk);
			}
			deskList[0]->GetTransform()->SetPosition(Vec3(-0.5f, -8.0f, 2.0f));
			deskList[0]->GetTransform()->SetRotation(Vec3(-0.0f, -23.0f, 0.0f));
			deskList[0]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[1]->GetTransform()->SetPosition(Vec3(3.0f, -8.0f, -1.5f));
			deskList[1]->GetTransform()->SetRotation(Vec3(-0.0f, -23.0f, 0.0f));
			deskList[1]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[2]->GetTransform()->SetPosition(Vec3(7.0f, -8.0f, -5.0f));
			deskList[2]->GetTransform()->SetRotation(Vec3(-0.0f, -23.0f, 0.0f));
			deskList[2]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[3]->GetTransform()->SetPosition(Vec3(14.0f, -8.0f, 0.5f));
			deskList[3]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			deskList[3]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[4]->GetTransform()->SetPosition(Vec3(12.9f, -8.0f, 4.9f));
			deskList[4]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			deskList[4]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[5]->GetTransform()->SetPosition(Vec3(11.6f, -8.0f, 9.5f));
			deskList[5]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			deskList[5]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[6]->GetTransform()->SetPosition(Vec3(-6.8f, -8.0f, -10.2f));
			deskList[6]->GetTransform()->SetRotation(Vec3(0.0f, -57.0f, 0.0f));
			deskList[6]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[7]->GetTransform()->SetPosition(Vec3(-1.4f, -8.0f, -11.0f));
			deskList[7]->GetTransform()->SetRotation(Vec3(0.0f, -57.0f, 0.0f));
			deskList[7]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));

			deskList[8]->GetTransform()->SetPosition(Vec3(3.59f, -8.0f, -11.4f));
			deskList[8]->GetTransform()->SetRotation(Vec3(0.0f, -65.0f, 0.0f));
			deskList[8]->GetTransform()->SetScale(Vec3(4.4f, 4.4f, 4.4f));
		}
#pragma endregion

#pragma region 사무실 의자 리스트

		std::vector<GameObject*> chairList;

		for (int i = 0; i < 9; i++)
		{
			Ground* pChair = Factory::CreateObject<Ground>(Vec3(-8.0f, -16.5f, 24.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\ChairBaseMerged.fbx");
			pChair->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));
			pChair->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pChair);
			chairList.push_back(pChair);
		}
		chairList[0]->GetTransform()->SetPosition(Vec3(0.2f, -7.9f, 0.5f));
		chairList[0]->GetTransform()->SetRotation(Vec3(-0.0f, 79.0, 0.0f));
		chairList[0]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[1]->GetTransform()->SetPosition(Vec3(4.5f, -7.9f, -2.7f));
		chairList[1]->GetTransform()->SetRotation(Vec3(0.0f, 36.0, 0.0f));
		chairList[1]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[2]->GetTransform()->SetPosition(Vec3(8.1f, -7.9f, -6.1f));
		chairList[2]->GetTransform()->SetRotation(Vec3(0.0f, 37.0, 0.0f));
		chairList[2]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[3]->GetTransform()->SetPosition(Vec3(13.6f, -7.9f, 1.5f));
		chairList[3]->GetTransform()->SetRotation(Vec3(0.0f, 223.0f, 0.0f));
		chairList[3]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[4]->GetTransform()->SetPosition(Vec3(12.3f, -7.9f, 6.1f));
		chairList[4]->GetTransform()->SetRotation(Vec3(0.0f, 243.0f, 0.0f));
		chairList[4]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[5]->GetTransform()->SetPosition(Vec3(12.3f, -7.9f, 8.5f));
		chairList[5]->GetTransform()->SetRotation(Vec3(0.0f, 52.0f, 0.0f));
		chairList[5]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[6]->GetTransform()->SetPosition(Vec3(5.1f, -7.9f, -11.4f));
		chairList[6]->GetTransform()->SetRotation(Vec3(0.0f, 1.0f, 0.0f));
		chairList[6]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[7]->GetTransform()->SetPosition(Vec3(-2.6f, -7.9f, -11.1f));
		chairList[7]->GetTransform()->SetRotation(Vec3(0.0f, 171.0f, 0.0f));
		chairList[7]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

		chairList[8]->GetTransform()->SetPosition(Vec3(-5.1f, -7.9f, -10.5f));
		chairList[8]->GetTransform()->SetRotation(Vec3(0.0f, -6.0f, 0.0f));
		chairList[8]->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

#pragma endregion

#pragma region "laterWallList"

		std::vector<GameObject*>laterWallList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pLateralWall = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\LateralWall.fbx");
			pLateralWall->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pLateralWall->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pLateralWall);
			laterWallList.push_back(pLateralWall);
		}
		laterWallList[0]->GetTransform()->SetPosition(Vec3(11.7f, -4.3f, -15.5f));
		laterWallList[0]->GetTransform()->SetRotation(Vec3(0.0f, 4.0f, 0.0f));

		laterWallList[1]->GetTransform()->SetPosition(Vec3(21.0f, -4.4f, -6.8f));
		laterWallList[1]->GetTransform()->SetRotation(Vec3(0.0f, -86.0f, 0.0f));
#pragma endregion

#pragma region "WallSlots"

		std::vector<GameObject*>wallSlotList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pWallSlots = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\WallSlots.fbx");
			pWallSlots->GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));
			pWallSlots->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pWallSlots);
			wallSlotList.push_back(pWallSlots);
		}
		wallSlotList[0]->GetTransform()->SetPosition(Vec3(0.3f, -4.6f, -15.9f));
		wallSlotList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		wallSlotList[0]->GetTransform()->SetScale(Vec3(14.0f, 14.0f, 14.0f));

		wallSlotList[1]->GetTransform()->SetPosition(Vec3(21.4f, -4.6f, 4.6f));
		wallSlotList[1]->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		wallSlotList[1]->GetTransform()->SetScale(Vec3(14.0f, 14.0f, 14.0f));

#pragma endregion

#pragma region "WallColumns"

		std::vector<GameObject*>mWallColumnList;

		for (int i = 0; i < 4; i++)
		{
			Ground* pWallColumn = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\WallColumn.fbx");
			pWallColumn->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pWallColumn->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pWallColumn);
			mWallColumnList.push_back(pWallColumn);
		}
		mWallColumnList[0]->GetTransform()->SetPosition(Vec3(-7.3f, -4.8f, -17.8f));
		mWallColumnList[0]->GetTransform()->SetRotation(Vec3(0.0f, -273.0f, 0.0f));
		mWallColumnList[0]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

		mWallColumnList[1]->GetTransform()->SetPosition(Vec3(23.3f, -4.4f, -1.7f));
		mWallColumnList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mWallColumnList[1]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

		mWallColumnList[2]->GetTransform()->SetPosition(Vec3(23.0f, -4.4f, 12.1f));
		mWallColumnList[2]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mWallColumnList[2]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

		mWallColumnList[3]->GetTransform()->SetPosition(Vec3(6.7f, -4.8f, -17.3f));
		mWallColumnList[3]->GetTransform()->SetRotation(Vec3(0.0f, 272.0f, 0.0f));
		mWallColumnList[3]->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));

#pragma endregion

#pragma region "mPostSlotsList"
		std::vector<GameObject*>mPostSlotsList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pPostSlots = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PostSlots.fbx");
			pPostSlots->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pPostSlots->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pPostSlots);
			mPostSlotsList.push_back(pPostSlots);
		}

		mPostSlotsList[0]->GetTransform()->SetPosition(Vec3(-1.6f, -4.0f, -15.1f));
		mPostSlotsList[0]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
		mPostSlotsList[0]->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));

		mPostSlotsList[1]->GetTransform()->SetPosition(Vec3(20.8f, -4.0f, 6.3f));
		mPostSlotsList[1]->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		mPostSlotsList[1]->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));

#pragma endregion

#pragma region "pPostCageDial"
		std::vector<GameObject*>mPostCageDialList;

		for (int i = 0; i < 2; i++)
		{
			Ground* pPostCageDial = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PostCageDial.fbx");
			pPostCageDial->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pPostCageDial->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pPostCageDial);
			mPostCageDialList.push_back(pPostCageDial);
		}

		mPostCageDialList[0]->GetTransform()->SetPosition(Vec3(-1.0f, -3.9f, -14.8f));
		mPostCageDialList[0]->GetTransform()->SetRotation(Vec3(0.0f, 87.0f, 0.0f));
		mPostCageDialList[0]->GetTransform()->SetScale(Vec3(7.0f, 8.5f, 8.5f));

		mPostCageDialList[1]->GetTransform()->SetPosition(Vec3(20.4f, -4.0f, 6.78f));
		mPostCageDialList[1]->GetTransform()->SetRotation(Vec3(0.0f, -3.0f, 0.0f));
		mPostCageDialList[1]->GetTransform()->SetScale(Vec3(7.0f, 8.5f, 8.5f));

#pragma endregion

#pragma region "pMainDesk"
		{
			Ground* pMainDesk = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\MainDesk.fbx");
			pMainDesk->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pMainDesk);

			pMainDesk->GetTransform()->SetPosition(Vec3(13.5f, -7.7f, -9.4f));
			pMainDesk->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pMainDesk->GetTransform()->SetScale(Vec3(14.5f, 14.5f, 14.5f));
		}
#pragma endregion

#pragma region "pTowerDetail"
		{
			Ground* pTowerDetail = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\TowerDetail.fbx");
			pTowerDetail->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pTowerDetail->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pTowerDetail);
			pTowerDetail->GetTransform()->SetPosition(Vec3(15.8f, -2.9f, -11.6));
			pTowerDetail->GetTransform()->SetRotation(Vec3(0.0f, -225.0f, 0.0f));
			pTowerDetail->GetTransform()->SetScale(Vec3(11.5f, 11.5f, 11.5f));
		}
#pragma endregion

#pragma region "Elevator"

		yj::Elevator* elevator = Factory::CreateObject<yj::Elevator>(Vec3(0, 0, 0), L"Deferred", L"");
		AddGameObject(elevator);

#pragma endregion

#pragma region "mPlantBase"

		std::vector<GameObject*> mPlantBaseList;
		for (int i = 0; i < 3; i++)
		{
			Ground* pPlantBase = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PlantBase.fbx");
			pPlantBase->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pPlantBase->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pPlantBase);

			pPlantBase->GetTransform()->SetPosition(Vec3(-2.8f, -7.8f, -5.0f));
			pPlantBase->GetTransform()->SetRotation(Vec3(0.0f, 33.0f, 0.0f));
			pPlantBase->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
			mPlantBaseList.push_back(pPlantBase);
		}

		mPlantBaseList[0]->GetTransform()->SetPosition(Vec3(-3.0f, -7.8f, 4.7f));
		mPlantBaseList[0]->GetTransform()->SetRotation(Vec3(0.0f, 33.0f, 0.0f));
		mPlantBaseList[0]->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

		mPlantBaseList[1]->GetTransform()->SetPosition(Vec3(-21.6f, -7.8f, -7.5f));
		mPlantBaseList[1]->GetTransform()->SetRotation(Vec3(0.0f, -49.0f, 0.0f));
		mPlantBaseList[1]->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));

		mPlantBaseList[2]->GetTransform()->SetPosition(Vec3(-1.0f, -11.4f, 19.2f));
		mPlantBaseList[2]->GetTransform()->SetRotation(Vec3(0.0f, -178.0f, 0.0f));
		mPlantBaseList[2]->GetTransform()->SetScale(Vec3(8.5f, 8.5f, 8.5f));
#pragma endregion

#pragma region TypeMachine

		std::vector<GameObject*> mTypeMachineList;
		for (int i = 0; i < 4; i++)
		{
			Ground* pTypeMachineMerged = Factory::CreateObject<Ground>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\TypeMachineMerged.fbx");
			pTypeMachineMerged->GetTransform()->SetScale(Vec3(9.0f, 9.0f, 9.0f));
			pTypeMachineMerged->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			AddGameObject(pTypeMachineMerged);
			mTypeMachineList.push_back(pTypeMachineMerged);
		}
		mTypeMachineList[0]->GetTransform()->SetPosition(Vec3(11.5f, -6.8f, 9.3f));
		mTypeMachineList[0]->GetTransform()->SetRotation(Vec3(0.0f, 187.0f, 0.0f));
		mTypeMachineList[0]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

		mTypeMachineList[1]->GetTransform()->SetPosition(Vec3(12.6f, -6.8f, 4.8f));
		mTypeMachineList[1]->GetTransform()->SetRotation(Vec3(0.0f, 37.0f, 0.0f));
		mTypeMachineList[1]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

		mTypeMachineList[2]->GetTransform()->SetPosition(Vec3(14.1f, -6.8f, 0.5f));
		mTypeMachineList[2]->GetTransform()->SetRotation(Vec3(0.0f, 37.0f, 0.0f));
		mTypeMachineList[2]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));

		mTypeMachineList[3]->GetTransform()->SetPosition(Vec3(14.1f, -6.8f, 0.5f));
		mTypeMachineList[3]->GetTransform()->SetRotation(Vec3(0.0f, 37.0f, 0.0f));
		mTypeMachineList[3]->GetTransform()->SetScale(Vec3(1.5f, 1.5f, 1.5f));
#pragma endregion

#pragma region SphereLight

		std::vector<GameObject*> mSphereLightList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pSphereLightBase = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\SphereLightBase.fbx");
			AddGameObject(pSphereLightBase);
			pSphereLightBase->GetMeshRenderer()->GetMaterial()->SetBloom(true, 3);
			pSphereLightBase->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 3);
			mSphereLightList.push_back(pSphereLightBase);

		}

		mSphereLightList[0]->GetTransform()->SetPosition(Vec3(6.6f, -1.6f, -15.4f));
		mSphereLightList[0]->GetTransform()->SetRotation(Vec3(0.0f, -20.0f, 0.0f));
		mSphereLightList[0]->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

		mSphereLightList[1]->GetTransform()->SetPosition(Vec3(21.0f, -1.6f, -1.5f));
		mSphereLightList[1]->GetTransform()->SetRotation(Vec3(0.0f, -20.0f, 0.0f));
		mSphereLightList[1]->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

#pragma endregion

#pragma region PostBoard
		{
			DecoObject* pPostBoard = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\PostBoard.fbx");
			AddGameObject(pPostBoard);
			pPostBoard->GetTransform()->SetPosition(Vec3(20.2f, -3.8f, -6.8f));
			pPostBoard->GetTransform()->SetRotation(Vec3(0.0f, -3.0f, 0.0f));
			pPostBoard->GetTransform()->SetScale(Vec3(5.5f, 5.5f, 5.5f));
		}
#pragma endregion

#pragma region HoD_LampPost
		{
			DecoObject* pHoD_LampPost = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\HoD_LampPost.fbx");
			AddGameObject(pHoD_LampPost);
			pHoD_LampPost->GetMeshRenderer()->GetMaterial()->SetBloom(true, 3);
			pHoD_LampPost->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.f, 1.f, 1.f, 1.f), 3);
			pHoD_LampPost->GetTransform()->SetPosition(Vec3(-3.1f, -8.5f, 14.8f));
			pHoD_LampPost->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pHoD_LampPost->GetTransform()->SetScale(Vec3(8.0f, 8.0f, 8.0f));
		}
#pragma endregion

		std::vector<GameObject*> mSideRallingBusStopStairList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pSideRallingBusStopStair = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\SideRallingBusStopStair.fbx");
			AddGameObject(pSideRallingBusStopStair);

			mSideRallingBusStopStairList.push_back(pSideRallingBusStopStair);
		}

		mSideRallingBusStopStairList[0]->GetTransform()->SetPosition(Vec3(-17.4f, -9.5f, 11.5f));
		mSideRallingBusStopStairList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mSideRallingBusStopStairList[0]->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));

		mSideRallingBusStopStairList[1]->GetTransform()->SetPosition(Vec3(-12.3f, -9.5f, 10.0f));
		mSideRallingBusStopStairList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mSideRallingBusStopStairList[1]->GetTransform()->SetScale(Vec3(6.5f, 6.5f, 6.5f));

		{
			DecoObject* pRailing11 = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Railing11.fbx");
			AddGameObject(pRailing11);
			pRailing11->GetTransform()->SetPosition(Vec3(14.3f, -3.3f, 14.7f));
			pRailing11->GetTransform()->SetRotation(Vec3::Zero);
			pRailing11->GetTransform()->SetScale(Vec3(12.5f, 12.5f, 12.5f));
		}

		{
			DecoObject* pRailing10 = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\Railing10.fbx");
			AddGameObject(pRailing10);
			pRailing10->GetTransform()->SetPosition(Vec3(15.9f, -3.3f, 16.6f));
			pRailing10->GetTransform()->SetRotation(Vec3::Zero);
			pRailing10->GetTransform()->SetScale(Vec3(17.5f, 17.5f, 17.5f));
		}

		{
			DecoObject* pGraveyardPlane = Factory::CreateObject<DecoObject>(Vec3(0, 0, 0), L"Deferred", L"..\\Resources\\FBX\\Map\\MainOfficeMap\\GraveyardPlane.fbx");
			AddGameObject(pGraveyardPlane);
			pGraveyardPlane->GetTransform()->SetPosition(Vec3(22.6f, -5.6f, -2.9f));
			pGraveyardPlane->GetTransform()->SetRotation(Vec3(0.0f, -10.0f, 0.0f));
			pGraveyardPlane->GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));
		}
	}

	void TitleScene::InitUI()
	{
		// Title
		{
			Interface* pLogoInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 180.f, 0.f), Vec2(300.f, 200.f), L"..\\Resources\\Texture\\DD_Logo_Smooth_Dropshadow.png");
			pLogoInterface->AddComponent(new LogoBlinkScript);
			pLogoInterface->SetColor(Vec3::Color(230.f, 200.f, 230.f));
			AddGameObject(pLogoInterface);
		}

		// Select Interface
		{
			mpSelectedInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 180.f, -3.f), Vec2(40.f, 39.f), L"..\\Resources\\Texture\\icon_crowfoot.png");
			mpSelectedInterface->SetAlpha(0.8f);
			AddGameObject(mpSelectedInterface);
		}

		// 텍스트 박스
		{
			pTextBox = Factory::CreateInterface<yj::TextBox>(Vec3(0.f, -300.f, -3.f), Vec2(400.0f, 100.0f), L"..\\Resources\\Texture\\TextBox.png");
			pTextBox->SetAlpha(0.8f);
			//pTextBox->SetColor(Vec3::Color(255,255,255));
			AddGameObject(pTextBox);
			//사이즈는 400 100
			pTextBox->Disable();
			pTextBox->SetDontDestroyObject(L"TextBox");
		}

		// HpUi
		{
			GameObject* pHpUiObj = new GameObject(LayerType::Unknown);
			Transform* pTransform = pHpUiObj->AddComponent(new Transform);
			pHpUiObj->AddComponent(new RigidBody);
			AddGameObject(pHpUiObj);
			yj::HpUi* pHpUI = pHpUiObj->AddComponent<yj::HpUi>();
			pHpUI->AddHpUI();
			pHpUiObj->SetDontDestroyObject(L"HpUi");
		}

		// MpUI
		{
			GameObject* pManaUiObj = new GameObject(LayerType::Unknown);
			Transform* pTransform = pManaUiObj->AddComponent(new Transform);
			pManaUiObj->AddComponent(new RigidBody);
			yj::ManaUi* pManaUI = pManaUiObj->AddComponent<yj::ManaUi>();
			pManaUI->AddManaUI();
			pManaUiObj->SetDontDestroyObject(L"MpUi");
			AddGameObject(pManaUiObj);
		}

		// Buttons
		{
			// 현모
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(-450.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());

				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"현모", MapType::LeftSecretFightMap));

				// 클릭 기능을 스크립트로 구현
				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();

				// 클릭했을 때 콜백
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });

				// 마우스가 버튼에서 벗어났을 때
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"현모", 35.f, true); });

				// 마우스가 버튼에 올라갔을 때
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"현모", 40.f, true); mpActiveInterface = pInterface; });

				// 텍스쳐 알파값 지정
				pInterface->SetAlpha(0.f);

				// 텍스트 지정
				pInterface->SetText(L"시작", 25.f, true);

				// 텍스트 컬러 지정
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));
				AddGameObject(pInterface);

				// 임시로 설정
				mpActiveInterface = pInterface;
			}

			// 상연
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(-150.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"상연", MapType::Monster_Player_Test));

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"상연", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"상연", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetAlpha(0.f);

				pInterface->SetText(L"시작", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

			// 지형
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(150.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"지형", MapType::PhysicsTest));

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"지형", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"지형", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetAlpha(0.f);

				pInterface->SetText(L"시작", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

			// 영진
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(450.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"영진", MapType::EntranceHallMap));

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetClickedCallback([=]() { pScript->Start(); });
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"영진", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"영진", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetAlpha(0.f);

				pInterface->SetText(L"시작", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}

			// Exit Button
			{
				ButtonInfo info = {};
				info.clickedCallback = []() { PostQuitMessage(0); };

				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(0.f, -300.f, -1.f), Vec2(50.f, 50.f), info);

				InterfaceButtonScript* pButtonScript = pInterface->GetScript<InterfaceButtonScript>();
				pButtonScript->SetNonHoveredCallback([=]() { pInterface->SetText(L"종료", 35.f, true); });
				pButtonScript->SetHoveredCallback([=]() { pInterface->SetText(L"종료", 40.f, true); mpActiveInterface = pInterface; });

				pInterface->SetText(L"종료", 25.f, true);
				pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f));

				AddGameObject(pInterface);
			}
		}
	}
}
