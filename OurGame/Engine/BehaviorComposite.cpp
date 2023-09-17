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
	void BehaviorComposite::AddChild(BehaviorNode* _pChild)
	{
		mChildren.push_back(_pChild);
	}

}
