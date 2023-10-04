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

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "CinematicCamMove.h"
#include "InterfaceAlphaScript.h"
#include "InterfaceButtonScript.h"
#include "StartButtonScript.h"
#include "LogoBlinkScript.h"
#include "PlayerMoveScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	TitleScene::TitleScene()
		: Scene(SceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();

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
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::Right2Map);
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
		// - Monster_Player_TestScene
		if (IS_DOWN(KeyType::L))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::EntranceHallMap);
		}

		// 영진
		// - MainOfficeMap - 3개치 분량
		// - RightMap
		if (IS_DOWN(KeyType::K))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::HallColliderCheckMap);
		}
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
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);

		// Create Main Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"MainCamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			pGameObject->AddComponent(new CameraMoveScript);
			//pGameObject->AddComponent(new yj::CinematicCamMove);

			pCamera->SetCullingMask(LayerType::Interface, true);
			pCamera->SetCullingMask(LayerType::Mirror, true);

			pTransform->SetPosition(Vec3(0.f, 0.f, 0.f));
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

		// Title
		{
			Interface* pLogoInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 180.f, 0.f), Vec2(300.f, 200.f), L"..\\Resources\\Texture\\DD_Logo_Smooth_Dropshadow.png");
			pLogoInterface->AddComponent(new LogoBlinkScript);
			AddGameObject(pLogoInterface);
		}

		// Select Interface
		{
			mpSelectedInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 180.f, -3.f), Vec2(40.f, 39.f), L"..\\Resources\\Texture\\icon_crowfoot.png");
			mpSelectedInterface->SetAlpha(0.8f);
			AddGameObject(mpSelectedInterface);
		}

		// Buttons
		{		
			// 현모
			{
				Interface* pInterface = Factory::CreateButtonInterface<Interface>(Vec3(-450.f, -200.f, -1.f), Vec2(50.f, 50.f), ButtonInfo());
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"현모", MapType::Right2Map));

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
				StartButtonScript* pScript = pInterface->AddComponent(new StartButtonScript(L"영진", MapType::Right2Map));

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

		//Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Capsule;
			physicsInfo.size = Vec3(0.8f, 0.5f, 0.8f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, -100.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			pPlayer->SetDontDestroyObject(L"Player");

			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));
			pPlayer->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.6f, 0.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);
			AddGameObject(pPlayer);
			//SetMeshTarget(pPlayer);
		}



	}

	void TitleScene::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	}
}

