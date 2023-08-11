#pragma once
#include "GameObject.h"

namespace hm
{
	class DecoObject :
		public GameObject
	{
	public:
		DecoObject();
		virtual ~DecoObject();
		DecoObject* Clone()
		{
			DecoObject* pDecoObject = GameObject::Clone<DecoObject>();
			return pDecoObject;
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


