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

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

/* Script */
#include "PlayerMoveScript.h"

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

		//¹è°æ¸Ê ÇÏ¾á»öÀ¸·Î ¸¸µé¾îÁÖ´Â ÄÚµå
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

		// 1, 2Ãþ º®
		{
			DecoObject* pFirstFloorWall = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\Main.fbx");

			pFirstFloorWall->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pFirstFloorWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			AddGameObject(pFirstFloorWall);
		}
		// 1Ãþ ¹Ù´Ú
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.f, 0.1f, 5.f);

			Ground* pFirstFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.14f, -1.3f, -2.87f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\HallColliderCheckMap\\MainRoom Floor Lower.fbx");
			
			pFirstFloor->GetTransform()->SetScale(Vec3(5.1f, 5.f, 5.1f));
			AddGameObject(pFirstFloor);
		}
	}

	void HallColliderCheckMap::Exit()
	{
	}
}