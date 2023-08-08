#pragma once
#include "ImageFilter.h"

namespace hm
{
	class CombineFilter :
		public ImageFilter
	{
	public:
		CombineFilter(shared_ptr<Material> _pMaterial, UINT _width, UINT _height);
		virtual ~CombineFilter() = default;

		virtual void Render();
	};
}


