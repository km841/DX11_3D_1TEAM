#include "pch.h"
#include "Tool.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Resources.h"
#include "GameObject.h"

namespace hm
{
	Tool::Tool()
		: mHwnd(0)
		, mpGameObject(nullptr)
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

		UpdateGui();

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

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1600, 900);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(0, 0);
		style.FramePadding = ImVec2(0, 0);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	}

	void Tool::UpdateGui()
	{
		Vec2 Resolution = gpEngine->GetResolution();
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(Resolution.x, Resolution.y));
		if (ImGui::Begin("Gizmo", nullptr,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar))
		{
			ImVec2 panelSize = ImGui::GetWindowSize();
			shared_ptr<Texture> pSwapChainTarget = GET_SINGLE(Resources)->Get<Texture>(L"SwapChainTarget_0");
			if (nullptr != pSwapChainTarget)
				ImGui::Image(pSwapChainTarget->GetSRV().Get(), panelSize);

			if (nullptr != mpGameObject)
				EditTransform();
		}
		ImGui::End();
	}

	void Tool::EditTransform()
	{
		bool useWindow = true;
		int gizmoCount = 1;
		float camDistance = 8.f;
		static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
		static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
		static bool useSnap = false;
		static float snap[3] = { 0.1f, 0.1f, 0.1f };
		static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
		static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
		static bool boundSizing = false;
		static bool boundSizingSnap = false;

		if (ImGui::IsKeyPressed(ImGuiKey_3))
			mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
		if (ImGui::IsKeyPressed(ImGuiKey_2))
			mCurrentGizmoOperation = ImGuizmo::ROTATE;
		if (ImGui::IsKeyPressed(ImGuiKey_1))
			mCurrentGizmoOperation = ImGuizmo::SCALE;
		
		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();

		Matrix viewMat = pActiveScene->GetMainCamera()->GetViewMatrix();
		Matrix projMat = pActiveScene->GetMainCamera()->GetProjectionMatrix();
		Matrix worldMat = mpGameObject->GetTransform()->GetWorldMatrix();

		ImGuiIO& io = ImGui::GetIO();
		float viewManipulateRight = io.DisplaySize.x;
		float viewManipulateTop = 0;
		static ImGuiWindowFlags gizmoWindowFlags = 0;
		if (useWindow)
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor(0.35f, 0.3f, 0.3f));
			ImGui::Begin("Gizmo", 0, gizmoWindowFlags);
			ImGuizmo::SetDrawlist();
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
			viewManipulateRight = ImGui::GetWindowPos().x + windowWidth;
			viewManipulateTop = ImGui::GetWindowPos().y;
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			gizmoWindowFlags = ImGui::IsWindowHovered() && ImGui::IsMouseHoveringRect(window->InnerRect.Min, window->InnerRect.Max) ? ImGuiWindowFlags_NoMove : 0;
		}
		else
		{
			ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
		}

		ImGuizmo::Manipulate(&viewMat._11, &projMat._11, mCurrentGizmoOperation, mCurrentGizmoMode, &worldMat._11, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
		mpGameObject->GetTransform()->SetWorldMatrix(worldMat);

		ImGuizmo::ViewManipulate(&viewMat._11, camDistance, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);

		if (useWindow)
		{
			ImGui::End();
			ImGui::PopStyleColor(1);
		}
	}

	void Tool::SetGameObject(GameObject* _pGameObject)
	{
		AssertEx(nullptr != _pGameObject, L"Tool::SetGameObject() - GameObject is nullptr!");
		mpGameObject = _pGameObject;
	}

	LRESULT Tool::DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
	}
}