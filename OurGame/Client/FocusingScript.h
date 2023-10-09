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

		void SetFollowTarget(GameObject* _pTarget);
		void SetFocusingTarget(GameObject* _pTarget);

		void SetFollowingMode(bool _bFlag) { mbFollowMode = _bFlag; }
		void SetFocusingMode(bool _bFlag) { mbFocusMode = _bFlag; }

	public:
		virtual void FixedUpdate() override;

	private:
		GameObject* mpFollowTarget;
		GameObject* mpFocusingTarget;

		float mFollowSpeed;

		bool mbFollowMode;
		bool mbFocusMode;
	};

}

