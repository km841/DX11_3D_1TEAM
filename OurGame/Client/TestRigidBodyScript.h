#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class TestRigidBodyScript :
		public MonoBehavior
	{
	public:
		TestRigidBodyScript();
		virtual ~TestRigidBodyScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void FixedUpdate() override;
	};
}
