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
		std::vector<ID3D11RenderTargetView*> vRenderTargets(mRenderTargetCount);

		for (int i = 0; i < mRenderTargetCount; ++i)
		{
			vRenderTargets[i] = mRenderTargets[i].pTarget->GetRTV().Get();
		}

		CONTEXT->OMSetRenderTargets(mRenderTargetCount, vRenderTargets.data(), mpDepthStencilTexture->GetDSV().Get());
	}

	void MultiRenderTarget::OMSetRenderTarget(int _index)
	{
		CONTEXT->OMSetRenderTargets(_index, mRenderTargets[0].pTarget->GetRTV().GetAddressOf(), mpDepthStencilTexture->GetDSV().Get());
	}

	void MultiRenderTarget::ClearRenderTargetView()
	{
		for (int i = 0; i < mRenderTargetCount; ++i)
		{
			CONTEXT->ClearRenderTargetView(mRenderTargets[i].pTarget->GetRTV().Get(), mRenderTargets[i].clearColors);
		}

		CONTEXT->ClearDepthStencilView(mpDepthStencilTexture->GetDSV().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
}

