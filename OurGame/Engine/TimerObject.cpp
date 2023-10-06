#include "pch.h"
#include "TimerObject.h"
#include "Timer.h"

TimerObject::TimerObject(float _endTime)
	: mbIsFinished(false)
	, mbIsRunning(false)
	, mbIsPaused(false)
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
	if (mbIsRunning && !mbIsPaused)
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

void TimerObject::Pause()
{
	if (true == mbIsRunning)
	{
		mbIsPaused = true;
	}
}

void TimerObject::Resume()
{
	if (false == mbIsRunning && false == mbIsFinished)
		mbIsPaused = false;
}

bool TimerObject::IsFinished()
{
	return mbIsFinished;
}
