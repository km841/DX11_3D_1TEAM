#include "pch.h"
#include "Interface.h"
#include "Engine.h"

namespace hm
{
	Interface::Interface(const InterfaceInfo& _info)
		: mInfo(_info)
		, mbEnable(true)
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
	}
	void Interface::Update()
	{
		ImGui::SetNextWindowPos(mPos);
		ImGui::SetNextWindowSize(mScale);

		if (ImGui::Begin((mInfo.name + "Framework").c_str(), nullptr,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ChildUpdate();
		}
		ImGui::End();
	}
	void Interface::FixedUpdate()
	{
	}
	void Interface::Render()
	{
	}
	void Interface::Destroy()
	{
	}
	void Interface::AddChild(Interface* _pChild)
	{
		int importance = _pChild->GetInterfaceInfo().importance;
		
		auto pair = mChildren.insert(std::make_pair(importance, _pChild));
		AssertEx(pair.second, L"Interface::AddChild() - 중복되는 Importance가 존재");
	}
	Interface* Interface::GetChild(const string& _name)
	{
		for (auto& pChild : mChildren)
		{
			if (_name == pChild.second->GetName())
				return pChild.second;
		}

		return nullptr;
	}
	void Interface::ChildUpdate()
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

