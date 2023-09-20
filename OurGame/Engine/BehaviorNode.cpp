#include "pch.h"
#include "BehaviorNode.h"
#include "AI.h"

namespace hm
{
	void BehaviorNode::Release()
	{
		delete this;
	}
	void BehaviorNode::SetRoot(BehaviorNode* _pNode)
	{
		mpRoot = _pNode;
	}
	void BehaviorNode::SetAI(AI* _pAI)
	{
		mpAI = _pAI;
	}
}