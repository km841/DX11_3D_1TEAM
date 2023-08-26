#include "pch.h"
#include "Tool.h"
#include "Engine.h"

namespace hm
{
	Tool::Tool()
		: mHwnd(0)
	{

	}

	Tool::~Tool()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void Tool::Initialize(HWND _hwnd, ComPtr<ID3D11Device> _pDevice, ComPtr<ID3D11DeviceContext> _pContext)
	{
		mHwnd = _hwnd;
		mpDevice = _pDevice;
		mpContext = _pContext;

		InitGui();
	}
	void Tool::Update()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if (ImGui::Begin("Mini Tool", nullptr))
		{
			if (ImGui::Button("Open"))
			{

			}
		}
		ImGui::End();
	}
	void Tool::Render()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}


	void Tool::InitGui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(mHwnd);
		ImGui_ImplDX11_Init(mpDevice.Get(), mpContext.Get());
	}

	LRESULT Tool::DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
	}
}