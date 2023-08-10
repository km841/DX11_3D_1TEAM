#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Resources.h"
#include "Transform.h"
#include "Camera.h"
#include "CameraMoveScript.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "CombineFilter.h"
#include "Engine.h"
#include "MeshData.h"
#include "RigidBody.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "SceneChangeEvent.h"
#include "EventManager.h"
#include "Collider.h"
#include "EventManager.h"
#include "PaperBurnScript.h"
#include "Factory.h"
#include "Player.h"
#include "PrefabManager.h"

namespace hm
{
	TestScene::TestScene()
		: Scene(SceneType::Test)
	{
	}
	TestScene::~TestScene()
	{
	}
	void TestScene::Initialize()
	{
		Scene::Initialize();
	}
	void TestScene::Update()
	{
		Scene::Update();

		if (IS_DOWN(KeyType::P))
		{
			GET_SINGLE(EventManager)->PushSceneChangeEvent(SceneType::Title);
		}
	}
	void TestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TestScene::FinalUpdate()
	{
		Scene::FinalUpdate();
	}
	void TestScene::Render()
	{
		Scene::Render();
	}
	void TestScene::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);

		// Create Camera
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"MainCamera");
			Transform* pTransform = pGameObject->AddComponent(new Transform);

			Camera* pCamera = pGameObject->AddComponent(new Camera);
			//pCamera->SetCullingMask(LayerType::Unknown, true);
			pGameObject->AddComponent(new CameraMoveScript);

			pTransform->SetPosition(Vec3(0.f, 0.f, 0.f));
			AddGameObject(pGameObject);
		}

		// Create DirLight
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->SetDontDestroyObject(L"DirLight");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(-10.f, 10.f, 0.f));
			pTransform->SetScale(Vec3(10.f, 10.f, 10.f));
			Light* pLight = pGameObject->AddComponent(new Light);
			pLight->SetDiffuse(Vec3(0.5f, 0.5f, 0.5f));
			pLight->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
			pLight->SetSpecular(Vec3(1.f, 1.f, 1.f));
			pLight->SetLightRange(100.f);
			pLight->SetLightDirection(Vec3(1.f, -1.f, 1.f));
			pLight->SetLightType(LightType::DirectionalLight);
			AddGameObject(pGameObject);
		}

		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(50.f, 50.f, 1.f);

			GameObject* pGameObject = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, -10.f, 0.f), physicsInfo, L"Forward", L"", LayerType::Ground);
			
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Grid", L"..\\Resources\\Texture\\blender_uv_grid_2k.png");
			pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
			
			pGameObject->GetTransform()->SetScale(Vec3(50.f, 50.f, 1.f));
			pGameObject->GetTransform()->SetRotation(AXIS_X, 90.f);
			AddGameObject(pGameObject);
		}

		// Forward Object
		//{
		//	GameObject* pGameObject = Factory::CreateObject<GameObject>(Vec3(-5.f, 0.f, 10.f), L"PaperBurn", L"", LayerType::Unknown);
		//	pGameObject->AddComponent(new PaperBurnScript);
		//	pGameObject->GetTransform()->SetRotation(Vec3(0.f, 45.f, 0.f));

		//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Test", L"..\\Resources\\Texture\\goodjob.png");
		//	shared_ptr<Texture> pNoiseTex = GET_SINGLE(Resources)->Load<Texture>(L"BurnNoise", L"..\\Resources\\Texture\\BurnNoise.png");
		//	// Texture2D t0

		//	// SetTexture( 레지스터 번호, 텍스쳐 );
		//	// 0 : 알베도
		//	// 1 : 노멀
		//	// 2 : 스페큘러
		//	// 3 : 이미시브
		//	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		//	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(1, pNoiseTex);

		//	AddGameObject(pGameObject);
		//}

		// Deferred Dynamic Box
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Box;
		//	physicsInfo.size = Vec3(1.f, 2.f, 1.f);

		//	GameObject* pGameObject = Factory::CreateObjectHasPhysical<GameObject>(Vec3(5.f, 10.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Desk.fbx", LayerType::Unknown);
		//	pGameObject->SetFrustumCheckFlag(true);
		//	pGameObject->SetDontDestroyObject(L"Box_1");
		//	pGameObject->GetTransform()->SetScale(Vec3(1.f, 2.f, 1.f));

		//	AddGameObject(pGameObject);
		//}

		// Deferred Static Box
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Static;
		//	physicsInfo.eGeometryType = GeometryType::Box;
		//	physicsInfo.size = Vec3(2.f, 1.f, 1.f);

		//	GameObject* pGameObject = Factory::CreateObjectHasPhysical<GameObject>(Vec3(-5.f, 10.f, 0.f), physicsInfo, L"Deferred", L"", LayerType::Player);
		//	pGameObject->SetFrustumCheckFlag(true);
		//	pGameObject->SetDontDestroyObject(L"Box_2");

		//	pGameObject->GetTransform()->SetScale(Vec3(2.f, 1.f, 1.f));
		//	pGameObject->GetTransform()->SetRotation(Vec3(45.f, 45.f, 45.f));

		//	AddGameObject(pGameObject);
		//}

		// Create Dynamic FBX Object
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Dynamic;
			info.size = Vec3(10.f, 3.f, 1.f);

			GameObject* pGameObject = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Desk.fbx", LayerType::Player);
			pGameObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pGameObject->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, -45.f, 0.f));
			pGameObject->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, -1.f));
			
			AddGameObject(pGameObject);
		}

		// Create Static FBX Object
		for (int i = 0; i < 2; ++i)
		{
			// 항아리1
			GameObject* pGameObject = Factory::CreateObject<GameObject>(Vec3(i * 10.f, 0.f, 0.f), L"MonsterDeferred", L"..\\Resources\\FBX\\Mage.fbx", LayerType::Unknown);
			shared_ptr<Texture> pCrackTex = GET_SINGLE(Resources)->Load<Texture>(L"EnemyCrack", L"..\\Resources\\Texture\\cracks_generic.png");
			pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(2, pCrackTex);

			pGameObject->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
			
			AddGameObject(pGameObject);
		}


		// Create Player
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Dynamic;
			info.size = Vec3(10.f, 3.f, 1.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Desk.fbx");
			pPlayer->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, -45.f, 0.f));
			pPlayer->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, -1.f));

			pPlayer->SetItem(new GameObject(LayerType::Unknown));
			pPlayer->SetState(5);

			AddGameObject(pPlayer);
			GET_SINGLE(PrefabManager)->AddPrefab(L"Test2", pPlayer);
		}

		// Prefab Player
		{
			Player* pPlayer = GET_SINGLE(PrefabManager)->GetPrefab<Player>(L"Test2");
			pPlayer->GetTransform()->SetPosition(Vec3(10.f, 0.f, 0.f));

			AddGameObject(pPlayer);
		}
	}
	void TestScene::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
	}
}