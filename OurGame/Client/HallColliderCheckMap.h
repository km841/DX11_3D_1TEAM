#pragma once
#include "Map.h"

namespace jh
{
	class HallColliderCheckMap :
		public Map
	{
	public:
		HallColliderCheckMap();
		virtual ~HallColliderCheckMap();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	private:
		void LightDirSet();
		void InitObjectAdd();
		void InitColliderAdd();
		void FuncObjectAdd();
		

	private:
		int mSpawnPoint = -1;
	};
}
