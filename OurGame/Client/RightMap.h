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
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

		GameObject* Target;

	private:
		void InitObjectAdd();
		void InitColliderAdd();
		void FuncObjectAdd();
	private:
		GameObject* pSpikeDoor;
		GameObject* pSpikeDoorCol;
		int mSpawnPoint = -1;
	};
}