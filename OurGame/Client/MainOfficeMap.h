#pragma once
#include "Map.h"
namespace yj {
	class MainOfficeMap :
		public Map
	{
	public:
		MainOfficeMap();
		virtual ~MainOfficeMap();

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

