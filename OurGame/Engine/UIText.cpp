#include "pch.h"
#include "UIText.h"
#include "GameObject.h"

namespace hm
{
	UIText::UIText()
		: Component(ComponentType::UI)
	{
	}
	UIText::~UIText()
	{
	}
	Component* UIText::Clone(GameObject* _pGameObject)
	{
		UIText* pUIText = _pGameObject->AddComponent(new UIText);
		return pUIText;
	}
	void UIText::Initialize()
	{
	}
	void UIText::Render()
	{
	}
}

