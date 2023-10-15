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
	private:
		void InitObjectAdd();
		void InitBusStart();

	private:
		Bus* pBus;
		Elevator* eTarget;

		int mSpawnPoint = -1;
		int mBusActive = -1;

		int mIntroAcive = -1;
		int mWorkerAcive = -1;
		int mDirectorActive = -1;

		bool mbIsBusCutSceneOver = false;
	};
}