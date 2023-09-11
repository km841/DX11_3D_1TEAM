#pragma once

namespace hm
{
	class Timer
	{
		DECLARE_SINGLE(Timer);

	public:
		void   Initialize();
		void   Update();
		void   Render();

		UINT32 GetFPS()       const { return mFPS; }
		float  GetDeltaTime() const { return mDeltaTime; }

	private:
		UINT32 mFPS = 0;
		UINT64 mFrequency = 0;
		UINT64 mPrevCount = 0;
		UINT32 mFrameCount = 0;

		float  mFrameTime = 0.f;
		float  mDeltaTime = 0.f;

		float mStepSize = 1.f / 30.f;

	};
}


