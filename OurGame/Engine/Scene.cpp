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
#include "Input.h"
#include "Transform.h"

namespace hm
{
	std::vector<wstring> Scene::mDontDestroyObjectNames;
	std::map<wstring, std::function<void()>> Scene::mSceneChangeCallbackMap;
	
	Scene::Scene(SceneType _eSceneType)
		: meSceneType(_eSceneType)
		, mpMainCamera(nullptr)
		, mpUICamera(nullptr)
		, mpCutSceneCamera(nullptr)
		, mpDirLight(nullptr)
		, mbIsBakedStaticShadow(false)
		, mbEnableDirLight(true)
		, mBakedStaticShadowCount(0)
		, mbIsInit(false)
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
		if (false == mbIsInit)
		{
			mbIsInit = true;
			for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
			{
				for (GameObject* pGameObject : mGameObjects[i])
				{
					AssertEx(pGameObject, L"This gameobject is nullptr");
					pGameObject->Initialize();
				}
			}
		}
	}
	void Scene::Update()
	{
		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			for (int j = 0; j < mGameObjects[i].size(); ++j)
			{
				AssertEx(mGameObjects[i][j], L"This gameobject is nullptr");
				mGameObjects[i][j]->Update();
			}
		}

		if (IS_DOWN(KeyType::N_7))
		{
			bool bIsDebugMode = GET_SINGLE(RenderManager)->IsDebugMode();
			GET_SINGLE(RenderManager)->SetDebugMode(!bIsDebugMode);
		}

		if (IS_DOWN(KeyType::N_8))
		{
			bool bIsApplyPostProcessing = GET_SINGLE(RenderManager)->IsApplyPostProcessing();
			GET_SINGLE(RenderManager)->SetPostProcessing(!bIsApplyPostProcessing);
		}

		if (IS_DOWN(KeyType::N_9))
		{
			bool bIsApplyHDR = GET_SINGLE(RenderManager)->IsApplyHDR();
			GET_SINGLE(RenderManager)->SetHDR(!bIsApplyHDR);
		}

		if (IS_DOWN(KeyType::N_0))
		{
			bool bIsApplyRimLighting = GET_SINGLE(RenderManager)->IsApplyRimLighting();
			GET_SINGLE(RenderManager)->SetRimLighting(!bIsApplyRimLighting);
		}

		//const Vec3& pos = mpMainCamera->GetTransform()->GetPosition();
		//wstring strPos = L"카메라 위치 : " + std::to_wstring(pos.x) + L", " + std::to_wstring(pos.y) + L", " + std::to_wstring(pos.z);
		//FONT->DrawString(strPos, 30.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff0000ff, FONT_ALIGN::LEFT);

		//const Vec3& rot = mpMainCamera->GetTransform()->GetRotation();
		//wstring strRot = L"카메라 회전 : " + std::to_wstring(rot.x) + L", " + std::to_wstring(rot.y) + L", " + std::to_wstring(rot.z);
		//FONT->DrawString(strRot, 30.f, Vec3(50.f, 810.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff0000ff, FONT_ALIGN::LEFT);

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

		
		if (GET_SINGLE(RenderManager)->IsDebugMode())
		{
			for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
			{
				for (GameObject* pGameObject : mGameObjects[i])
				{
					AssertEx(pGameObject, L"This gameobject is nullptr");
					pGameObject->Render();
				}
			}
		}


		FONT->Render();
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
			if (_pGameObject->GetName() == L"MainCamera")
				mpMainCamera = _pGameObject;
			if (_pGameObject->GetName() == L"UICamera")
				mpUICamera = _pGameObject;
			if (_pGameObject->GetName() == L"CutSceneCamera")
				mpCutSceneCamera = _pGameObject;

			mCameraObjects.push_back(_pGameObject);
		}

		if (nullptr != _pGameObject->GetLight())
		{
			if (_pGameObject->GetName() == L"DirLight")
				mpDirLight = _pGameObject;
			mLightObjects.push_back(_pGameObject);
		}

		if (nullptr != _pGameObject->GetMirror())
		{
			mMirrorObjects.push_back(_pGameObject);
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
				if (pGameObject->GetName() == L"MainCamera")
					mpMainCamera = pGameObject;
				if (pGameObject->GetName() == L"UICamera")
					mpUICamera = pGameObject;
				if (pGameObject->GetName() == L"CutSceneCamera")
					mpCutSceneCamera = pGameObject;

				mCameraObjects.push_back(pGameObject);
			}

			if (nullptr != pGameObject->GetLight())
			{
				if (pGameObject->GetName() == L"DirLight")
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
	void Scene::AddSceneChangeCallback(const wstring& _name, std::function<void()> _function)
	{
		AssertEx(nullptr != _function, L"Scene::AddSceneChangeCallback() - 콜백이 nullptr임");

		auto iter = mSceneChangeCallbackMap.find(_name);
		auto endIter = mSceneChangeCallbackMap.end();
		AssertEx(iter == endIter, L"Scene::AddSceneChangeCallback() - 이미 등록된 콜백 이름");

		mSceneChangeCallbackMap.insert(std::make_pair(_name, _function));
	}

	void Scene::RemoveSceneChangeCallback(const wstring& _name)
	{
		auto iter = mSceneChangeCallbackMap.find(_name);
		auto endIter = mSceneChangeCallbackMap.end();
		if (iter == endIter)
			mSceneChangeCallbackMap.erase(iter);
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
		AssertEx(mpMainCamera, L"Scene::GetMainCamera() : Main CameraObject is nullptr");
		return mpMainCamera->GetCamera();
	}
	Camera* Scene::GetCutSceneCamera()
	{
		AssertEx(mpCutSceneCamera, L"Scene::GetCutSceneCamera() : CutScene CameraObject is nullptr");
		return mpCutSceneCamera->GetCamera();
	}
	Camera* Scene::GetUICamera()
	{
		AssertEx(mpUICamera, L"Scene::GetMainCamera() : UI CameraObject is nullptr");
		return mpUICamera->GetCamera();
	}
	Light* Scene::GetDirLight()
	{
		AssertEx(mpDirLight, L"GetDirLight() : Dir LightObject is nullptr");
		return mpDirLight->GetLight();
	}
	void Scene::SetDirLightPosition(const Vec3& _position)
	{
		AssertEx(mpDirLight, L"Scene::SetDirLightPosition() : DirLight is nullptr");
		mpDirLight->GetTransform()->SetPosition(_position);
	}

	void Scene::SetDirLightRotation(const Vec3& _rotation)
	{
		AssertEx(mpDirLight, L"Scene::SetDirLightRotation() : DirLight is nullptr");
		mpDirLight->GetTransform()->SetRotation(_rotation);
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

			if (_pGameObject == mpCutSceneCamera)
				mpCutSceneCamera = nullptr;
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