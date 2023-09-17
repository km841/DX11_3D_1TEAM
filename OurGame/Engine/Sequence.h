#pragma once
#include "BehaviorComposite.h"
namespace hm
{
	class Sequence :
		public BehaviorComposite
	{
	public:
		Sequence(std::function<BehaviorResult()> _behavior = nullptr);
		virtual ~Sequence() { }

	public:
		virtual BehaviorResult Run() override;
	};
}


