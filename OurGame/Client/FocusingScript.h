#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class GameObject;
	class FocusingScript :
		public MonoBehavior
	{
	public:
		FocusingScript();
		virtual ~FocusingScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

		void SetFocusingTarget(GameObject* _pTarget);

	public:
		virtual void FixedUpdate() override;

	private:
		GameObject* mpTarget;
		float mFollowSpeed;

		float mPrevLength;
		Vec3 mPrevLookDir;

		bool mbFocusMode;
	};

}

