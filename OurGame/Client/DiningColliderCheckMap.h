#pragma once
#include "Map.h"
namespace sy
{
	class DiningColliderCheckMap :
		public Map
	{
	public:
		DiningColliderCheckMap();
		virtual ~DiningColliderCheckMap();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

	public:
		void TestCallback() { MessageBoxA(NULL, "Start Callback", "Caption", MB_OK); }

		virtual void Enter();
		virtual void Exit();
	};
}

