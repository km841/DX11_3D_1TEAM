#pragma once
#include "Map.h"

namespace hm
{
	class BossMap :
		public Map
	{
	public:
		BossMap();
		virtual ~BossMap();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	};
}


