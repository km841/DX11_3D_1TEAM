#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class PaperBurnScript :
		public MonoBehavior
	{
	public:
		PaperBurnScript();
		~PaperBurnScript() = default;
		virtual void FixedUpdate() override;

	private:
		float mAccTime;
	};
}


