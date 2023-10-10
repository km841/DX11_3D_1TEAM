#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class InterfaceAlphaScript :
		public MonoBehavior
	{
	public:
		InterfaceAlphaScript();
		~InterfaceAlphaScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

		void SetColor(const Vec3& _color) { mColor = _color; }
		void SetAlpha(float _alpha) { mAlpha = _alpha; }
		float GetAlpha() { return mAlpha; }

	private:
		float mAlpha;
		Vec3 mColor;
	};
}


