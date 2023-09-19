#pragma once
#include "AI.h"
namespace hm
{
	class BehaviorNode
	{
	public:
		BehaviorNode() = default;
		virtual ~BehaviorNode() { }

		virtual void Release();
		virtual void SetRoot(BehaviorNode* _pNode);
		virtual void SetAI(AI* _pAI);

	public:
		virtual BehaviorResult Run() = 0;
		AI*  GetAI() { return mpAI; }

		template<typename T = class Monster>
		T* GetMonster()
		{
			AssertEx(nullptr != mpAI, L"BehaviorNode::GetMonster() - AI가 설정되지 않음");
			T* pMonster = static_cast<T*>(mpAI->GetGameObject());
			return pMonster;
		}

	protected:
		std::function<BehaviorResult()> mBehavior;
		BehaviorNode*					mpRoot = nullptr;
		AI*								mpAI   = nullptr;
	};
}


