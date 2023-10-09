#pragma once
#include "GameObject.h"
#include "TimerObject.h"
#include "BreakablePotCell.h"

namespace jh
{
	class BreakablePot : public GameObject
	{
	public:
		BreakablePot(GameObject* _pBase);
		virtual ~BreakablePot();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnTriggerEnter(Collider* _pOther);
		virtual void OnTriggerStay(Collider* _pOther);
		virtual void OnTriggerExit(Collider* _pOther);

	public:
		void BreakPots(const Vec3 _hitPos);
		void RestorePots(bool _isTemp);

	private:
		GameObject* mpBasePot;
		std::vector<BreakablePotCell*> mpPotCells;

		bool mbIsRestoringTemp;
		bool mbIsRestoring;
		TimerObject mWaitTimer;
		TimerObject mProgressTimer;
		TimerObject mTempTimer;

		bool mbIsWaiting;
		float mWaitTime;
	};
}
