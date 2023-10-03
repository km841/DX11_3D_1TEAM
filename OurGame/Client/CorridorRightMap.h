#pragma once
#include "Map.h"

namespace jh
{
	class CorridorRightMap :
		public Map
	{
	public:
		CorridorRightMap();
		virtual ~CorridorRightMap();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	public:

		void InitObjectAdd();
		void InitColliderAdd();
		void FuncObjectAdd();


	private:
		GameObject* pSpikeDoor;
		GameObject* pSpikeDoorCol;

	};

}
