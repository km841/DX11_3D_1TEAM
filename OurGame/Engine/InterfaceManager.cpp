#include "pch.h"
#include "InterfaceManager.h"
#include "Engine.h"

namespace hm
{
	InterfaceManager::InterfaceManager()
	{

	}

	InterfaceManager::~InterfaceManager()
	{
		for (auto pInterface : mInterfaceMap)
		{
			pInterface.second->Destroy();
			SAFE_DELETE(pInterface.second);
		}
	}

	void InterfaceManager::Initialize()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = gpEngine->GetResolution();

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(0, 0);
		style.FramePadding = ImVec2(0, 0);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

		for (int i = 1; i < 100; ++i)
		{
			if (30 == i)
				io.FontDefault = LoadFont("..\\Resources\\Font\\msgothic.ttc", i);
			else
				LoadFont("..\\Resources\\Font\\msgothic.ttc", i);
		}
	}

	void InterfaceManager::Update()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		Vec2 Resolution = gpEngine->GetResolution();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(Resolution.x, Resolution.y));

		for (auto& pInterface : mInterfaceMap)
		{
			pInterface.second->Update();
		}

	}
	void InterfaceManager::Render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	void InterfaceManager::AddInterface(Interface* _interface)
	{
		InterfaceInfo& info = _interface->GetInterfaceInfo();
		auto pair = mInterfaceMap.insert(std::make_pair(info, _interface));
		AssertEx(pair.second, L"InterfaceManager::AddInterface() - 이미 해당 Importance가 존재함");
	}
	Interface* InterfaceManager::GetInterface(const string& _name)
	{
		for (auto& pInterface : mInterfaceMap)
		{
			if (_name == pInterface.second->GetName())
				return pInterface.second;

			Interface* pFind = pInterface.second->GetChild(_name);
			if (nullptr != pFind)
				return pFind;
		}

		return nullptr;
	}
	ImFont* InterfaceManager::LoadFont(const string& _fontPath, int _fontSize)
	{
		static int count = 0;

		ImGuiIO& io = ImGui::GetIO();
		ImFont* pFont = nullptr;

		if (mFontMap.end() != mFontMap.find(_fontPath))
		{
			std::map<FontSize, FontIndex>& idxMap = mFontMap[_fontPath];
			if (idxMap.end() == idxMap.find(_fontSize))
			{
				pFont = io.Fonts->AddFontFromFileTTF(_fontPath.c_str(), static_cast<float>(_fontSize));
				idxMap[_fontSize] = count++;
			}
		}

		else
		{
			pFont = io.Fonts->AddFontFromFileTTF(_fontPath.c_str(), static_cast<float>(_fontSize));
			std::map<FontSize, FontIndex>& idxMap = mFontMap[_fontPath];
			idxMap[_fontSize] = count++;
		}

		return pFont;
	}
	void InterfaceManager::SetFont(const string& _fontPath, int _fontSize)
	{
		ImGuiIO& io = ImGui::GetIO();
		std::map<FontSize, FontIndex>& idxMap = mFontMap[_fontPath];
		int idx = idxMap[_fontSize];
		ImGui::PushFont(io.Fonts->Fonts[idx]);
	}
}