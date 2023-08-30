#pragma once
#include "Map.h"
namespace yj
{
	class RightMap :
		public Map
	{
	public:
		RightMap();
		virtual ~RightMap();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

		GameObject* Target;

	};

}