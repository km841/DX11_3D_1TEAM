#include "pch.h"
#include "UI.h"

namespace hm
{
	UI::UI()
		: GameObject(LayerType::Interface)
	{
	}

	UI::~UI()
	{
	}

	void UI::Initialize()
	{
		GameObject::Initialize();
	}

	void UI::Update()
	{
		GameObject::Update();
	}

	void UI::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void UI::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void UI::Render()
	{
		GameObject::Render();
	}

	void UI::Destroy()
	{
		GameObject::Destroy();
	}

}

