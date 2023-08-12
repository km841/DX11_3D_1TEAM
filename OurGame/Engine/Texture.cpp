#include "pch.h"
#include "Texture.h"
#include "Engine.h"

namespace hm
{
	Texture::Texture()
		: Object(ObjectType::Texture)
		, meTextureType(0)
	{
	}

	Texture::~Texture()
	{
	}

	void Texture::Load(const wstring& _path)
	{
		wstring ext = fs::path(_path).extension();

		HRESULT hr = 0;

		if (ext == L".dds" || ext == L".DDS")
			hr = LoadFromDDSFile(_path.c_str(), DDS_FLAGS_NONE, nullptr, mScratchImage);
		else if (ext == L".tga" || ext == L".TGA")
			hr = LoadFromTGAFile(_path.c_str(), nullptr, mScratchImage);
		else // png, jpg, jpeg, bmp
			hr = LoadFromWICFile(_path.c_str(), WIC_FLAGS_NONE, nullptr, mScratchImage);

		//auto absolutePath = fs::absolute(_path);
		//bool bIsExist = fs::exists(absolutePath);

		AssertEx(SUCCEEDED(hr), L"Texture::Load() - 텍스쳐 로드 실패, 경로 문제일 가능성 높음");

		hr = CreateShaderResourceView(
			DEVICE.Get(),
			mScratchImage.GetImages(),
			mScratchImage.GetImageCount(),
			mScratchImage.GetMetadata(),
			mpSRV.GetAddressOf());

		AssertEx(SUCCEEDED(hr), L"Texture::Load() - 텍스쳐 SRV 생성 실패");

		mpSRV->GetResource(reinterpret_cast<ID3D11Resource**>(mpTex2D.GetAddressOf()));
		mName = _path;
		mTexSize = Vec3(
			static_cast<float>(mScratchImage.GetMetadata().width),
			static_cast<float>(mScratchImage.GetMetadata().height), 1.f);
	}

	void Texture::Create(UINT _type, DXGI_FORMAT _eFormat, int _width, int _height, bool _bMultiSampling)
	{
		D3D11_TEXTURE2D_DESC td = { 0 };
		mTexSize = Vec3(static_cast<float>(_width), static_cast<float>(_height), 1.f);

		td.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		td.CPUAccessFlags = 0;
		td.Width = _width;
		td.Height = _height;
		td.ArraySize = 1;
		td.SampleDesc.Count = true == _bMultiSampling ? 4 : 1;
		td.SampleDesc.Quality = 0;
		td.MipLevels = 1;
		td.MiscFlags = 0;
		td.BindFlags = _type;

		if (_type & D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
			td.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		else
			td.Format = _eFormat;

		HRESULT hr = DEVICE->CreateTexture2D(&td, nullptr, mpTex2D.GetAddressOf());
		AssertEx(SUCCEEDED(hr), L"Texture::Create() - Texture2D 생성 실패");

		CreateFromTexture(_type, _eFormat, mpTex2D, _bMultiSampling);
	}

	void Texture::CreateFromTexture(UINT _type, DXGI_FORMAT _eFormat, ComPtr<ID3D11Texture2D> _pTex2D, bool _bMultiSampling)
	{
		meTextureType = _type;
		mpTex2D = _pTex2D;

		D3D11_TEXTURE2D_DESC td = {};
		mpTex2D->GetDesc(&td);

		if (meTextureType & D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rd;
			rd.Format = DXGI_FORMAT_UNKNOWN;
			rd.ViewDimension = true == _bMultiSampling ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
			HRESULT hr = DEVICE->CreateRenderTargetView(mpTex2D.Get(), nullptr, mpRTV.GetAddressOf());

			AssertEx(SUCCEEDED(hr), L"Texture::CreateFromTexture() - 텍스쳐 RTV 생성 실패");
		}

		if (meTextureType & D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC sd = {};
			sd.Format = _eFormat;
			sd.ViewDimension = true == _bMultiSampling ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
			sd.Texture2D.MipLevels = 1;

			HRESULT hr = DEVICE->CreateShaderResourceView(mpTex2D.Get(), &sd, mpSRV.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"Texture::CreateFromTexture() - 텍스쳐 SRV 생성 실패");
		}

		if (meTextureType & D3D11_BIND_DEPTH_STENCIL)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsd = {};
			dsd.Format = DXGI_FORMAT_UNKNOWN;
			dsd.ViewDimension = true == _bMultiSampling ? D3D11_DSV_DIMENSION_TEXTURE2D : D3D11_DSV_DIMENSION_TEXTURE2D;
			HRESULT hr = DEVICE->CreateDepthStencilView(mpTex2D.Get(), nullptr, mpDSV.GetAddressOf());

			AssertEx(SUCCEEDED(hr), L"Texture::CreateFromTexture() - 텍스쳐 DSV 생성 실패");
		}

		if (meTextureType & D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC ud = {};
			ud.Format = _eFormat;
			ud.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;
			HRESULT hr = DEVICE->CreateUnorderedAccessView(mpTex2D.Get(), nullptr, mpUAV.GetAddressOf());
			AssertEx(SUCCEEDED(hr), L"Texture::CreateFromTexture() - 텍스쳐 UAV 생성 실패");
		}
	}
}

