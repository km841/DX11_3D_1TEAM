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

		void SetAlpha(float _alpha) { mAlpha = _alpha; }
		float GetAlpha() { return mAlpha; }

	private:
		float mAlpha;
	};
}


