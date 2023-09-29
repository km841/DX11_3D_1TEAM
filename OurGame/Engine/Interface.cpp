#include "pch.h"
#include "Interface.h"
#include "Engine.h"
#include "Timer.h"

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

