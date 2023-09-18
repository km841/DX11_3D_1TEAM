#pragma once
#include "BehaviorNode.h"

namespace hm
{
	class BehaviorTask :
		public BehaviorNode
	{
	public:
		BehaviorTask(std::function<BehaviorResult()> _behavior = nullptr);
		virtual ~BehaviorTask() { }

	public:
		virtual BehaviorResult Run() { return nullptr != mBehavior ? mBehavior() : BehaviorResult::Success; }

	};

}

