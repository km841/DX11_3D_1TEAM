#pragma once
#include "Object.h"

namespace hm
{
	class Video :
		public Object
	{
	public:
		Video();
		virtual ~Video();
		// Resources에 의해 호출되며 외부 이미지를 로드하는 함수
		virtual void Load(const wstring& _path) override;

	public:
		void Play();
		
	private:
		ComPtr<IBaseFilter> mpBaseFilter;
		ComPtr<IBaseFilter> mpRenderer;
		ComPtr<IPin> mpSourceOutputPin;
		ComPtr<IPin> mpRendererInputPin;
		wstring mPath;
	};
}


