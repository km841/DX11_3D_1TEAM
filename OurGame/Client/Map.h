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
		void SetCameraHolder(CameraHolder* _pHolder);
		CameraHolder* GetCameraHolder() { return spHolder; }

	protected:
		GameObject* mTarget = nullptr;
		static CameraHolder* spHolder;
		bool mbShadow;
	};
}




