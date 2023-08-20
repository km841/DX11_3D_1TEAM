#pragma once
#include "MonoBehavior.h"
namespace hm
{
	class TestAnimationScript :
		public MonoBehavior
	{
	public:
		TestAnimationScript();
		virtual ~TestAnimationScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void FixedUpdate() override;
	};

}

