#pragma once

#include "GameObject.h"
namespace yj
{

	class Elevator : public GameObject
	{
	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();



		void CheckPlayerIn();
		void OrderUp() { isMoveComplete = false; }
		void OrderDown() { isMoveComplete = false; }
		void OrderStop() { frameCurrSpeed = 0.0f; };
		



	private:
		GameObject* pBarricade;
		GameObject* pMoveFrame;
		GameObject* pRill_01;
		GameObject* pRill_02;
		GameObject* pWeight;

		float frameInitSpeed = 0.0f;
		float frameCurrSpeed = 0.0f;
		float frameMaxSpeed;
		float frameAddSpeed;

		bool isMoveComplete = false;

		bool GetIsMoveComplete() { return isMoveComplete; }

		void BarricadeOn() { pBarricade->Enable(); };
		void BarricadeOff() { pBarricade->Disable(); };
	};
}