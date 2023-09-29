#pragma once
#include "Scene.h"

namespace hm
{
	class SceneManager
	{
	public:
		DECLARE_SINGLE(SceneManager);

	public:
		void Initialize();
		void Update();
		void FixedUpdate();
		void FinalUpdate();
		void Render();
		void Destroy();

		Scene* GetActiveScene() { return mpActiveScene; }
		Scene* GetScene(SceneType _eSceneType);
		void AddScene(Scene* _pScene);
		void AddMap(Scene* _pMap);
		void ActiveAndInitializeScene(SceneType _eSceneType);
		Vec3 ScreenToWorldPosition(const Vec3& _screenCoord, Camera* _pCamera);
		Vec3 WorldToScreenPosition(const Vec3& _worldCoord, Camera* _pCamera);

	private:
		/* 씬을 바꾼다 (*이 함수는 이벤트로 처리해야하므로 직접 호출 금지)
		* 씬을 바꾸는 작업은 해당 프레임에서 처리해야 할 일을 모두 처리한 후에 이루어져야 함
		*/
		friend class EventManager;
		void ChangeScene(SceneType _eSceneType);

	private:
		std::array<Scene*, SCENE_TYPE_COUNT> mScenes = {};
		Scene* mpActiveScene = nullptr;
	};
}




