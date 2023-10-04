#pragma once
#include "Effect.h"

namespace hm
{
	class SwordGlareEffect :
		public Effect
	{
	public:
		SwordGlareEffect();
		virtual ~SwordGlareEffect();
		SwordGlareEffect* Clone()
		{
			SwordGlareEffect* pEffect = GameObject::Clone<SwordGlareEffect>();
			return pEffect;
		}

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();
	};
}


