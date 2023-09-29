#include "pch.h"
#include "Interface.h"
#include "Engine.h"
#include "Timer.h"
#include "UIText.h"

namespace hm
{
	Interface::Interface()
		: GameObject(LayerType::Interface)
	{
	}

	Interface::~Interface()
	{
		for (auto& pChild : mChildren)
		{
			SAFE_DELETE(pChild.second);
		}
		mChildren.clear();
	}

	void Interface::Initialize()
	{
		GameObject::Initialize();
	}
	void Interface::Update()
	{
		GameObject::Update();
	}
	void Interface::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Interface::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}
	void Interface::Render()
	{
		GameObject::Render();
	}
	void Interface::Destroy()
	{
		GameObject::Destroy();
	}

	Interface* Interface::GetChild(const wstring& _name)
	{
		for (auto& pChild : mChildren)
		{
			if (_name == pChild.second->GetName())
				return pChild.second;
		}

		return nullptr;
	}
	void Interface::UpdateChild()
	{
		for (auto& pChild : mChildren)
		{
			if (false == pChild.second->IsEnable())
				continue;

			pChild.second->Update();
		}
	}

	void Interface::SetText(const wstring& _text, float _size, bool _bIsShadow)
	{
		UIText* pUIText = GetUIText();
		if (nullptr == pUIText)
		{
			pUIText = AddComponent(new UIText);
		}

		pUIText->SetText(_text);
		pUIText->SetSize(_size);
		pUIText->Shadow(_bIsShadow);

		// Default Option
		{
			pUIText->SetRenderArea(0.f, 0.f, RESOLUTION.x, RESOLUTION.y * 2.f);
			pUIText->SetAlignH(TextAlignH::Center);
			pUIText->SetAlignV(TextAlignV::Mid);
			pUIText->SetShadowOffset(Vec3(1.5f, -1.5f, 0.f));
			pUIText->SetShadowColor(0.f, 0.f, 0.f, 1.f);
		}
	}

	void Interface::SetTextColor(const Vec4& _color)
	{
		UIText* pUIText = GetUIText();
		if (nullptr == pUIText)
		{
			pUIText = AddComponent(new UIText);
		}

		pUIText->SetColor(_color);
	}

	void Interface::AddChild(Interface* _pChild)
	{
	}
	void Interface::Enable()
	{	
		mbEnable = true;
		for (auto& pChild : mChildren)
		{
			pChild.second->Enable();
		}
	}
	void Interface::Disable()
	{
		for (auto& pChild : mChildren)
		{
			pChild.second->Disable();
		}
		mbEnable = false;
	}
}

