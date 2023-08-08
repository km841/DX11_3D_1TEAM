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

		//int a = 0

		// Create Camera
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Unknown);
		//	pGameObject->AddComponent(new Transform);
		//	pGameObject->AddComponent(new Camera);
		//	pGameObject->GetCamera()->SetProjectionType(ProjectionType::Orthographic);

		//	pGameObject->GetTransform()->SetPosition(Vec3(0.f, 0.f, 0.f));

		//	AddGameObject(pGameObject);
		//}

		// Ground
		{
			GameObject* pGameObject = new GameObject(LayerType::Ground);
			pGameObject->AddComponent(new PaperBurnScript);
			pGameObject->SetFrustumCheckFlag(false);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(0.f, -10.f, 0.f));
			pTransform->SetScale(Vec3(50.f, 50.f, 1.f));

			MeshRenderer* pMeshRenderer = new MeshRenderer;

			shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Grid", L"..\\Resources\\Texture\\blender_uv_grid_2k.png");

			pMaterial->SetTexture(0, pTexture);
			pMeshRenderer->SetMaterial(pMaterial);
			
			pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadCubeMesh());
			pGameObject->AddComponent(pMeshRenderer);

			RigidBody* pRigidBody = pGameObject->AddComponent(new RigidBody);

			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(50.f, 50.f, 1.f);

			pRigidBody->SetPhysical(physicsInfo);

			pTransform->SetRotation(AXIS_X, 90.f);
			Vec3 rot = pTransform->GetRotation();

			pGameObject->AddComponent(new Collider);
			AddGameObject(pGameObject);
		}

		// Forward Object
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			pGameObject->AddComponent(new PaperBurnScript);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(-5.f, 0.f, 10.f));
			pTransform->SetRotation(Vec3(0.f, 45.f, 0.f));
			pTransform->SetScale(Vec3(1.f, 1.f, 1.f));

			MeshRenderer* pMeshRenderer = new MeshRenderer;

			shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward");
			shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"Test", L"..\\Resources\\Texture\\goodjob.png");
			pMaterial->SetTexture(0, pTexture);

			pMeshRenderer->SetMaterial(pMaterial);
			pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadCubeMesh());
			pGameObject->AddComponent(pMeshRenderer);

			AddGameObject(pGameObject);
		}

		// Particle Object
		{
			//GameObject* pGameObject = new GameObject(LayerType::Unknown);
			//Transform* pTransform = pGameObject->AddComponent(new Transform);
			//pTransform->SetPosition(Vec3(0.f, -5.f, 0.f));
			//pTransform->SetScale(Vec3(1.f, 1.f, 1.f));
			//pGameObject->AddComponent<ParticleSystem>();

			//AddGameObject(pGameObject);
		}

		//// Compute Shader Test
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Monster);
		//	Transform* pTransform = pGameObject->AddComponent(new Transform);
		//	pTransform->SetPosition(Vec3(2.5f, 0.f, 0.f));
		//	
		//	pTransform->SetScale(Vec3(1.f, 1.f, 1.f));

		//	MeshRenderer* pMeshRenderer = new MeshRenderer;

		//	shared_ptr<Material> pComputeMaterial = GET_SINGLE(Resources)->Get<Material>(L"Compute");
		//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->CreateTexture(
		//		L"ComputeTest", DXGI_FORMAT_R8G8B8A8_UNORM,
		//		D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE,
		//		500, 500);

		//	pComputeMaterial->SetTexture(0, pTexture);
		//	pComputeMaterial->Dispatch(1, 1024, 1);

		//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		//	pMaterial->SetTexture(0, pTexture);
		//	pMeshRenderer->SetMaterial(pMaterial);
		//	pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadCubeMesh());
		//	pGameObject->AddComponent(pMeshRenderer);

		//	RigidBody* pRigidBody = pGameObject->AddComponent(new RigidBody);

		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Sphere;
		//	//physicsInfo.eGeometryType = GeometryType::Sphere;

		//	pRigidBody->SetPhysical(physicsInfo);
		//	pGameObject->AddComponent(new Collider);
		//	AddGameObject(pGameObject);
		//}

		//// Position Object
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Unknown);
		//	pGameObject->AddComponent(new Transform);
		//	pGameObject->GetTransform()->SetPosition(Vec3(0.f, 0.f, 10.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(7.f, 5.f, 5.f));

		//	MeshRenderer* pMeshRenderer = new MeshRenderer;

		//	shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Forward")->Clone();
		//	shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Get<Texture>(L"NormalTarget");

		//	pMaterial->SetTexture(0, pTexture);
		//	pMeshRenderer->SetMaterial(pMaterial);
		//	pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		//	pGameObject->AddComponent(pMeshRenderer);

		//	AddGameObject(pGameObject);
		//}

		// Deferred Object
		{
			GameObject* pGameObject = new GameObject(LayerType::Player);
			pGameObject->SetFrustumCheckFlag(true);
			pGameObject->SetDontDestroyObject(L"Box_1");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(5.f, 10.f, 0.f));
			pTransform->SetScale(Vec3(1.f, 2.f, 1.f));

			MeshRenderer* pMeshRenderer = new MeshRenderer;

			shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred");
			pMeshRenderer->SetMaterial(pMaterial);
			pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadCubeMesh());
			pGameObject->AddComponent(pMeshRenderer);

			RigidBody* pRigidBody = pGameObject->AddComponent(new RigidBody);

			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.f, 2.f, 1.f);

			pRigidBody->SetPhysical(physicsInfo);
			pGameObject->AddComponent(new Collider);
			AddGameObject(pGameObject);
		}

		// Deferred Object
		{
			GameObject* pGameObject = new GameObject(LayerType::Player);
			pGameObject->SetFrustumCheckFlag(true);
			pGameObject->SetDontDestroyObject(L"Box_2");
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(-5.f, 10.f, 0.f));

			pTransform->SetScale(Vec3(2.f, 1.f, 1.f));

			MeshRenderer* pMeshRenderer = new MeshRenderer;

			shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(L"Deferred");

			pMeshRenderer->SetMaterial(pMaterial);
			pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadCubeMesh());
			pGameObject->AddComponent(pMeshRenderer);

			RigidBody* pRigidBody = pGameObject->AddComponent(new RigidBody);
			pRigidBody->SetVelocity(AXIS_X, 1.f);

			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 1.f, 1.f);

			pRigidBody->SetPhysical(physicsInfo);

			pTransform->SetRotation(Vec3(45.f, 45.f, 45.f));
			//pTransform->AddRotation(AXIS_Z, 45.f);
			pGameObject->AddComponent(new Collider);
			AddGameObject(pGameObject);
		}

		// Create DirLight
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Unknown);
		//	pGameObject->SetDontDestroyObject(L"DirLight");
		//	Transform* pTransform = pGameObject->AddComponent(new Transform);
		//	pTransform->SetPosition(Vec3(-10.f, 10.f, 0.f));
		//	pTransform->SetScale(Vec3(10.f, 10.f, 10.f));
		//	Light* pLight = pGameObject->AddComponent(new Light);
		//	pLight->SetDiffuse(Vec3(0.5f, 0.5f, 0.5f));
		//	pLight->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		//	pLight->SetSpecular(Vec3(1.f, 1.f, 1.f));
		//	pLight->SetLightRange(100.f);
		//	pLight->SetLightDirection(Vec3(1.f, -1.f, 1.f));
		//	pLight->SetLightType(LightType::DirectionalLight);
		//	AddGameObject(pGameObject);
		//}

		//// Create Light
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Unknown);
		//	pGameObject->AddComponent(new Transform);
		//	pGameObject->GetTransform()->SetPosition(Vec3(0.f, 500.f, 0.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
		//	Light* pLight = pGameObject->AddComponent(new Light);
		//	pLight->SetDiffuse(Vec3(0.f, 1.f, 0.f));
		//	pLight->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		//	pLight->SetSpecular(Vec3(1.f, 1.f, 1.f));
		//	pLight->SetLightRange(200.f);
		//	pLight->SetLightDirection(Vec3(1.f, -1.f, 1.f));
		//	pLight->SetLightType(LightType::PointLight);
		//	AddGameObject(pGameObject);
		//}

		//// Create Light
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Unknown);
		//	pGameObject->AddComponent(new Transform);
		//	pGameObject->GetTransform()->SetPosition(Vec3(0.f, 200.f, 70.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
		//	Light* pLight = pGameObject->AddComponent(new Light);
		//	pLight->SetDiffuse(Vec3(0.f, 0.f, 1.f));
		//	pLight->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		//	pLight->SetSpecular(Vec3(1.f, 1.f, 1.f));
		//	pLight->SetLightRange(100.f);
		//	pLight->SetLightDirection(Vec3(1.f, -1.f, 1.f));
		//	pLight->SetLightType(LightType::PointLight);
		//	AddGameObject(pGameObject);
		//}

		//// Create Light
		//{
		//	GameObject* pGameObject = new GameObject(LayerType::Unknown);
		//	pGameObject->AddComponent(new Transform);
		//	pGameObject->GetTransform()->SetPosition(Vec3(0.f, 100.f, -100.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		//	pGameObject->AddComponent(new Light);
		//	pGameObject->GetLight()->SetDiffuse(Vec3(1.f, 0.f, 0.f));
		//	pGameObject->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		//	pGameObject->GetLight()->SetSpecular(Vec3(1.f, 1.f, 1.f));
		//	pGameObject->GetLight()->SetLightRange(150.f);
		//	pGameObject->GetLight()->SetLightDirection(Vec3(-1.f, 0.f, 0.f));
		//	pGameObject->GetLight()->SetLightType(LightType::PointLight);
		//	AddGameObject(pGameObject);
		//}

		// FBX
		//for (int i  = 0; i < 3; ++i)
		//{
		//	shared_ptr<MeshData> pMeshData = GET_SINGLE(Resources)->LoadFBX(L"..\\Resources\\FBX\\Mage.fbx");
		//	GameObject* pGameObject = pMeshData->Instantiate();
		//	pGameObject->AddComponent(new PaperBurnScript);

		//	shared_ptr<Texture> pNoiseTex = GET_SINGLE(Resources)->Load<Texture>(L"BurnNoise", L"..\\Resources\\Texture\\BurnNoise.png");
		//	pGameObject->GetMeshRenderer()->GetMaterial()->SetTexture(1, pNoiseTex);

		//	pGameObject->SetName(L"Mage");
		//	pGameObject->GetTransform()->SetPosition(Vec3(i * 10.f, 0.f, 10.f));
		//	pGameObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		//	AddGameObject(pGameObject);
		//}

		// Desk
		//for (int i = 0; i < 2; ++i)
		//{
		//	shared_ptr<MeshData> pMeshData = GET_SINGLE(Resources)->LoadFBX(L"..\\Resources\\FBX\\Desk.fbx");
		//	GameObject* pGameObject = pMeshData->Instantiate();
		//	pGameObject->SetName(L"Desk");
		//	pGameObject->SetFrustumCheckFlag(false);
		//	pGameObject->GetTransform()->SetPosition(Vec3(i * 10.f, 0.f, 0.f));
		//	pGameObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
		//	AddGameObject(pGameObject);
		//}

		// Map
		//{
		//	shared_ptr<MeshData> pMeshData = GET_SINGLE(Resources)->LoadFBX(L"..\\Resources\\FBX\\R_Right2.fbx");
		//	GameObject* pGameObject = pMeshData->Instantiate();
		//	pGameObject->SetName(L"R_Right2");
		//	pGameObject->SetFrustumCheckFlag(false);
		//	pGameObject->GetTransform()->SetPosition(Vec3(0.f, 0.f, 0.f));
		//	pGameObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		//	pGameObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
		//	AddGameObject(pGameObject);
		//}
	}
	void TestScene::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
	}
}