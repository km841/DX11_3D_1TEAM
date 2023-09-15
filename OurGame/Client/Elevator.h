#pragma once

#include "GameObject.h"
#include "DecoObject.h"

namespace yj
{

	class Elevator : public GameObject
	{
	public:

		Elevator();
		virtual ~Elevator();
		Elevator* Clone()
		{
			Elevator* pElevator = GameObject::Clone<Elevator>();
			return pElevator;
		}

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

	public:

		enum State
		{
			StandbyDown,
			StandbyUp,
			Move,
			ArriveUp,
			ArriveDown,
		};
		State state;
		bool CheckState(State _state) {
			if (state != _state) { return false; }
			else { return true; }
		}

		DecoObject* GetpMoveFrame() { return pMoveFrame; }
			public:

		int direction;
		//Down = 0;
		//Up = 1;
		//else Error;




	private:

		DecoObject* pUpperBarricade;
		DecoObject* pBelowBarricade;

		DecoObject* pUpperChecker;
		DecoObject* pBelowChecker;

		DecoObject* pMoveFrame;

		DecoObject* pElevatorCol;

		GameObject* pRill_01;
		GameObject* pRill_02;

		GameObject* pWeight;

		float frameInitSpeed = 0.0f;
		float frameCurrSpeed = 2.0f;
		float frameMaxSpeed;
		float frameAddSpeed;

		float belowLimit = -3.7f;
		float upLimit = 4.6f;

		void ElevatorMove();

		bool isPlayerIn = false;


		void CheckPlayerStayFront();

		void BarricadeOn(int num);
		void BarricadeOff(int num);
	};
}