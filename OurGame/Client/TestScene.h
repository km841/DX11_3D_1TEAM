#pragma once
#include "Scene.h"

namespace hm
{
	class TestScene :
		public Scene
	{
	public:
		TestScene();
		virtual ~TestScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	};
}


