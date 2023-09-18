#include "pch.h"
#include "Sequence.h"

namespace hm
{
	Sequence::Sequence(std::function<BehaviorResult()> _behavior)
	{
		mBehavior = _behavior;
	}
	BehaviorResult Sequence::Run()
	{
		for (BehaviorNode* pChild : mChildren)
		{
			BehaviorResult eResult = pChild->Run();
			if (BehaviorResult::Failure == eResult)
				return BehaviorResult::Failure;

			else if (BehaviorResult::Running == eResult)
				return BehaviorResult::Running;
		}

		return BehaviorResult::Success;
	}
}