#include "pch.h"
#include "CorridorRightMap.h"
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

CorridorRightMap::CorridorRightMap()
	: Map(MapType::CorridorRightMap)
{
}

CorridorRightMap::~CorridorRightMap()
{
}

void CorridorRightMap::Initialize()
{
	Map::Initialize();
}

void CorridorRightMap::Update()
{
	Map::Update();
}

void CorridorRightMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void CorridorRightMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void CorridorRightMap::Render()
{
	Map::Render();
}

void CorridorRightMap::Enter()
{
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);

	//¹è°æ¸Ê ÇÏ¾á»öÀ¸·Î ¸¸µé¾îÁÖ´Â ÄÚµå
	gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

#pragma region º®
	// º®
	{
		DecoObject* pWall = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor.fbx");

		pWall->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
		pWall->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

		pWall->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
		pWall->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));

		AddGameObject(pWall);
	}
#pragma endregion

#pragma region ¹Ù´Ú
	// ¹Ù´Ú
	{
		DecoObject* pFloor = Factory::CreateObject<DecoObject>(Vec3(0.f, -7.1f, -2.19f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\CorridorRightMap\\Corridor-detach.fbx");

		pFloor->GetTransform()->SetScale(Vec3(45.7f, 1.f, 45.6f));
		pFloor->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));

		//pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
		//pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(148.f, 147.f, 150.f));

		SetGizmoTarget(pFloor);
		AddGameObject(pFloor);
	}
#pragma endregion
}

void CorridorRightMap::Exit()
{
}
