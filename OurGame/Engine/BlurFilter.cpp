#include "pch.h"
#include "BlurFilter.h"
#include "Material.h"

namespace hm
{
	BlurFilter::BlurFilter(shared_ptr<Material> _pMaterial, UINT _width, UINT _height)
		: ImageFilter(_pMaterial, _width, _height)
	{
	}
	void BlurFilter::Render()
	{
		ImageFilter::Render();
	}
}

