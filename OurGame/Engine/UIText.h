#pragma once
#include "Component.h"
namespace hm
{
	class UIText :
		public Component
	{
	public:
		UIText();
		virtual ~UIText();
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void Initialize() override;
		virtual void Render() override;

	private:
	};
}


