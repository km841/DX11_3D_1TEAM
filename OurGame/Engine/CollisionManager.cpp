#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RigidBody.h"

namespace hm
{
	CollisionManager::CollisionManager()
	{
	}

	CollisionManager::~CollisionManager()
	{
	}

	void CollisionManager::Update()
	{
	}

	void CollisionManager::SetCollisionGroup(LayerType _eLayerType_1, LayerType _eLayerType_2)
	{
		mArrColGroup[static_cast<int>(_eLayerType_1)][static_cast<int>(_eLayerType_2)] = true;

		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();

		std::vector<GameObject*> gameObjects_1 = pActiveScene->GetGameObjects(_eLayerType_1);
		for (GameObject* pGameObject : gameObjects_1)
		{
			pGameObject->GetRigidBody()->SetOtherLayerInFilterData(_eLayerType_2);
		}
	}

	std::bitset<LAYER_TYPE_COUNT> CollisionManager::GetCollisionGroup(LayerType _eLayerType)
	{
		return mArrColGroup[static_cast<int>(_eLayerType)];
	}

}
