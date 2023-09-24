#include "pch.h"
#include "ThreadBase.h"

namespace hm
{
	ThreadBase::ThreadBase()
		: mThreadHandle(0)
		, mStartEvent(0)
		, mbLoop(false)
	{
	}
	ThreadBase::~ThreadBase()
	{
		if (mStartEvent)
		{
			CloseHandle(mStartEvent);
			mStartEvent = 0;
		}
	}
	void ThreadBase::Initialize()
	{
		mStartEvent = CreateEvent(nullptr, false, false, nullptr);
		mThreadHandle = (HANDLE)_beginthreadex(nullptr, 0, ThreadBase::ThreadFunction, this, 0, nullptr);
	}
	void ThreadBase::Run()
	{
	}
	void ThreadBase::Start()
	{
		::SetEvent(mStartEvent);
	}
	void ThreadBase::Pause()
	{
		DWORD count = 0;
		do
		{
			count = ::SuspendThread(mThreadHandle);
		} while (count <= 0);
	}
	void ThreadBase::Resume()
	{
		DWORD count = 0;
		do
		{
			count = ::ResumeThread(mThreadHandle);
		} while (count >= 0);
	}
	void ThreadBase::WaitStartEvent()
	{
		WaitForSingleObject(mStartEvent, INFINITE);
	}
	UINT32 __stdcall ThreadBase::ThreadFunction(void* _pArg)
	{
		ThreadBase* pThread = (ThreadBase*)_pArg;
		pThread->WaitStartEvent();
		pThread->Run();

		return 0;
	}
}