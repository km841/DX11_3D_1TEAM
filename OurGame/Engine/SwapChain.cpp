#include "pch.h"
#include "SwapChain.h"
#include "Engine.h"

namespace hm
{
	void SwapChain::Initialize()
	{
		CreateSwapChain();
		CreateRTV();
	}

	void SwapChain::CreateSwapChain()
	{
		mpSwapChain.Reset();
		const WindowInfo& windowInfo = gpEngine->GetWindowInfo();

		DXGI_SWAP_CHAIN_DESC sd = {};

		sd.BufferDesc.Width = static_cast<UINT32>(windowInfo.width);
		sd.BufferDesc.Height = static_cast<UINT32>(windowInfo.height);
		sd.BufferDesc.RefreshRate.Numerator = 60; // 화면 갱신 비율
		sd.BufferDesc.RefreshRate.Denominator = 1; // 화면 갱신 비율
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 버퍼의 디스플레이 형식
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 2;
		sd.OutputWindow = windowInfo.hwnd;
		sd.Windowed = true;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hr = DXGI->CreateSwapChain(DEVICE.Get(), &sd, &mpSwapChain);
		AssertEx(SUCCEEDED(hr), L"SwapChain::CreateSwapChain() - SwapChain 생성 실패");
	}

	void SwapChain::CreateRTV()
	{
		ComPtr<ID3D11Texture2D> pBackBuffer;
		mpSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

		DEVICE->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &mpRTV);
	}
	void SwapChain::Present()
	{
		mpSwapChain->Present(0, 0);
	}
}


