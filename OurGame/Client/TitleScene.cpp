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
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::Monster_Player_Test);
		}

		// 영진
		// - MainOfficeMap - 3개치 분량
		// - RightMap
		if (IS_DOWN(KeyType::K))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(MapType::Right2Map);
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

		// Create Shadow Camera
		//GameObject* pShadowCamera = nullptr;
		//{
		//	pShadowCamera = new GameObject(LayerType::Unknown);
		//	pShadowCamera->SetDontDestroyObject(L"ShadowCamera");
		//	Transform* pTransform = pShadowCamera->AddComponent(new Transform);

		//	Camera* pCamera = pShadowCamera->AddComponent(new Camera);

		//	pCamera->SetCullingMask(LayerType::UI, true);

		//	pTransform->SetPosition(Vec3(63.f, 63.f, 61.5f));
		//	pTransform->SetRotation(Vec3(37.2f, 242.f, 180.f));
		//	AddGameObject(pShadowCamera);
		//}
		
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
			UI* pUI = Factory::CreateObject<UI>(Vec3(0.f, 0.f, 0.f), L"Forward", L"");

			pUI->GetTransform()->SetScale(Vec3(RESOLUTION.x / 2.f, RESOLUTION.y / 2.f, 1.f));
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"TitleLogo", L"..\\Resources\\Texture\\Title_Temp.png");
			pUI->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			pUI->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());

			AddGameObject(pUI);
		}

		// Text
		{
			Interface* pInterface = Factory::CreateObject<Interface>(Vec3(-500.f, 200.f, -1.f), L"Interface", L"");
			InterfaceAlphaScript* pScript = pInterface->AddComponent(new InterfaceAlphaScript);
			InterfaceButtonScript* pButton = pInterface->AddComponent(new InterfaceButtonScript);

			//pButton->SetClickedCallback([]() { MessageBoxA(NULL, NULL, NULL, NULL); });

			shared_ptr<Texture> pHoveredTexture = GET_SINGLE(Resources)->Load<Texture>(L"TitleLogo", L"..\\Resources\\Texture\\Title_Temp.png");
			shared_ptr<Texture> pClickedTexture = GET_SINGLE(Resources)->Load<Texture>(L"clicked", L"..\\Resources\\Texture\\blender_uv_grid_2k.png");
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"good", L"..\\Resources\\Texture\\goodjob.png");
			pButton->SetHoveredTexture(pHoveredTexture);
			pButton->SetClickedTexture(pClickedTexture);
			pButton->SetNonHoveredTexture(pTexture);

			pScript->SetAlpha(0.5f);
			pInterface->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

			pInterface->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			pInterface->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			UIText* pText = pInterface->AddComponent(new UIText);

			//pInterface->GetRigidBody()->SetVelocity(Vec3(10.f, 0.f, 0.f));

			pText->SetText(L"즐거운추석");
			pText->SetSize(25.f);
			pText->SetRenderArea(0.f, 0.f, RESOLUTION.x, RESOLUTION.y);
			pText->SetAlignH(TextAlignH::Center);
			pText->SetAlignV(TextAlignV::Top);
			pText->SetShadowOffset(Vec3(1.5f, -1.5f, 0.f));
			pText->Shadow(true);
			pText->SetShadowColor(0.f, 0.f, 0.f, 1.f);
			pText->SetColor(1.f, 0.f, 0.f, 1.f);

			AddGameObject(pInterface);
		}


	}

	void TitleScene::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	}
}

