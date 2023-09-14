#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class OwnerFollowScript :
		public MonoBehavior
	{
	public:
		OwnerFollowScript(GameObject* _pOwner);
		~OwnerFollowScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

		void SetOffset(const Vec3& _offset) { mOffset = _offset; }

	private:
		GameObject* mpOwner;
		Vec3 mOffset;
	};

}

