#include "pch.h"
#include "CombineFilter.h"
#include "MultiRenderTarget.h"
#include "Texture.h"
#include "Engine.h"
#include "Material.h"
#include "Mesh.h"


namespace hm
{
	CombineFilter::CombineFilter(shared_ptr<Material> _pMaterial, UINT _width, UINT _height)
		: ImageFilter(_pMaterial, _width, _height)
	{
	}

	void CombineFilter::Render()
	{
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		CONTEXT->ClearRenderTargetView(mpTexture->GetRTV().Get(), clearColor);
		CONTEXT->RSSetViewports(1, &mViewport);
		gpEngine->GetMultiRenderTarget(MultiRenderTargetType::SwapChain)->OMSetRenderTarget(1);

		mpMaterial->PushGraphicData();
		mpMesh->Render();
	}
}

