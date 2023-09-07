#pragma once
#include "Map.h"

namespace hm
{
	class Monster_Player_TestScene :
		public Map
	{
	public:
		Monster_Player_TestScene();
		virtual ~Monster_Player_TestScene();

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