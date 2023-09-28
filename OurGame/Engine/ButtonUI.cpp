#include "pch.h"
#include "ButtonUI.h"
#include "Input.h"
#include "InterfaceManager.h"

namespace hm
{
	ButtonUI::ButtonUI(const string& _name, int _importance, const Vec2& _pos, const Vec2& _scale)
		: Interface(InterfaceInfo(InterfaceType::UI, _name, _importance))
	{
		mPos = _pos;
		mScale = _scale;
	}

	ButtonUI::~ButtonUI()
	{
	}

	void ButtonUI::Initialize()
	{
		Interface::Initialize();
	}

	void ButtonUI::Update()
	{
		if (mColor.Length() > 0.f)
			ImGui::PushStyleColor(ImGuiCol_Button, mColor);


		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_ButtonHovered] = mHoveredColor; // RGBA 값으로 설정
		style.Colors[ImGuiCol_ButtonActive] = mClickedColor; // RGBA 값으로 설정

		ImGui::SetCursorPos(mPos);
		InterfaceFont font("..\\Resources\\Font\\msgothic.ttc", 66);
		if (ImGui::Button(mInfo.name.c_str(), mScale))
		{
			ChildUpdate();

			if (nullptr != mCallback)
				mCallback();
		}

		if (mColor.Length() > 0.f)
			ImGui::PopStyleColor();
	}

	void ButtonUI::FixedUpdate()
	{
		Interface::FixedUpdate();
	}

	void ButtonUI::Render()
	{
		Interface::Render();
	}

	void ButtonUI::Destroy()
	{
		Interface::Destroy();
	}
}

