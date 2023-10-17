#pragma once
#include "Map.h"

namespace hm
{
	class EndingScene :
		public Map
	{
	public:
		EndingScene();
		virtual ~EndingScene();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void Enter();
		virtual void Exit();
	};
}


