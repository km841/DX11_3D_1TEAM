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
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrayRockType1.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"GrayRockType1", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - GrayRockType2
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrayRockType2.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"GrayRockType2", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - GrayRockType3
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrayRockType3.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"GrayRockType3", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType1
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\BlackRockType1.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType1", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType2
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\BlackRockType2.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType2", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType3
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\BlackRockType3.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType3", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}

		// 현모 - BlackRockType4
		{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\BlackRockType4.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			AddPrefab<DecoObject>(L"BlackRockType4", pDecoObject);
			SAFE_DELETE(pDecoObject);
		}
	}
}
