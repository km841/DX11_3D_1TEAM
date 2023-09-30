#pragma once
#include "Component.h"

namespace hm
{
	class MonoBehavior :
		public Component
	{
	public:
		MonoBehavior();
		virtual ~MonoBehavior();

		virtual Component* Clone(class GameObject* _pGameObject) = 0;
		virtual void PushData() { }

	private:

	};
}


