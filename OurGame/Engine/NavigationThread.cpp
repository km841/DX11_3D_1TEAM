#include "pch.h"
#include "NavigationThread.h"
#include "NavSceneComponent.h"

namespace hm
{
	NavigationThread::NavigationThread()
		: mpNavManager(nullptr)
		, mpNavSceneComponent(nullptr)
	{
		SetLoop(true);
		mExitEvent = CreateEvent(nullptr, false, false, nullptr);
	}

	NavigationThread::~NavigationThread()
	{
		SetLoop(false);
		WaitForSingleObject(mExitEvent, INFINITE);
		CloseHandle(mExitEvent);
		SAFE_DELETE(mpNavSceneComponent);
	}
	void NavigationThread::Run()
	{
		/*while (true == mbLoop)
		{
			if (false == mWorkQueue.Empty())
			{
				NavWorkData workData = mWorkQueue.Front();
				mWorkQueue.Pop();

				NavResultData resultData;
				mpNavSceneComponent->FindPath(workData.pTransform->GetPosition(), workData.end, resultData.pathList);

				resultData.callback = workData.callback;
				mpNavManager->AddNavResult(resultData);
			}
		}

		::SetEvent(mExitEvent);*/
	}
	void NavigationThread::DisableCell(std::vector<Vec3>& _exceptPos)
	{
	}

	void NavigationThread::DisableCell(std::vector<NavigationCell*>& _exceptCell)
	{
	}
}

