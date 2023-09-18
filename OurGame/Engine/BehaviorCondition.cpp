#include "pch.h"
#include "BehaviorCondition.h"

namespace hm
{
	BehaviorCondition::BehaviorCondition(std::function<BehaviorResult()> _behavior)
	{
		mBehavior = _behavior;
	}
}