#include "pch.h"
#include "SceneManager.h"
#include "Engine.h"
#include "Camera.h"

namespace hm
{
	SceneManager::SceneManager()
	{
	}

	SceneManager::~SceneManager()
	{
		for (int i = 0; i < SCENE_TYPE_COUNT; ++i)
		{
			SAFE_DELETE(mScenes[i]);
		}
	}

	void SceneManager::Initialize()
	{
	}
	void SceneManager::Update()
	{
		mpActiveScene->Update();
	}
	void SceneManager::FixedUpdate()
	{
		mpActiveScene->FixedUpdate();
	}
	void SceneManager::FinalUpdate()
	{
		mpActiveScene->FinalUpdate();
	}
	void SceneManager::Render()
	{
		mpActiveScene->Render();
	}
	void SceneManager::Destroy()
	{
		for (size_t i = 0; i < mScenes.size(); ++i)
		{
			if (nullptr != mScenes[i])
				mScenes[i]->Destroy();

			SAFE_DELETE(mScenes[i]);
		}
	}
	Scene* SceneManager::GetScene(SceneType _eSceneType)
	{
		AssertEx(mScenes[static_cast<int>(_eSceneType)], L"SceneManager::GetScene() - 생성되지 않은 씬을 가져오려는 시도");
		return mScenes[static_cast<int>(_eSceneType)];
	}
	void SceneManager::AddScene(Scene* _pScene)
	{
		SceneType eSceneType = _pScene->GetSceneType();
		AssertEx(SceneType::End != eSceneType, L"SceneManager::AddScene() - 잘못된 SceneType");
		mScenes[static_cast<int>(eSceneType)] = _pScene;
	}
	void SceneManager::AddMap(Scene* _pMap)
	{
		SceneType eSceneType = _pMap->GetSceneType();
		AssertEx(SceneType::End != eSceneType, L"SceneManager::AddMap() - 잘못된 SceneType");
		mScenes[static_cast<int>(eSceneType)] = _pMap;
	}
	void SceneManager::ActiveAndInitializeScene(SceneType _eSceneType)
	{
		mpActiveScene = GetScene(_eSceneType);
		mpActiveScene->Enter();
		mpActiveScene->Initialize();
	}
	Vec3 SceneManager::ScreenToWorldPosition(const Vec3& _screenCoord, Camera* _pCamera)
	{
		Vec2 Resolution = RESOLUTION;
		int width = static_cast<int>(Resolution.x);
		int height = static_cast<int>(Resolution.y);

		Matrix matProjection = _pCamera->GetProjectionMatrix();

		float viewX = (+2.f * _screenCoord.x / width - 1) / matProjection(0, 0);
		float viewY = (-2.f * _screenCoord.y / height + 1) / matProjection(1, 1);

		Matrix matViewInv = _pCamera->GetViewMatrix().Invert();

		Vec3 worldPos = Vec3(viewX, viewY, _screenCoord.z);
		worldPos = XMVector3TransformCoord(worldPos, matViewInv);

		return worldPos;
	}

	Vec3 SceneManager::WorldToScreenPosition(const Vec3& _worldCoord, Camera* _pCamera)
	{
		Vec2 Resolution = RESOLUTION;
		int width = static_cast<int>(Resolution.x);
		int height = static_cast<int>(Resolution.y);

		Matrix matView = _pCamera->GetViewMatrix();
		Matrix matProjection = _pCamera->GetProjectionMatrix();
		Matrix matFinal = matView * matProjection;

		Vec3 screenPos = XMVector3TransformCoord(_worldCoord, matFinal);

		screenPos.x = width * ((screenPos.x + 1) / 2.f);
		screenPos.y = height * ((screenPos.y + 1) / 2.f);

		screenPos.x -= width / 2.f;
		screenPos.y -= height / 2.f;

		return screenPos;
	}

	void SceneManager::ChangeScene(SceneType _eSceneType)
	{
		std::vector<GameObject*> mGameObjects = mpActiveScene->TransportDontDestroyObjects();

		if (nullptr != mpActiveScene)
			mpActiveScene->Exit();

		mpActiveScene->RemovePhysicsActors();
		ActiveAndInitializeScene(_eSceneType);

		mpActiveScene->PushGameObjects(mGameObjects);
		mpActiveScene->Start();
	}
}