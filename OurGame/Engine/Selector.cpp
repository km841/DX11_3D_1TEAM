#include "pch.h"
#include "Selector.h"

namespace hm
{
	Selector::Selector(std::function<BehaviorResult()> _behavior)
	{
		mBehavior = _behavior;
	}
	BehaviorResult Selector::Run()
	{
		for (BehaviorNode* pChild : mChildren)
		{
			BehaviorResult eResult = pChild->Run();
			if (BehaviorResult::Success == eResult)
				return BehaviorResult::Success;

			else if (BehaviorResult::Running == eResult)
				return BehaviorResult::Running;
		}

		return BehaviorResult::Failure;
	}
}