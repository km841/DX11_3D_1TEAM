#pragma once

#include "GameObject.h"

namespace yj
{
	class FireLamp : public GameObject
	{
	public:
		FireLamp(GameObject* _UpperPart, GameObject* _BelowPart);
		virtual ~FireLamp();
		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	public:
		void Active();

	private:
		GameObject* pUpperPart;
		GameObject* pBelowPart;

		float mFlowLimit = 0.5f;
		float mCurrFlowDist = 0.0f;
		float mFlowSpeed = 1.0f;

		float mTurnSpeed = 180.0f;

		int mLampSequence = -1;
	};
}