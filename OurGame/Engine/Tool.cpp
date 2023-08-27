#include "pch.h"
#include "Tool.h"
#include "Engine.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Camera.h"
#include "Resources.h"
#include "GameObject.h"
#include "Input.h"

namespace hm
{
	Tool::Tool()
		: mHwnd(0)
		, mpGameObject(nullptr)
		, meCurrentOperation(ImGuizmo::ROTATE)
		, meCurrentMode(ImGuizmo::WORLD)
		, mSnaps{0.1f, 0.1f, 0.1f}
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

		UpdateGizmo();

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

	void Tool::UpdateGizmo()
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
			{
				EditTransform();
			}
		}
		ImGui::End();
	}

	void Tool::EditTransform()
	{
		if (IS_DOWN(KeyType::N_3))
			meCurrentOperation = ImGuizmo::TRANSLATE;
		if (IS_DOWN(KeyType::N_2))
			meCurrentOperation = ImGuizmo::ROTATE;
		if (IS_DOWN(KeyType::N_1))
			meCurrentOperation = ImGuizmo::SCALE;
		if (IS_DOWN(KeyType::SQUARE_BKT_L))
			mSnaps *= 0.1f;
		if (IS_DOWN(KeyType::SQUARE_BKT_R))
			mSnaps *= 10.f;

		mSnaps.x = std::clamp(mSnaps.x, 0.01f, 10.f );
		mSnaps.y = std::clamp(mSnaps.y, 0.01f, 10.f );
		mSnaps.z = std::clamp(mSnaps.z, 0.01f, 10.f );
		
		Scene* pActiveScene = GET_SINGLE(SceneManager)->GetActiveScene();
		Matrix viewMat = pActiveScene->GetMainCamera()->GetViewMatrix();
		Matrix projMat = pActiveScene->GetMainCamera()->GetProjectionMatrix();
		Matrix worldMat = mpGameObject->GetTransform()->GetWorldMatrix();
		Matrix identityMat = Matrix::Identity;

		ImGui::Begin("Gizmo");
		ImGuizmo::SetDrawlist();
		float windowWidth = static_cast<float>(ImGui::GetWindowWidth());
		float windowHeight = static_cast<float>(ImGui::GetWindowHeight());
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
		
		ImGuizmo::Manipulate(&viewMat._11, &projMat._11, meCurrentOperation, meCurrentMode, &worldMat._11, &identityMat._11, &mSnaps.x);
		mpGameObject->GetTransform()->SetWorldMatrix(worldMat);

		ImGui::End();
	}

	void Tool::SetGameObject(GameObject* _pGameObject)
	{
		if (nullptr != mpGameObject)
			mpGameObject->GetTransform()->SetUpdateByMat(false);

		AssertEx(nullptr != _pGameObject, L"Tool::SetGameObject() - 게임오브젝트가 nullptr이다.");
		AssertEx(nullptr != _pGameObject->GetTransform(), L"Tool::SetGameObject() - 게임오브젝트가 트랜스폼 컴포넌트를 소유하지 않음");
		mpGameObject = _pGameObject;
	}

	LRESULT Tool::DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
	}
}