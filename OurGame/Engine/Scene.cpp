#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Engine.h"
#include "Camera.h"
#include "Material.h"
#include "Resources.h"
#include "Light.h"
#include "ImageFilter.h"
#include "CombineFilter.h"
#include "BlurFilter.h"
#include "RigidBody.h"
#include "RenderManager.h"
#include "Collider.h"

namespace hm
{
	std::vector<wstring> Scene::mDontDestroyObjectNames;
	
	Scene::Scene(SceneType _eSceneType)
		: meSceneType(_eSceneType)
		, mpMainCamera(nullptr)
		, mpUICamera(nullptr)
		, mpDirLight(nullptr)
	{
	}
	Scene::~Scene()
	{
		for (std::vector<GameObject*>& layerGroup : mGameObjects)
		{
			for (size_t i = 0; i < layerGroup.size(); ++i)
			{
				SAFE_DELETE(layerGroup[i]);
			}
			layerGroup.clear();
		}
	}
	void Scene::Initialize()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (GameObject* pGameObject : mGameObjects[i])
			{
				AssertEx(pGameObject, L"This gameobject is nullptr");
				pGameObject->Initialize();
			}
		}
	}
	void Scene::Update()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (GameObject* pGameObject : mGameObjects[i])
			{
				AssertEx(pGameObject, L"This gameobject is nullptr");
				pGameObject->Update();
			}
		}
	}
	void Scene::FixedUpdate()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (GameObject* pGameObject : mGameObjects[i])
			{
				AssertEx(pGameObject, L"This gameobject is nullptr");
				pGameObject->FixedUpdate();
			}
		}
	}
	void Scene::FinalUpdate()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (GameObject* pGameObject : mGameObjects[i])
			{
				AssertEx(pGameObject, L"This gameobject is nullptr");
				pGameObject->FinalUpdate();
			}
		}
	}
	void Scene::Render()
	{
		GET_SINGLE(RenderManager)->ClearRenderTargets();
		GET_SINGLE(RenderManager)->Render(this);

		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (GameObject* pGameObject : mGameObjects[i])
			{
				AssertEx(pGameObject, L"This gameobject is nullptr");
				pGameObject->Render();
			}
		}
	}
	void Scene::Destroy()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (auto& pGameObject : mGameObjects[i])
			{
				AssertEx(pGameObject, L"This gameobject is nullptr");
				pGameObject->Destroy();
			}
		}
	}

	void Scene::AddGameObject(GameObject* _pGameObject)
	{
		AssertEx(_pGameObject, L"GameObject is nullptr");

		if (true == _pGameObject->IsDontDestroy())
		{
			auto findIter = std::find(mDontDestroyObjectNames.begin(), mDontDestroyObjectNames.end(), _pGameObject->GetName());
			if (findIter == mDontDestroyObjectNames.end())
			{
				mDontDestroyObjectNames.push_back(_pGameObject->GetName());
			}
			else
			{
				_pGameObject->Destroy();
				SAFE_DELETE(_pGameObject);
				return;
			}
		}

		LayerType eLayerType = _pGameObject->GetLayerType();
		mGameObjects[static_cast<int>(eLayerType)].push_back(_pGameObject);

		if (nullptr != _pGameObject->GetCamera())
		{
			if (mCameraObjects.empty())
				mpMainCamera = _pGameObject;
			mCameraObjects.push_back(_pGameObject);
		}

		if (nullptr != _pGameObject->GetLight())
		{
			if (mLightObjects.empty())
				mpDirLight = _pGameObject;
			mLightObjects.push_back(_pGameObject);
		}
	}
	void Scene::PushGameObjects(const std::vector<GameObject*>& _gameObjects)
	{
		for (GameObject* pGameObject : _gameObjects)
		{
			LayerType eLayerType = pGameObject->GetLayerType();
			mGameObjects[static_cast<int>(eLayerType)].push_back(pGameObject);

			if (nullptr != pGameObject->GetCamera())
			{
				if (mCameraObjects.empty())
					mpMainCamera = pGameObject;
				mCameraObjects.push_back(pGameObject);
			}

			if (nullptr != pGameObject->GetLight())
			{
				if (mLightObjects.empty())
					mpDirLight = pGameObject;
				mLightObjects.push_back(pGameObject);
			}
		}
	}
	void Scene::RemoveGameObject(GameObject* _pGameObject)
	{
		RemoveCameraInObjectFromScene(_pGameObject);
		RemoveLightInObjectFromScene(_pGameObject);

		std::vector<GameObject*>& gameObjects = mGameObjects[static_cast<int>(_pGameObject->GetLayerType())];
		auto pFindIt = std::find(gameObjects.begin(), gameObjects.end(), _pGameObject);
		if (pFindIt != gameObjects.end())
		{
			if (_pGameObject->IsPhysicsObject())
			{
				gpEngine->GetPhysics()->RemoveActor(_pGameObject);
				_pGameObject->GetRigidBody()->SetActorInSceneFlag(false);
			}
			gameObjects.erase(pFindIt);
		}
	}
	void Scene::DeleteGameObject(GameObject* _pGameObject)
	{
		RemoveGameObject(_pGameObject);
		_pGameObject->Destroy();

		auto findIter = std::find(mDontDestroyObjectNames.begin(), mDontDestroyObjectNames.end(), _pGameObject->GetName());
		if (findIter != mDontDestroyObjectNames.end())
		{
			mDontDestroyObjectNames.erase(findIter);
		}

		SAFE_DELETE(_pGameObject);
	}
	void Scene::RemoveGameObjects(std::vector<GameObject*>& _gameObjects)
	{
		while (false == _gameObjects.empty())
		{
			RemoveGameObject(_gameObjects.front());
		}
	}
	void Scene::RemoveGameObjects(LayerType _eLayerType)
	{
		RemoveGameObjects(GetGameObjectsRef(_eLayerType));
	}
	void Scene::DeleteGameObjects(std::vector<GameObject*>& _gameObjects)
	{
		while (false == _gameObjects.empty())
		{
			DeleteGameObject(_gameObjects.front());
		}
	}
	void Scene::DeleteGameObjects(LayerType _eLayerType)
	{
		DeleteGameObjects(GetGameObjectsRef(_eLayerType));
	}
	const std::vector<GameObject*>& Scene::GetGameObjects(LayerType _eLayerType) const
	{
		return mGameObjects[static_cast<int>(_eLayerType)];
	}
	std::vector<GameObject*>& Scene::GetGameObjectsRef(LayerType _eLayerType)
	{
		return mGameObjects[static_cast<int>(_eLayerType)];
	}
	std::vector<GameObject*> Scene::TransportDontDestroyObjects()
	{
		std::vector<GameObject*> gameObjects;

		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			std::vector<GameObject*>& curLayerObjects = mGameObjects[static_cast<int>(i)];
			std::vector<GameObject*>::iterator iter = curLayerObjects.begin();

			for (; iter != curLayerObjects.end(); )
			{
				if (true == (*iter)->IsDontDestroy())
				{
					RemoveCameraInObjectFromScene(*iter);
					RemoveLightInObjectFromScene(*iter);

					if ((*iter)->IsPhysicsObject())
						(*iter)->GetCollider()->ClearCollisionCount();

					gameObjects.push_back(*iter);
					iter = curLayerObjects.erase(iter);
					continue;
				}
				iter++;
			}
		}

		return gameObjects;
	}
	void Scene::RemovePhysicsActors()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (auto& pGameObject : mGameObjects[i])
			{
				if (pGameObject->IsPhysicsObject())
				{
					gpEngine->GetPhysics()->RemoveActor(pGameObject);
					pGameObject->GetRigidBody()->SetActorInSceneFlag(false);
				}
			}
		}
	}
	Camera* Scene::GetMainCamera()
	{
		AssertEx(mpMainCamera, L"Scene::GetMainCamera : Main CameraObject is nullptr");
		return mpMainCamera->GetCamera();
	}
	Camera* Scene::GetUICamera()
	{
		AssertEx(mpUICamera, L"Scene::GetMainCamera : UI CameraObject is nullptr");
		return mpUICamera->GetCamera();
	}
	void Scene::RemoveCameraInObjectFromScene(GameObject* _pGameObject)
	{
		if (nullptr != _pGameObject->GetCamera())
		{
			auto pFindIt = std::find(mCameraObjects.begin(), mCameraObjects.end(), _pGameObject);
			if (pFindIt != mCameraObjects.end())
				mCameraObjects.erase(pFindIt);

			if (_pGameObject == mpMainCamera)
				mpMainCamera = nullptr;

			if (_pGameObject == mpUICamera)
				mpUICamera = nullptr;
		}
	}
	void Scene::RemoveLightInObjectFromScene(GameObject* _pGameObject)
	{
		if (nullptr != _pGameObject->GetLight())
		{
			auto pFindIt = std::find(mLightObjects.begin(), mLightObjects.end(), _pGameObject);
			if (pFindIt != mLightObjects.end())
				mLightObjects.erase(pFindIt);

			if (_pGameObject == mpDirLight)
				mpDirLight = nullptr;
		}
	}
}