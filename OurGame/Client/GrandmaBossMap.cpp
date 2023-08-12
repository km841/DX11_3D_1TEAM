#include "pch.h"
#include "GrandmaBossMap.h"
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

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	GrandmaBossMap::GrandmaBossMap()
		: Map(MapType::GrandmaBossMap)
	{
	}

	GrandmaBossMap::~GrandmaBossMap()
	{
	}

	void GrandmaBossMap::Initialize()
	{
		Map::Initialize();
	}

	void GrandmaBossMap::Update()
	{
		Map::Update();
	}

	void GrandmaBossMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void GrandmaBossMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void GrandmaBossMap::Render()
	{
		Map::Render();
	}

	void GrandmaBossMap::Enter()
	{
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));
		// Ground
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(25.f, 1.f, 25.f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -10.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossGround.fbx");
			pGround->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pGround->GetTransform()->SetPositionExcludingColliders(Vec3(-12.f, -18.5f, 0.f));

			AddGameObject(pGround);
		}

		// Table
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(5.f, 0.f, 20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossTable.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(-90.f, 20.f, 0.f));
			AddGameObject(pDecoObject);
		}

		// Start
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, -10.f, -30.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossStart.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(-90.f, 90.f, 0.f));
			AddGameObject(pDecoObject);
		}

		// Wall
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 12; ++x)
			{
				DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossWall1.fbx");
				pDecoObject->GetRigidBody()->RemoveGravity();

				float radian = (225.f + (x * 16.f)) * XM_PI / 180.f;
				float radius = 13.f;

				pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
				pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 50.f + x * 16.f, 0.f));

				pDecoObject->GetTransform()->SetPosition(
					Vec3(radius * cosf(radian) + radius * sinf(radian),
						-20.f + y * 10.f,
						(radius * cosf(radian) - radius * sinf(radian)) + 10.f));
				AddGameObject(pDecoObject);
			}
		}
	}

	void GrandmaBossMap::Exit()
	{
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
	}
}

