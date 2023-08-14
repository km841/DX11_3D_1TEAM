#include "pch.h"
#include "PrefabManager.h"
#include "GameObject.h"
#include "Factory.h"
#include "Ground.h"

namespace hm
{
	PrefabManager::PrefabManager()
	{
	}

	PrefabManager::~PrefabManager()
	{
	}

	void PrefabManager::Initialize()
	{
		CreateDefaultPrefab();
	}

	void PrefabManager::ClearPrefab()
	{
		for (int i = 0; i < mPrefabMap.size(); ++i)
		{
			PrefabMap& prefabMap = mPrefabMap[i];

			for (auto& pair : prefabMap)
			{
				SAFE_DELETE(pair.second);
			}
		}

	}
	void PrefabManager::CreateDefaultPrefab()
	{	
		// 현모 - GrayRockType1
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\GrayRockType1.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"GrayRockType1", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - GrayRockType2
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\GrayRockType2.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"GrayRockType2", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - GrayRockType3
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\GrayRockType3.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"GrayRockType3", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType1
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\BlackRockType1.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType1", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType2
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\BlackRockType2.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType2", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType3
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\BlackRockType3.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType3", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType4
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\BlackRockType4.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType4", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - Bannister
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Static;
			info.size = Vec3(13.f, 1.f, 3.f);

			WallObject* pWallObject = Factory::CreateObjectHasPhysical<WallObject>(Vec3(0.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\Prefab\\Bannister.fbx");

			pWallObject->GetMeshRenderer()->GetMaterial()->SetInt(3, 1, 14, 0);
			pWallObject->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));
			pWallObject->GetTransform()->SetRotation(Vec3(0.f, -90.f, -90.f));
			AddPrefab<WallObject>(L"Bannister", pWallObject);
			SAFE_DELETE(pWallObject);
		}
	}
}
