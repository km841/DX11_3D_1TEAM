#pragma once
#include "Map.h"
#include "Elevator.h"
#include "Bus.h"

namespace yj {
	class MainOfficeMap :
		public Map
	{
	public:
		MainOfficeMap();
		virtual ~MainOfficeMap();

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
		void InitBusStart();

		Bus* pBus;
		Elevator* eTarget;
	};
}

