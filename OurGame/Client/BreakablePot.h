#pragma once
#include "GameObject.h"
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

	public:
		void BreakPots();
		void RestorePots();

	private:
		void CreateCells();

	private:
		GameObject* mpBasePot;
		std::vector<BreakablePotCell*> mpPotCells;
	};
}