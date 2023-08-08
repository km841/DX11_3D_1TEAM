#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class CameraMoveScript :
		public MonoBehavior
	{
	public:
		CameraMoveScript();
		~CameraMoveScript() = default;
		virtual void FixedUpdate() override;

	private:
		float mSpeed;
	};
}


