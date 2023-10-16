#include "pch.h"
#include "Timer.h"
#include "Engine.h"

namespace hm
{

	Timer::Timer()
	{

	}

	Timer::~Timer()
	{

	}
	void Timer::Initialize()
	{
		::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mFrequency));
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mPrevCount)); // CPU Å¬·°
	}

	void Timer::Update()
	{
		UINT64 currentCount;
		::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

		mDeltaTime = (currentCount - mPrevCount) / static_cast<float>(mFrequency);

		if (mDeltaTime > mStepSize)
			mDeltaTime = mStepSize;

		mFrameCount++;
		mFrameTime += mDeltaTime;
		mPrevCount = currentCount;

		if (mFrameTime > 1.f)
		{
			mFPS = static_cast<UINT32>(mFrameCount / mFrameTime);
			mFrameTime = 0.f;
			mFrameCount = 0;
		}
	}

	void Timer::Render()
	{
		//WCHAR text[100] = L"";
		//::wsprintf(text, L"FPS : %d", static_cast<int>(mFPS));

		//::SetWindowText(gpEngine->GetWindowInfo().hwnd, text);
	}

}

