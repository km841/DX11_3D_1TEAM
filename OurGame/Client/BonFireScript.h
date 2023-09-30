#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class BonFireScript :
		public MonoBehavior
	{
	public:
		BonFireScript();
		virtual ~BonFireScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void FixedUpdate() override;
		void PushData();

	private:
		float mAccTime;
	};
}


