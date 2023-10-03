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
		void SetRelativePos(Vec3 _pos) { mRelativePos = _pos; }
		const Vec3 GetRelativePos() { return mRelativePos; }
		void SetOriginPos(Vec3 _pos) { mOriginPos = _pos; }
		const Vec3 GetOriginPos() { return mOriginPos; }
		bool IsOriginPos() { return this->GetTransform()->GetPosition() == mOriginPos; }

	private:
		Vec3 mRelativePos;
		Vec3 mOriginPos;
	};
}
