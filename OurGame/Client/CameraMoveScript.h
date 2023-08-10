#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class CameraMoveScript :
		public MonoBehavior
	{
	public:
		CameraMoveScript();
		~CameraMoveScript() = default;
		virtual void FixedUpdate() override;

		virtual Component* Clone(class GameObject* _pGameObject);

	private:
		float mSpeed;
	};
}


