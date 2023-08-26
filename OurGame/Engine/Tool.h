#pragma once
namespace hm
{
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

	private:
		void InitGui();

	private:
		HWND mHwnd;
		ComPtr<ID3D11Device> mpDevice;
		ComPtr<ID3D11DeviceContext> mpContext;
	};
}


