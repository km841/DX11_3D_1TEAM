#pragma once
#include "GameObject.h"

namespace jh
{
	class BreakablePotCell : public GameObject
	{
	public:
		BreakablePotCell();
		virtual ~BreakablePotCell();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

	public:
		void SetOriginPos(Vec3 _pos) { mOriginPos = _pos; }
		bool IsOriginPos() { return this->GetTransform()->GetPosition() == mOriginPos; }

	private:
		Vec3 mOriginPos;
	};
}
