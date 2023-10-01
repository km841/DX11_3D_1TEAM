#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class MonsterCrackScript :
		public MonoBehavior
	{
	public:
		MonsterCrackScript();
		~MonsterCrackScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

	private:

	};
}


