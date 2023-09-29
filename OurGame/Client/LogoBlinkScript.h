#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class LogoBlinkScript :
		public MonoBehavior
	{
	public:
		LogoBlinkScript();
		~LogoBlinkScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

	private:
		float mRatio;
		int mSign;
	};
}


