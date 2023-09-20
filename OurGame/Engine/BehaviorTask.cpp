#include "pch.h"
#include "BehaviorTask.h"

namespace hm
{
	BehaviorTask::BehaviorTask(std::function<BehaviorResult()> _behavior)
	{
		mBehavior = _behavior;
	}
}