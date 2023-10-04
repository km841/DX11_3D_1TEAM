#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
	class MonsterHitScript :
		public MonoBehavior
	{
	public:
		MonsterHitScript();
		~MonsterHitScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

		void HitBegin();

	private:
		TimerObject mTimer;

	};
}


