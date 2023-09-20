#pragma once
#include "BehaviorNode.h"
namespace hm
{
	class BehaviorComposite :
		public BehaviorNode
	{
	public:
		BehaviorComposite() = default;
		virtual ~BehaviorComposite();
		virtual void Release();
		virtual void SetRoot(BehaviorNode* _pNode);
		virtual void SetAI(AI* _pAI);

	public:
		void AddChild(BehaviorNode* _pChild);

	protected:
		std::vector<BehaviorNode*> mChildren;
	};
}

