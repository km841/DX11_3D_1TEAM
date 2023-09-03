#pragma once
#include "Map.h"
namespace hm
{
	class GrandmaBossMap :
		public Map
	{
	public:
		GrandmaBossMap();
		virtual ~GrandmaBossMap();

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


