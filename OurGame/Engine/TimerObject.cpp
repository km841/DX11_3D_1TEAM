#include "pch.h"
#include "TimerObject.h"
#include "Timer.h"

TimerObject::TimerObject()
	: mbIsFinished(false)
	, mbIsRunning(false)
	, mEndTime(0.f)
	, mCurTime(0.f)
{
}

float TimerObject::GetProgress()
{
	return mCurTime / mEndTime;
}

void TimerObject::Update()
{
	if (mbIsRunning)
		mCurTime += DELTA_TIME;

	if (mCurTime > mEndTime)
	{
		mCurTime = mEndTime;
		mbIsFinished = true;
		mbIsRunning = false;
	}
}

void TimerObject::Start()
{
	mbIsRunning = true;
}

void TimerObject::Stop()
{
	mbIsRunning = false;
	mCurTime = 0.f;
}

bool TimerObject::IsFinished()
{
	return mbIsFinished;
}
