#include "pch.h"
#include "MultiRenderTarget.h"
#include "Engine.h"

namespace hm
{
	void MultiRenderTarget::Create(MultiRenderTargetType _eRenderTargetType, const std::vector<RenderTarget>& _renderTargets, shared_ptr<Texture> _depthStencilTexture)
	{
		meRenderTargetType = _eRenderTargetType;
		mRenderTargets = _renderTargets;
		mpDepthStencilTexture = _depthStencilTexture;
		mRenderTargetCount = static_cast<int>(mRenderTargets.size());
	}

	void MultiRenderTarget::OMSetRenderTarget()
	{
		Vec3 texSize = mRenderTargets[0].pTarget->GetTexSize();
		D3D11_VIEWPORT vp = D3D11_VIEWPORT{ 0.f, 0.f, texSize.x, texSize.y, 0.f, 1.f };
		D3D11_RECT rect = D3D11_RECT{ 0, 0, static_cast<LONG>(texSize.x), static_cast<LONG>(texSize.y) };

		CONTEXT->RSSetViewports(1, &vp);
		CONTEXT->RSSetScissorRects(1, &rect);

		std::vector<ID3D11RenderTargetView*> renderTargets(mRenderTargetCount);
		for (int i = 0; i < mRenderTargetCount; ++i)
		{
			renderTargets[i] = mRenderTargets[i].pTarget->GetRTV().Get();
		}

		CONTEXT->OMSetRenderTargets(mRenderTargetCount, renderTargets.data(), mpDepthStencilTexture->GetDSV().Get());
	}

	void MultiRenderTarget::OMSetRenderTarget(int _index)
	{
		Vec2 resolution = gpEngine->GetResolution();
		D3D11_VIEWPORT vp = D3D11_VIEWPORT{ 0.f, 0.f, resolution.x, resolution.y, 0.f, 1.f };
		D3D11_RECT rect = D3D11_RECT{ 0, 0, static_cast<LONG>(resolution.x), static_cast<LONG>(resolution.y) };

		CONTEXT->RSSetViewports(1, &vp);
		CONTEXT->RSSetScissorRects(1, &rect);

		CONTEXT->OMSetRenderTargets(_index, mRenderTargets[0].pTarget->GetRTV().GetAddressOf(), mpDepthStencilTexture->GetDSV().Get());
	}

	void MultiRenderTarget::ClearRenderTargetView()
	{
		for (int i = 0; i < mRenderTargetCount; ++i)
		{
			CONTEXT->ClearRenderTargetView(mRenderTargets[i].pTarget->GetRTV().Get(), mRenderTargets[i].clearColors);
		}

		CONTEXT->ClearDepthStencilView(mpDepthStencilTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
	void MultiRenderTarget::ClearDepthView()
	{
		CONTEXT->ClearDepthStencilView(mpDepthStencilTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	void MultiRenderTarget::SetClearColor(Vec4 _color)
	{
		_color /= 255.f;

		for (int i = 0; i < mRenderTargetCount; ++i)
		{
			memcpy(mRenderTargets[i].clearColors, &_color.x, sizeof(Vec4));
		}
	}
	void MultiRenderTarget::SetClearColor(int _index, Vec4 _color)
	{
		_color /= 255.f;
		memcpy(mRenderTargets[_index].clearColors, &_color.x, sizeof(Vec4));
	}
}

