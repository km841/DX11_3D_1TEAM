#pragma once
#include "GameObject.h"
#include "TimerObject.h"
#include "BreakablePotCell.h"

namespace jh
{
	class BreakablePot : public GameObject
	{
	public:
		BreakablePot(GameObject* _pBase, std::vector<BreakablePotCell*> _vpCells);
		virtual ~BreakablePot();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnTriggerEnter(Collider* _pOther);
		virtual void OnTriggerStay(Collider* _pOther);
		virtual void OnTriggerExit(Collider* _pOther);

	public:
		void BreakPots();
		void RestorePots();

	private:
		GameObject* mpBasePot;
		std::vector<BreakablePotCell*> mpPotCells;

		bool mbIsRestroing;
		TimerObject mTimer;

		bool mbIsWaiting;
		float mWaitTime;
	};
}
