#pragma once
#include "GameObject.h"

namespace hm
{
	class Effect :
		public GameObject
	{
	public:
		Effect();
		virtual ~Effect();
		Effect* Clone()
		{
			Effect* pEffect = GameObject::Clone<Effect>();
			return pEffect;
		}

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void PushBloomData() {}
	};
}
