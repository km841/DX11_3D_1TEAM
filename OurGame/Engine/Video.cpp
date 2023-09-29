#include "pch.h"
#include "Video.h"
#include "Engine.h"
#include "RenderManager.h"
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
		//HRESULT hr = VBUILDER->RenderFile(mPath.c_str(), NULL);
		VBUILDER->AddSourceFilter(mPath.c_str(), mPath.c_str(), &mpBaseFilter);
		CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC, IID_IBaseFilter, reinterpret_cast<void**>(mpRenderer.GetAddressOf()));
		VBUILDER->AddFilter(mpRenderer.Get(), L"Video Renderer");

		HRESULT hr = mpBaseFilter->FindPin(L"Output", reinterpret_cast<IPin**>(mpSourceOutputPin.GetAddressOf()));
		AssertEx(SUCCEEDED(hr), L"Video::Load() - Output Pin 생성 실패");

		hr = mpRenderer->FindPin(L"VMR Input0", reinterpret_cast<IPin**>(mpRendererInputPin.GetAddressOf()));
		VBUILDER->ConnectDirect(mpSourceOutputPin.Get(), mpRendererInputPin.Get(), NULL);

		hr = VCONTROL->Run();
		// Wait for the video to finish (replace with your game loop)
		Sleep(5000); // Sleep for 5 seconds

		// Stop the graph
		VCONTROL->Stop();


	}
}