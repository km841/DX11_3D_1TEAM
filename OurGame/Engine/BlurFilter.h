#pragma once
#include "ImageFilter.h"

namespace hm
{
	class Material;
	class BlurFilter :
		public ImageFilter
	{
	public:
		BlurFilter(shared_ptr<Material> _pMaterial, UINT _width, UINT _height);
		virtual ~BlurFilter() = default;

		virtual void Render();
	};

}

