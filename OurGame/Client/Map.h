#pragma once
#include "Scene.h"
namespace hm
{
	class CameraHolder;
	class Map :
		public Scene
	{
	public:
		Map(MapType _eMapType);
		virtual ~Map();

	public:
		virtual void Initialize();
		virtual void Start() {}
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	public:
		void SetGizmoTarget(GameObject* _pTarget);
		void SetMeshTarget(GameObject* _pTarget);
		void SetPlayerHolder(GameObject* _pHolder);
		void SetCutSceneHolder(GameObject* _pHolder);
		static GameObject* GetPlayerHolder() { return spPlayerHolder; }
		static GameObject* GetCutSceneHolder() { return spCutSceneHolder; }

		//void ChangeCameraMode() { std::swap(mpMainCamera, mpCutSceneCamera); }
		static void SetPlayerHolderPosition(const Vec3& _pos);
		static void SetCutSceneHolderPosition(const Vec3& _pos);


		
	protected:
		GameObject* mTarget = nullptr;
		static GameObject* spPlayerHolder;
		static GameObject* spCutSceneHolder;
		static GameObject* spCutSceneFocusingTarget;
		bool mbShadow;
	};
}




