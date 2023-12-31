#pragma once
#include "GameObject.h"
namespace hm
{
	class ImageFilter;
	class GameObject;
	class Scene
	{
	public:
		friend class RenderManager;
		Scene(SceneType _eSceneType);
		virtual ~Scene();

	public:
		virtual void Initialize();
		virtual void Start() {}
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void Enter() abstract;
		virtual void Exit()  abstract;

	public:
		/* 범용적으로 게임 오브젝트를 씬에 추가하는 함수 
		- DontDestroyObject가 중복으로 씬에 추가되지 않도록 내부적으로 처리합니다.
		*/
		void AddGameObject(GameObject* _pGameObject);
		
		/*
		** 특수한 목적 외엔 사용 금지 **
		* TransfortGameObject에서 DontDestroy 오브젝트들을 다음 씬에 밀어넣기 위한 함수
		- 일반적으로는 AddGameObject를 사용하여 
		- 동일한 DontDestroy 오브젝트가 중복으로 생성되지 않게 해야 합니다. 
		*/
		void PushGameObjects(const std::vector<GameObject*>& _gameObjects);

		/* 씬에서 게임오브젝트를 제거하는 함수*/
		void RemoveGameObject(GameObject* _pGameObject);

		/* 씬에서 게임 오브젝트를 제거한 후 삭제하는 함수 */
		void DeleteGameObject(GameObject* _pGameObject);

		/* 레이어 단위로 게임 오브젝트들을 씬에서 제거하는 함수 */
		void RemoveGameObjects(std::vector<GameObject*>& _gameObjects);
		void RemoveGameObjects(LayerType _eLayerType);

		/* 레이어 단위로 게임 오브젝트들을 삭제하는 함수 */
		void DeleteGameObjects(std::vector<GameObject*>& _gameObjects);
		void DeleteGameObjects(LayerType _eLayerType);

		static void AddSceneChangeCallback(const wstring& _name, std::function<void()> _function);
		static void RemoveSceneChangeCallback(const wstring& _name);
		static const std::map<wstring, std::function<void()>>& GetSceneChangeCallbackMap() { return mSceneChangeCallbackMap; }

		/*
		* 레이어에 속한 게임오브젝트들을 반환하는 함수
		- 게임오브젝트의 값을 변경할 필요가 없는 경우
		- 보통의 경우 이 함수를 사용하는 것을 권장
		*/
		const std::vector<GameObject*>& GetGameObjects(LayerType _eLayerType) const;

		/* 레이어에 속한 게임오브젝트들의 참조를 반환하는 함수
		- 반환값에 수정을 가하면 원본이 수정되므로 주의 필요
		*/
		std::vector<GameObject*>& GetGameObjectsRef(LayerType _eLayerType);

		/* 씬이 변경될 때 SceneManager에서 이 함수를 호출하여 DontDestroy 오브젝트들을 다음 씬으로 옮겨주는 함수 */
		std::vector<GameObject*> TransportDontDestroyObjects();

		/* 씬에 있는 Physics Actor들을 씬에서 모두 제거해주는 함수 */
		void RemovePhysicsActors();
		void AddPhysicsActors();

		Camera* GetMainCamera();
		Camera* GetCutSceneCamera();
		Camera* GetUICamera();
		Light* GetDirLight();

		SceneType GetSceneType() { return meSceneType; }
		void DisableDirLight() { mbEnableDirLight = false; }
		void EnableDirLight() { mbEnableDirLight = true; }

		bool IsBakedStaticShadow() { return mbIsBakedStaticShadow; }
		void SetDirLightPosition(const Vec3& _position);
		void SetDirLightRotation(const Vec3& _rotation);

		void ChangeCameraMode() { std::swap(mpMainCamera, mpCutSceneCamera); }

	private:
		/* 인자로 넘어온 게임 오브젝트가 가진 카메라를 씬에서 제거해주는 함수 */
		void RemoveCameraInObjectFromScene(GameObject* _pGameObject);

		/* 인자로 넘어온 게임 오브젝트가 가진 빛을 씬에서 제거해주는 함수 */
		void RemoveLightInObjectFromScene(GameObject* _pGameObject);

	protected:
		SceneType	meSceneType;
		std::array<std::vector<GameObject*>, LAYER_TYPE_COUNT> mGameObjects;

		GameObject* mpMainCamera;
		GameObject* mpUICamera;
		GameObject* mpCutSceneCamera;
		GameObject* mpDirLight;

		std::vector<GameObject*> mCameraObjects;
		std::vector<GameObject*> mLightObjects;
		std::vector<GameObject*> mMirrorObjects;


		bool mbIsBakedStaticShadow;
		bool mbEnableDirLight;

		int mBakedStaticShadowCount;

		bool mbIsInit;

	protected:
		static std::vector<wstring> mDontDestroyObjectNames;
		static std::map<wstring, std::function<void()>> mSceneChangeCallbackMap;
	};
}


