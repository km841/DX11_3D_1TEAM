#pragma once
#include "Scene.h"
namespace hm
{
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

	protected:
		GameObject* mTarget = nullptr;
		bool mbShadow;
	};
}




