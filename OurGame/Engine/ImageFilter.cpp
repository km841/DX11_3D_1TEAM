#include "pch.h"
#include "ImageFilter.h"
#include "Resources.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"
#include "Engine.h"

namespace hm
{
	ImageFilter::ImageFilter(shared_ptr<Material> _pMaterial, UINT _width, UINT _height)
	: mpMaterial(_pMaterial)
	, mWidth(_width)
	, mHeight(_height)
	{
		UINT32 format = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET |
			D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
			
		if (ShaderType::Compute == _pMaterial->GetShader()->GetShaderType())
			format |= D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;

		mpTexture = GET_SINGLE(Resources)->CreateTexture(
			std::to_wstring((UINT64)this),
			DXGI_FORMAT_R8G8B8A8_UNORM,
			format,
			_width, _height
		);

		mpMesh = GET_SINGLE(Resources)->LoadRectMesh();

		ZeroMemory(&mViewport, sizeof(D3D11_VIEWPORT));
		mViewport.TopLeftX = 0;
		mViewport.TopLeftY = 0;
		mViewport.Width = float(_width);
		mViewport.Height = float(_height);
		mViewport.MinDepth = 0.0f;
		mViewport.MaxDepth = 1.0f;

		mpMaterial->SetVec2(0, Vec2(1.f / _width, 1.f / _height));
	}
	void ImageFilter::Render()
	{
		ShaderType eShaderType = mpMaterial->GetShader()->GetShaderType();

		if (ShaderType::Compute == eShaderType)
		{
			mpMaterial->SetTexture(0, mpTexture);
			mpMaterial->Dispatch(1, 1024, 1);
		}
		else
		{
			float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			CONTEXT->ClearRenderTargetView(mpTexture->GetRTV().Get(), clearColor);
			CONTEXT->RSSetViewports(1, &mViewport);
			CONTEXT->OMSetRenderTargets(1, mpTexture->GetRTV().GetAddressOf(), nullptr);
			mpMaterial->PushGraphicData();
			mpMesh->Render();
		}
	}
	void ImageFilter::SetSRV(int _index, shared_ptr<Texture> _pTexture)
	{
		mpMaterial->SetTexture(_index, _pTexture);
	}
}

