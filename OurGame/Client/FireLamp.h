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

		virtual void OnCollisionEnter(Collider* pOtherCollider);
		virtual void OnCollisionStay(Collider* pOtherCollider) ;
		virtual void OnCollisionExit(Collider* pOtherCollider) ;

		virtual void OnTriggerEnter(Collider* pOtherCollider);
		virtual void OnTriggerStay(Collider* pOtherCollider) ;
		virtual void OnTriggerExit(Collider* pOtherCollider) ;

	public:
		void Active();
		bool GetIsBurn() { return isBurn; }
	private:
		GameObject* pUpperPart;
		GameObject* pBelowPart;
		GameObject* pColObj;
		float mFlowLimit = 0.5f;
		float mCurrFlowDist = 0.0f;
		float mFlowSpeed = 1.0f;

		float mTurnSpeed = 180.0f;

		int mLampSequence = -1;

		bool isBurn;
	};
}