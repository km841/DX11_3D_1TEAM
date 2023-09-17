#pragma once
namespace hm
{
	class AI;
	class Monster;
	class BehaviorNode
	{
	public:
		BehaviorNode() = default;
		virtual ~BehaviorNode() { }

		virtual void Release();

	public:
		virtual BehaviorResult Run() = 0;

		void SetAI(AI* _pAI) { mpAI = _pAI; }
		AI*  GetAI() { return mpAI; }

	protected:
		std::function<BehaviorResult()> mBehavior;
		BehaviorNode*					mpRoot = nullptr;
		AI*								mpAI   = nullptr;
	};
}


