#include "pch.h"
#include "Video.h"
#include "Engine.h"
namespace hm
{
	Video::Video()
		: Object(ObjectType::Video)
	{
	}
	Video::~Video()
	{
	}
	void Video::Load(const wstring& _path)
	{
		mPath = _path;
		bool bExists = fs::exists(_path);
		AssertEx(bExists, L"Video::Load() - 존재하지 않는 경로");
	}
	void Video::Play()
	{
		HRESULT hr = VBUILDER->RenderFile(mPath.c_str(), NULL);

		if (SUCCEEDED(hr))
		{
			VWINDOW->put_Left(0);
			VWINDOW->put_Top(0);

			VWINDOW->put_FullScreenMode(OATRUE);

			hr = VCONTROL->Run();
			if (SUCCEEDED(hr))
			{
				long ev;
				VEVENT->WaitForCompletion(INFINITE, &ev);
			}
		}

		else
		{
			AssertEx(false, L"Video::Play() - 비디오를 실행할 수 없음 (경로 문제일 가능성 높음)");
		}

	}
}