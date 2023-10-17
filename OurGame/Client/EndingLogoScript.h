#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
	class EndingLogoScript :
		public MonoBehavior
	{
	public:
		EndingLogoScript();
		~EndingLogoScript() = default;
		virtual void FixedUpdate() override;

		virtual Component* Clone(class GameObject* _pGameObject);

	private:
		TimerObject mWaitTimer;
		TimerObject mTimer;
		TimerObject mTopMovingBeginTimer;
		TimerObject mTopMovingTimer;
		bool mbIsSoundBegin;

	};
}


