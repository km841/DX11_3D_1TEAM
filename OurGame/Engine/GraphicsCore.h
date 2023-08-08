#pragma once

namespace hm
{

	/*
	 - DirectX11에서 주요 기능을 담당하는 Device와 Context를 관리하는 클래스
	*/

	class GraphicsCore
	{
	public:
		GraphicsCore() = default;
		~GraphicsCore() = default;
	public:
		// 내부에서 디바이스, 컨텍스트와 Dxgi를 생성
		void Initialize();

		ComPtr<ID3D11DeviceContext> GetContext() { return mpContext; }
		ComPtr<ID3D11Device> GetDevice() { return mpDevice; }
		ComPtr<IDXGIFactory> GetDxgi() { return mpDxgi; }

	private:
		// 디바이스와 컨텍스트를 생성한다
		void CreateDeviceAndContext();

		// DxgiFactory를 생성한다. (DxgiFactory는 SwapChain을 만들 때 사용한다)
		void CreateDxgiFactory();

	private:
		ComPtr<ID3D11DeviceContext> mpContext;
		ComPtr<ID3D11Device> mpDevice;
		ComPtr<IDXGIFactory> mpDxgi;
	};
}


