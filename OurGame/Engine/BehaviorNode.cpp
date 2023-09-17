#include "pch.h"
#include "BehaviorNode.h"

namespace hm
{
	void BehaviorNode::Release()
	{
		delete this;
	}
}