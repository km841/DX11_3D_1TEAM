#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RigidBody.h"
#include "Collider.h"
#include "MeshRenderer.h"

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
		KinematicOverlapCheck();
	}

	void CollisionManager::SetCollisionGroup(LayerType _eLayerType_1, LayerType _eLayerType_2)
	{
		if (_eLayerType_1 < _eLayerType_2)
			std::swap(_eLayerType_1, _eLayerType_2);

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

	void CollisionManager::ClearAllCollisionForObject(GameObject* _pGameObject)
	{
		auto iterBegin = mColMap.begin();
		auto iterEnd = mColMap.end();

		UINT32 id = _pGameObject->GetID();
		
		for ( ; iterBegin != iterEnd; iterBegin++)
		{
			UINT32 first = static_cast<UINT32>(iterBegin->first);
			UINT32 second = (iterBegin->first >> 32);
			if (id == first || id == second)
			{
				if (true == iterBegin->second)
				{
					iterBegin->second = false;
				}
			}
		}
	}

	void CollisionManager::KinematicOverlapCheck()
	{
		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			std::vector<GameObject*> gameObjects = pActiveScene->GetGameObjects(static_cast<LayerType>(i));
			std::bitset<LAYER_TYPE_COUNT>& flags = mArrColGroup[i];

			for (int j = 0; j < LAYER_TYPE_COUNT; ++j)
			{
				if (false == flags[j])
					continue;

				std::vector<GameObject*> others = pActiveScene->GetGameObjects(static_cast<LayerType>(j));

				for (int k = 0; k < others.size(); ++k)
				{
					if (false == others[k]->IsPhysicsObject())
						continue;

					if (ActorType::Kinematic != others[k]->GetRigidBody()->GetActorType())
						continue;

					if (false == others[k]->IsEnable())
						continue;

					for (int l = 0; l < gameObjects.size(); ++l)
					{
						if (false == gameObjects[l]->IsPhysicsObject())
							continue;

						if (ActorType::Kinematic != gameObjects[l]->GetRigidBody()->GetActorType())
							continue;

						if (false == gameObjects[l]->IsEnable())
							continue;

						ColID id = {};
						id.first = gameObjects[l]->GetID();
						id.second = others[k]->GetID();

						auto iter = mColMap.find(id.id);
						if (iter == mColMap.end())
						{
							mColMap[id.id] = false;
						}

						bool bResult = others[k]->GetCollider()->Overlap(gameObjects[l]->GetCollider());
						if (true == bResult)
						{
							if (false == mColMap[id.id])
							{
								others[k]->GetCollider()->OnTriggerEnter(gameObjects[l]->GetCollider());
								gameObjects[l]->GetCollider()->OnTriggerEnter(others[k]->GetCollider());

							}
							else
							{
								others[k]->GetCollider()->OnTriggerStay(gameObjects[l]->GetCollider());
								gameObjects[l]->GetCollider()->OnTriggerStay(others[k]->GetCollider());
							}
							mColMap[id.id] = true;
						}
						else
						{
							if (true == mColMap[id.id])
							{
								others[k]->GetCollider()->OnTriggerExit(gameObjects[l]->GetCollider());
								gameObjects[l]->GetCollider()->OnTriggerExit(others[k]->GetCollider());
							}
							mColMap[id.id] = false;
						}
					}


				}

			}
		}
	}

}
