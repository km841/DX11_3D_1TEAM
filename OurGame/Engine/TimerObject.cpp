#include "pch.h"
#include "TimerObject.h"
#include "Timer.h"

TimerObject::TimerObject(float _endTime)
	: mbIsFinished(false)
	, mbIsRunning(false)
	, mEndTime(_endTime)
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
	mbIsFinished = false;
	mbIsRunning = false;
	mCurTime = 0.f;
}

bool TimerObject::IsFinished()
{
	return mbIsFinished;
}
