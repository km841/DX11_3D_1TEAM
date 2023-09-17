#pragma once
#include "BehaviorComposite.h"

namespace hm
{
	class Selector :
		public BehaviorComposite
	{
	public:
		Selector(std::function<BehaviorResult()> _behavior = nullptr);
		virtual ~Selector() { }

	public:
		virtual BehaviorResult Run() override;

	};

}

