#include "pch.h"
#include "BehaviorComposite.h"

namespace hm
{
	BehaviorComposite::~BehaviorComposite()
	{
	}
	void BehaviorComposite::Release()
	{
		for (int i = 0; i < mChildren.size(); ++i)
		{
			mChildren[i]->Release();
		}

		delete this;
	}
	void BehaviorComposite::SetRoot(BehaviorNode* _pNode)
	{
		for (int i = 0; i < mChildren.size(); ++i)
		{
			mChildren[i]->SetRoot(_pNode);
		}
		BehaviorNode::SetRoot(_pNode);
	}
	void BehaviorComposite::SetAI(AI* _pAI)
	{
		for (int i = 0; i < mChildren.size(); ++i)
		{
			mChildren[i]->SetAI(_pAI);
		}
		BehaviorNode::SetAI(_pAI);
	}
	void BehaviorComposite::AddChild(BehaviorNode* _pChild)
	{
		mChildren.push_back(_pChild);
	}

}
