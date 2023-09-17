#pragma once
#include "BehaviorNode.h"

namespace hm
{
	class GameObject;
	class BehaviorCondition :
		public BehaviorNode
	{
	public:
		BehaviorCondition(std::function<BehaviorResult()> _behavior = nullptr);
		virtual ~BehaviorCondition() { }

	public:
		virtual BehaviorResult Run() { return nullptr != mBehavior ? mBehavior() : BehaviorResult::Success; }

	protected:
	};
}


