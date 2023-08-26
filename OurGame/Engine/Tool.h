#pragma once
namespace hm
{
	class GameObject;
	class Tool
	{
	public:
		Tool();
		~Tool();
	public:
		void Initialize(HWND _hwnd, ComPtr<ID3D11Device> _pDevice, ComPtr<ID3D11DeviceContext> _pContext);
		void Update();
		void Render();

	public:
		LRESULT DispatchWndMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void SetGameObject(GameObject* _pGameObject);

	private:
		void InitGui();
		void UpdateGui();
		void EditTransform();
		

	private:
		HWND mHwnd;
		ComPtr<ID3D11Device> mpDevice;
		ComPtr<ID3D11DeviceContext> mpContext;

		GameObject* mpGameObject;
	};
}


