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

		void SetCollapsePos(Vec3 _pos) { mCollapsePos = _pos; }
		const Vec3 GetCollapsePos() { return mCollapsePos; }
		void SetCollapseRot(Vec3 _rot) { mCollapseRot = _rot; }
		const Vec3 GetCollapseRot() { return mCollapseRot; }

		bool IsOriginPos() { return this->GetTransform()->GetPosition() == mOriginPos; }

		void CalculateForce(const Vec3 _hitPos);

	private:
		Vec3 mRelativePos;
		Vec3 mOriginPos;
		Vec3 mCollapsePos;
		Vec3 mCollapseRot;
	};
}
