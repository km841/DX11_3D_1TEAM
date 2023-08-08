#include "pch.h"
#include "GraphicsCore.h"

namespace hm
{
	void GraphicsCore::Initialize()
	{
		CreateDeviceAndContext();
		CreateDxgiFactory();

	}
	void GraphicsCore::CreateDeviceAndContext()
	{
		// Create Device/Context
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

//#if defined(DEBUG_BUILD)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif
		HRESULT hResult = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
			0, creationFlags,
			featureLevels, ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION, &mpDevice,
			0, &mpContext);
		AssertEx(SUCCEEDED(hResult), L"GraphicsCore::CreateDeviceAndContext() - Device 积己 角菩");
	}


	void GraphicsCore::CreateDxgiFactory()
	{
		// Create DXGI
		HRESULT hResult = CreateDXGIFactory(IID_PPV_ARGS(&mpDxgi));
		AssertEx(SUCCEEDED(hResult), L"GraphicsCore::CreateDxgiFactory() - DxgiFactory 积己 角菩");
	}
}

